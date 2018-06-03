#include <stdbool.h>
#include <stdio.h>
#include "string_processor.h"


// string_proc_list* string_proc_list_create(char* name){
// 	string_proc_list* list	= malloc(sizeof(string_proc_list));
// 	list->name				= str_copy(name);
// 	list->first				= NULL;
// 	list->last				= NULL;
// 	return list;
// }

// string_proc_node* string_proc_node_create(string_proc_func f, string_proc_func g, string_proc_func_type type){
// 	string_proc_node* node	= malloc(sizeof(string_proc_node));
// 	node->next				= NULL;
// 	node->previous			= NULL;
// 	node->f					= f;
// 	node->g					= g;
// 	node->type				= type;
// 	return node;
// }

// string_proc_key* string_proc_key_create(char* value){
// 	string_proc_key* key	= malloc(sizeof(string_proc_key));
// 	key->length				= str_len(value);
// 	key->value				= str_copy(value);
// 	return key;
// }

// void string_proc_list_destroy(string_proc_list* list){
// 	free(list->name);
// 	string_proc_node* current_node	= list->first;
// 	string_proc_node* next_node		= NULL;
// 	while(current_node != NULL){
// 		next_node		= current_node->next;
// 		string_proc_node_destroy(current_node);
// 		current_node	= next_node;
// 	}
// 	list->first						= NULL;
// 	list->last						= NULL;
// 	free(list);
// }

// void string_proc_node_destroy(string_proc_node* node){
// 	node->next		= NULL;
// 	node->previous	= NULL;
// 	node->f			= NULL;
// 	node->g			= NULL;			
// 	free(node);
// }

// void string_proc_key_destroy(string_proc_key* key){
// 	free(key->value);
// 	key->value	= NULL;
// 	key->length	= 0;
// 	free(key);
// }

// void string_proc_list_add_node(string_proc_list* list, string_proc_func f, string_proc_func g, string_proc_func_type type){
// 	string_proc_node* node	= string_proc_node_create(f, g, type);
// 	if(list->first == NULL){
// 		list->first	= node;
// 		list->last	= node;	
// 	}else{
// 		string_proc_node* old_last	= list->last;
// 		list->last		= node;
// 		old_last->next	=  node;
// 		node->previous	= old_last;
// 	}
// }

// void string_proc_list_apply(string_proc_list* list, string_proc_key* key, bool encode){
// 	if(encode){
// 		string_proc_node* current_node	= list->first;
// 		while(current_node != NULL){
// 			current_node->f(key);
// 			current_node	= current_node->next;
// 		}
// 	}else{
// 		string_proc_node* current_node	= list->last;
// 		while(current_node != NULL){
// 			current_node->g(key);
// 			current_node	= current_node->previous;
// 		}
// 	}
// }

char* string_proc_func_type_string(string_proc_func_type type){
	switch(type){
		case REVERSIBLE: return "reversible";
		case IRREVERSIBLE: return "irreversible";
		default: return "undefined";
	}
}

void string_proc_list_print(string_proc_list* list, FILE* file){
	uint32_t length	= 0;
	string_proc_node* current_node	= list->first;
	while(current_node != NULL){
		length++;
		current_node = current_node->next;
	}
	fprintf( file, "List length:%d\n", length );
	current_node	= list->first;
	while(current_node != NULL){
		fprintf(file, "\tnode type:%s\n", string_proc_func_type_string(current_node->type)); 
		current_node = current_node->next;
	}
}
void string_proc_list_encode(string_proc_list* list, char* msg, FILE* file){
	string_proc_key* key	= string_proc_key_create(msg);
	string_proc_list_apply(list, key, true);
	fprintf(file, "%s", key->value);
	string_proc_key_destroy(key);
}
void string_proc_list_decode(string_proc_list* list, char* msg, FILE* file){
	string_proc_key* key	= string_proc_key_create(msg);
	string_proc_list_apply(list, key, false);
	fprintf(file, "%s", key->value);
	string_proc_key_destroy(key);
}


/**  **/
uint32_t string_proc_list_type_amount(string_proc_list* list, string_proc_func_type type){
	uint32_t amount = 0;
	string_proc_node* current_node	= list->first;
	while(current_node != NULL){
		if(current_node->type == type)
			amount++;
		current_node	= current_node->next;
	}
	return amount;
}
string_proc_list* string_proc_list_filter_by_type(string_proc_list* list, string_proc_func_type type){
	string_proc_list* new_list		= string_proc_list_create(list->name);
	string_proc_node* current_node	= list->first;
	while(current_node != NULL){
		if(current_node->type == type){
			string_proc_list_add_node(new_list, current_node->f, current_node->g, current_node->type);
		}
		current_node	= current_node->next;
	}
	return new_list;	
}
string_proc_list* string_proc_list_invert(string_proc_list* list){
	string_proc_list* new_list		= string_proc_list_create(list->name);
	string_proc_node* current_node	= list->first;
	while(current_node != NULL){
		string_proc_list_add_node(new_list, current_node->g, current_node->f, current_node->type);
		current_node	= current_node->next;
	}
	return new_list;	
}

/** AUX FUNCTIONS **/
uint32_t str_len(char* a) {
	uint32_t i=0;
	while(a[i]!=0) {
		i++;
	}
	return i;
}

char* str_copy(char* a) {
	uint32_t len	= str_len(a);
	char* s=malloc(len+1);
	s[len] = '\0';
	while(len--!=0) { 
		s[len]=a[len];
	}
	return s;
}

int32_t str_cmp(char* a, char* b) {
  int i=0;
  while(a[i]==b[i] && a[i]!=0 && b[i]!=0) i++;
  if(a[i]==0 && b[i]==0) return 0;
  if(a[i]==0) return 1;
  if(b[i]==0) return -1;
  if(a[i]<b[i])
    return 1;
  else
    return -1;
}

/** **/
char wrap_around_int(int32_t value){
	if(value < 0){
		while(value < 0)value += 256;
	}else if(value > 255){
		while(value > 255)value -=  256;
	}
	return (char)value;
}

char saturate_int(int32_t value){
	if(value < 0){
		value = 0;
	}else if(value > 255){
		value = 255;
	}
	return (char)value;
}

void shift_2(string_proc_key* key){
	uint32_t i;
	for(i = 0; i < key->length; i++){
		key->value[i] = wrap_around_int(((int32_t)key->value[i]) + 2);
	}
}
void unshift_2(string_proc_key* key){
	uint32_t i;
	for(i = 0; i < key->length; i++){
		key->value[i] = wrap_around_int(((int32_t)key->value[i]) - 2);
	}
}
void shift_position(string_proc_key* key){
	uint32_t i;
	for(i = 0; i < key->length; i++){
		key->value[i] = wrap_around_int(((int32_t)key->value[i]) + i);
	}
}
void unshift_position(string_proc_key* key){
	uint32_t i;
	for(i = 0; i < key->length; i++){
		key->value[i] = wrap_around_int(((int32_t)key->value[i]) - i);
	}
}
void saturate_2(string_proc_key* key){
	uint32_t i;
	for(i = 0; i < key->length; i++){
		key->value[i] = saturate_int(((int32_t)key->value[i]) + 2);
	}
}
void unsaturate_2(string_proc_key* key){
	uint32_t i;
	for(i = 0; i < key->length; i++){
		key->value[i] = saturate_int(((int32_t)key->value[i]) - 2);
	}
}
void saturate_position(string_proc_key* key){
	uint32_t i;
	for(i = 0; i < key->length; i++){
		key->value[i] = saturate_int(((int32_t)key->value[i]) + i);
	}
}
void unsaturate_position(string_proc_key* key){
	uint32_t i;
	for(i = 0; i < key->length; i++){
		key->value[i] = saturate_int(((int32_t)key->value[i]) - i);
	}
}
