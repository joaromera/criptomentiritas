#include <stdbool.h>
#include <stdio.h>
#include "string_processor.h"
#include "string_processor_utils.h"

//TODO: debe implementar
/**
*	Debe devolver el largo de la lista pasada por parámetro
*/
uint32_t string_proc_list_length(string_proc_list* list){
    uint32_t length = 0;
    if (list->first != NULL) length++;

    string_proc_node* actual = list->first;
    while (actual != NULL && actual != list->last) {
        length++;
        actual = actual->next;
    }
    return length;
}

//TODO: debe implementar
/**
*	Debe insertar el nodo con los parámetros correspondientes en la posición indicada por index desplazando en una
*	posición hacia adelante los nodos sucesivos en caso de ser necesario, la estructura de la lista debe ser
*	actualizada de forma acorde
*	si index es igual al largo de la lista debe insertarlo al final de la misma
*	si index es mayor al largo de la lista no debe insertar el nodo
*	debe devolver true si el nodo pudo ser insertado en la lista, false en caso contrario
*/
bool string_proc_list_add_node_at(string_proc_list* list, string_proc_func f, string_proc_func g, string_proc_func_type type, uint32_t index){
	uint32_t length = string_proc_list_length(list);
	if (index > length) return false;
    if (index == length) {          //insertar al final
        string_proc_list_add_node(list, f, g, type);
        return true;
    }
    
    string_proc_node* node	= malloc(sizeof(string_proc_node));
	node->next				= NULL;
	node->previous			= NULL;
	node->f					= f;
	node->g					= g;
	node->type				= type;

    if (index == 0 && length > 0) { //caso: insertar en primera posicion en una lista con length>=1 
        node->next = list->first;
        list->first = node;
        node->next->previous = node;
        return true;
    }

    string_proc_node* anterior = list->first;
    string_proc_node* actual = anterior->next;
    index--;
    
    while (index > 0) {             //inserto dentro de la lista, ni primero ni ultimo
        index--;
        anterior = actual;
        actual = actual->next;
    }
    anterior->next = node;
    actual->previous = node;
    node->next = actual;
    node->previous = anterior;
    return true;
}

//TODO: debe implementar
/**
*	Debe eliminar el nodo que se encuentra en la posición indicada por index de ser posible
*	la lista debe ser actualizada de forma acorde y debe devolver true si pudo eliminar el nodo o false en caso contrario
*/
bool string_proc_list_remove_node_at(string_proc_list* list, uint32_t index){
    uint32_t length = string_proc_list_length(list);
	if (index >= length) return false;

    string_proc_node* erased = NULL;
    if (index == 0) {
        erased = list->first;
        if (length == 1) {
            list->first = NULL;    
        } else {
            string_proc_node* newFirst = erased->next;
            list->first = newFirst;
            newFirst->previous = NULL;    
        }
    } else if (index == length - 1) {
        erased = list->last;
        string_proc_node* newLast = erased->previous;
        list->last = newLast;
        newLast->next = NULL;
    } else {
        string_proc_node* anterior = list->first;
        erased = anterior->next;
        index--;
        while (index > 0) {
            anterior = erased;
            erased = erased->next;
            index--;
        }
        anterior->next = erased->next;
        erased->next->previous = anterior;
    }
    free(erased);
    return true;
}

//TODO: debe implementar
/**
*	Debe devolver una copia de la lista pasada por parámetro copiando los nodos en el orden inverso
*/
string_proc_list* string_proc_list_invert_order(string_proc_list* list){
    string_proc_list* invertedList = string_proc_list_create(list->name);
    uint32_t length = string_proc_list_length(list);
    string_proc_node* actual = list->last;
    for (unsigned int i = 0; i < length; i++){
        string_proc_list_add_node(invertedList, actual->f, actual->g, actual->type);
        actual = actual->previous;
    }
    return invertedList;
}

//TODO: debe implementar
/**
*	Hace una llamada sucesiva a los nodos de la lista pasada por parámetro siguiendo la misma lógica
*	que string_proc_list_apply pero comienza imprimiendo una línea 
*	"Encoding key 'valor_de_la_clave' through list nombre_de_la_list\n"
* 	y luego por cada aplicación de una función f o g escribe 
*	"Applying function at [direccion_de_funcion] to get 'valor_de_la_clave'\n"
*/
void string_proc_list_apply_print_trace(string_proc_list* list, string_proc_key* key, bool encode, FILE* file){
    printf("Encoding key '%s' through list %s\n", key->value, list->name);   

    if(encode){
		string_proc_node* current_node	= list->first;
		while(current_node != NULL){
			current_node->f(key);
            printf("Applying function at [0x%X] to get '%s'\n", current_node->f, key->value);
			current_node = current_node->next;
		}
	}else{
		string_proc_node* current_node	= list->last;
		while(current_node != NULL){
			current_node->g(key);
            printf("Applying function at [0x%X] to get '%s'\n", current_node->g, key->value);
			current_node = current_node->previous;
		}
	}
}

//TODO: debe implementar
/**
*	Debe desplazar en dos posiciones hacia adelante el valor de cada caracter de la clave pasada por parámetro
*	si el mismo se encuentra en una posición impar, resolviendo los excesos de representación por saturación
*/
void saturate_2_odd(string_proc_key* key){
	uint32_t i;
	for(i = 0; i < key->length; i++){
        if (i % 2 == 1) key->value[i] = saturate_int(((int32_t)key->value[i]) + 2);
	}
}

//TODO: debe implementar
/**
*	Debe desplazar en dos posiciones hacia atrás el valor de cada caracter de la clave pasada por parámetro
*	si el mismo se encuentra en una posición impar, resolviendo los excesos de representación por saturación
*/
void unsaturate_2_odd(string_proc_key* key){
    uint32_t i;
	for(i = 0; i < key->length; i++){
        if (i % 2 == 1) key->value[i] = saturate_int(((int32_t)key->value[i]) - 2);
	}
}

bool isPrime(unsigned int n){
    if (n == 0 || n == 1) return false;
    
    unsigned int i;
    for (i = 2; i*i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

//TODO: debe implementar
/**
*	Debe desplazar en tantas posiciones como sea la posición hacia adelante del valor de cada caracter de la clave pasada por parámetro
*	si el mismo se encuentra en una posición que sea un número primo, resolviendo los excesos de representación con wrap around
*/
void shift_position_prime(string_proc_key* key){
	uint32_t i;
	for(i = 0; i < key->length; i++){
        if (isPrime(i)) key->value[i] = wrap_around_int(((int32_t)key->value[i]) + i);
	}
}

//TODO: debe implementar
/**
*	Debe desplazar en tantas posiciones como sea la posición hacia atrás del valor de cada caracter de la clave pasada por parámetro
*	si el mismo se encuentra en una posición que sea un número primo, resolviendo los excesos de representación con wrap around
*/
void unshift_position_prime(string_proc_key* key){
 	uint32_t i;
	for(i = 0; i < key->length; i++){
        if (isPrime(i)) key->value[i] = wrap_around_int(((int32_t)key->value[i]) - i);
	}   
}
