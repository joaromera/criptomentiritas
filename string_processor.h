#ifndef STRING_PROC_H
#define STRING_PROC_H
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
/**  **/
typedef enum string_proc_func_type_t{
	REVERSIBLE 		= 0,
	IRREVERSIBLE	= 1
} __attribute__((__packed__)) string_proc_func_type;

typedef struct string_proc_key_t {
	uint32_t length;
	char* value;
} __attribute__((__packed__)) string_proc_key; 
typedef void (*string_proc_func) (string_proc_key*);
typedef struct string_proc_list_t {
	char* name;
	struct string_proc_node_t* first;
	struct string_proc_node_t* last;
} __attribute__((__packed__)) string_proc_list;

typedef struct string_proc_node_t {
	struct string_proc_node_t* next;
	struct string_proc_node_t* previous;
	string_proc_func f;
	string_proc_func g;
	string_proc_func_type type;
} __attribute__((__packed__)) string_proc_node;
       
/**  **/
string_proc_list* string_proc_list_create(char* name);
string_proc_node* string_proc_node_create(string_proc_func f, string_proc_func g, string_proc_func_type type);
string_proc_key* string_proc_key_create(char* value);
void string_proc_list_destroy(string_proc_list* list);
void string_proc_node_destroy(string_proc_node* node);
void string_proc_key_destroy(string_proc_key* key);
void string_proc_list_add_node(string_proc_list* list, string_proc_func f, string_proc_func g, string_proc_func_type type);
void string_proc_list_apply(string_proc_list* list, string_proc_key* key, bool encode);
/** **/
char* string_proc_func_type_string(string_proc_func_type type);
void string_proc_list_print(string_proc_list* list, FILE* file);
void string_proc_list_encode(string_proc_list* list, char* msg, FILE* file);
void string_proc_list_decode(string_proc_list* list, char* msg, FILE* file);
/**  **/
uint32_t string_proc_list_type_amount(string_proc_list* list, string_proc_func_type type);
string_proc_list* string_proc_list_filter_by_type(string_proc_list* list, string_proc_func_type type);
string_proc_list* string_proc_list_invert(string_proc_list* list);

/** Funciones Auxiliares Sugeridas **/
uint32_t str_len(char* a);
char* str_copy(char* a);
int32_t str_cmp(char* a, char* b);
char wrap_around_int(int32_t value);
char saturate_int(int32_t value);

/** Operaciones sobre strings**/

void shift_2(string_proc_key* key);
void unshift_2(string_proc_key* key);
void shift_position(string_proc_key* key);
void unshift_position(string_proc_key* key);
void duplicate_characters(string_proc_key* key);
void decimate_characters(string_proc_key* key);
void saturate_2(string_proc_key* key);
void unsaturate_2(string_proc_key* key);
void saturate_position(string_proc_key* key);
void unsaturate_position(string_proc_key* key);

#endif
