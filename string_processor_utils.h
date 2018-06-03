#ifndef STRING_PROC_UTILS_H
#define STRING_PROC_UTILS_H
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "string_processor.h"

uint32_t string_proc_list_length(string_proc_list* list);
bool string_proc_list_add_node_at(string_proc_list* list, string_proc_func f, string_proc_func g, string_proc_func_type type, uint32_t index);
bool string_proc_list_remove_node_at(string_proc_list* list, uint32_t index);
string_proc_list* string_proc_list_invert_order(string_proc_list* list);
void string_proc_list_apply_print_trace(string_proc_list* list, string_proc_key* key, bool encode, FILE* file);

void saturate_2_odd(string_proc_key* key);
void unsaturate_2_odd(string_proc_key* key);
void shift_position_prime(string_proc_key* key);
void unshift_position_prime(string_proc_key* key);

#endif
