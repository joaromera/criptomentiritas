#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "string_processor.h"
#include "string_processor_utils.h"

#define FILE_OP(filename, x) pFile = fopen ( filename, "a" ); x fclose( pFile );
#define TEST_N	300

char *filename_1 =  "salida.caso1.txt";
char *filename_2 =  "salida.caso2.txt";
char *filename_N =  "salida.casoN.txt";
void test_1_element();
void test_2_elements();
void test_N_elements();

int main() {
	srand(20140831);
	remove(filename_1);
	test_1_element();
	remove(filename_2);
	test_2_elements();
	remove(filename_N);
	test_N_elements();  
	return 0;
}

void test_1_element(){
	FILE *pFile; 
	FILE_OP(filename_1,fputs( ">>>>>>>>>>>>>>>> PROBANDO LISTA 1 ELEMENTO\n", pFile );)
	string_proc_list *list = string_proc_list_create("lista_test_1");
	FILE_OP(filename_1,string_proc_list_print(list, pFile);)
	string_proc_list_destroy(list);
	FILE_OP(filename_1,fputs( ">>>>>>>>>>>>>>>> LISTA 1 DESTRUIDA\n", pFile );)
	FILE_OP(filename_1,fputs( ">>>>>>>>>>>>>>>> PROBANDO LISTA 1 ELEMENTO 1 NODO \n", pFile );)
	list = string_proc_list_create("lista_test_1_1_node");
	string_proc_list_add_node(list, shift_2, unshift_2, REVERSIBLE);
	FILE_OP(filename_1,string_proc_list_print(list, pFile);)
	string_proc_list_destroy(list);
	FILE_OP(filename_1,fputs( ">>>>>>>>>>>>>>>> LISTA 1 DESTRUIDA\n", pFile );)
	FILE_OP(filename_1,fputs( ">>>>>>>>>>>>>>>> PROBANDO NODO \n", pFile );)
	string_proc_node* node = string_proc_node_create(shift_2, unshift_2, REVERSIBLE);
	string_proc_node_destroy(node);
	FILE_OP(filename_1,fputs( ">>>>>>>>>>>>>>>> NODO DESTRUIDO\n", pFile );)
	FILE_OP(filename_1,fputs( ">>>>>>>>>>>>>>>> PROBANDO CLAVE \n", pFile );)
	string_proc_key* key = string_proc_key_create("hola mundo");
	string_proc_key_destroy(key);
	FILE_OP(filename_1,fputs( ">>>>>>>>>>>>>>>> CLAVE DESTRUIDA\n", pFile );)
	FILE_OP(filename_1,fputs( ">>>>>>>>>>>>>>>> PROBANDO STR_LEN \n", pFile );)
	FILE_OP(filename_1,fprintf(pFile, "%d\n", str_len("largo a probar")+1);)
	FILE_OP(filename_1,fputs( ">>>>>>>>>>>>>>>> PROBANDO STR_COPY / STR_CMP\n", pFile );)
	char* copy	= str_copy("largo a probar");
	FILE_OP(filename_1,fprintf(pFile, "%s\n", str_cmp("largo a probar", copy) == 0 ? "OK" : "NOK");)
	free(copy);
	FILE_OP(filename_1,fprintf(pFile, "%s\n", str_cmp("largo a probar", "largo a probar") == 0 ? "OK" : "NOK");)
	FILE_OP(filename_1,fprintf(pFile, "%s\n", str_cmp("abcd", "bbcd") == 1 ? "OK" : "NOK");)
	FILE_OP(filename_1,fprintf(pFile, "%s\n", str_cmp("bbcde", "bbcdf") == 1 ? "OK" : "NOK");)
	FILE_OP(filename_1,fprintf(pFile, "%s\n", str_cmp("cbcde", "bbcdf") == -1 ? "OK" : "NOK");)
	FILE_OP(filename_1,fputs( ">>>>>>>>>>>>>>>> PROBANDO OPERACIONES\n", pFile );)	
	key = string_proc_key_create("hemos ido demasiado lejos y se acerca la hora de detenernos a reflexionar sobre los tests");
	FILE_OP(filename_1,shift_2(key); fprintf(pFile, "shift_2:%s\n", key->value);)
	string_proc_key_destroy(key);
	key = string_proc_key_create("hemos ido demasiado lejos y se acerca la hora de detenernos a reflexionar sobre los tests");
	FILE_OP(filename_1,unshift_2(key); fprintf(pFile, "unshift_2:%s\n", key->value);)
	string_proc_key_destroy(key);
	key = string_proc_key_create("hemos ido demasiado lejos y se acerca la hora de detenernos a reflexionar sobre los tests");
	FILE_OP(filename_1,shift_position(key); fprintf(pFile, "shift_position:%s\n", key->value);)
	string_proc_key_destroy(key);
	key = string_proc_key_create("hemos ido demasiado lejos y se acerca la hora de detenernos a reflexionar sobre los tests");
	FILE_OP(filename_1,shift_position(key); fprintf(pFile, "unshift_position:%s\n", key->value);)
	string_proc_key_destroy(key);
	key = string_proc_key_create("hemos ido demasiado lejos y se acerca la hora de detenernos a reflexionar sobre los tests");
	FILE_OP(filename_1,saturate_2(key); fprintf(pFile, "saturate_2:%s\n", key->value);)
	string_proc_key_destroy(key);
	key = string_proc_key_create("hemos ido demasiado lejos y se acerca la hora de detenernos a reflexionar sobre los tests");
	FILE_OP(filename_1,unsaturate_2(key); fprintf(pFile, "unsaturate_2:%s\n", key->value);)
	string_proc_key_destroy(key);
	key = string_proc_key_create("hemos ido demasiado lejos y se acerca la hora de detenernos a reflexionar sobre los tests");
	FILE_OP(filename_1,saturate_position(key); fprintf(pFile, "saturate_position:%s\n", key->value);)
	string_proc_key_destroy(key);
	key = string_proc_key_create("hemos ido demasiado lejos y se acerca la hora de detenernos a reflexionar sobre los tests");
	FILE_OP(filename_1,unsaturate_position(key); fprintf(pFile, "unsaturate_position:%s\n", key->value);)
	string_proc_key_destroy(key);
	FILE_OP(filename_1,fputs( ">>>>>>>>>>>>>>>> PROBANDO ENCODE DECODE\n", pFile );)
	list = string_proc_list_create("lista_test_2");
	string_proc_list_add_node(list, shift_2, unshift_2, REVERSIBLE);
	FILE_OP(filename_1,fputs( "Encode:", pFile );)
	FILE_OP(filename_1,string_proc_list_encode(list, "hemos ido demasiado lejos y se acerca la hora de detenernos a reflexionar sobre los tests", pFile);)
	FILE_OP(filename_1,fputs( "\nDecode:", pFile );)
	FILE_OP(filename_1,string_proc_list_decode(list, "hemos ido demasiado lejos y se acerca la hora de detenernos a reflexionar sobre los tests", pFile);)
	FILE_OP(filename_1,fputs( "\n", pFile );)
	string_proc_list_destroy(list);
	FILE_OP(filename_1,fputs( ">>>>>>>>>>>>>>>> PROBANDO FILTER_BY_TYPE\n", pFile );)
	list = string_proc_list_create("lista_test_2");
	string_proc_list_add_node(list, shift_2, unshift_2, REVERSIBLE);
	string_proc_list_add_node(list, saturate_2, saturate_2, IRREVERSIBLE);
	FILE_OP(filename_1,fputs( "Encode:", pFile );)
	FILE_OP(filename_1,string_proc_list_encode(list, "hemos ido demasiado lejos y se acerca la hora de detenernos a reflexionar sobre los tests", pFile);)
	FILE_OP(filename_1,fputs( "\nDecode:", pFile );)
	FILE_OP(filename_1,string_proc_list_decode(list, "hemos ido demasiado lejos y se acerca la hora de detenernos a reflexionar sobre los tests", pFile);)
	FILE_OP(filename_1,fputs( "\n", pFile );)
	FILE_OP(filename_1,fputs( ">>>>>>>>>>>>>>>> FILTRANDO\n", pFile );)
	string_proc_list *filtered_list	= string_proc_list_filter_by_type(list, REVERSIBLE);
	FILE_OP(filename_1,fputs( "Encode:", pFile );)
	FILE_OP(filename_1,string_proc_list_encode(filtered_list, "hemos ido demasiado lejos y se acerca la hora de detenernos a reflexionar sobre los tests", pFile);)
	FILE_OP(filename_1,fputs( "\nDecode:", pFile );)
	FILE_OP(filename_1,string_proc_list_decode(filtered_list, "hemos ido demasiado lejos y se acerca la hora de detenernos a reflexionar sobre los tests", pFile);)
	FILE_OP(filename_1,fputs( "\n", pFile );)
	string_proc_list_destroy(filtered_list);
	string_proc_list_destroy(list);
	FILE_OP(filename_1,fputs( ">>>>>>>>>>>>>>>> PROBANDO INVERT\n", pFile );)
	list = string_proc_list_create("lista_test_2");
	string_proc_list_add_node(list, shift_2, unshift_2, REVERSIBLE);
	string_proc_list_add_node(list, saturate_2, saturate_2, IRREVERSIBLE);
	FILE_OP(filename_1,fputs( "Encode:", pFile );)
	FILE_OP(filename_1,string_proc_list_encode(list, "hemos ido demasiado lejos y se acerca la hora de detenernos a reflexionar sobre los tests", pFile);)
	FILE_OP(filename_1,fputs( "\nDecode:", pFile );)
	FILE_OP(filename_1,string_proc_list_decode(list, "hemos ido demasiado lejos y se acerca la hora de detenernos a reflexionar sobre los tests", pFile);)
	FILE_OP(filename_1,fputs( "\n", pFile );)
	FILE_OP(filename_1,fputs( ">>>>>>>>>>>>>>>> INVIRTIENDO\n", pFile );)
	string_proc_list *inverted_list	= string_proc_list_invert(list);
	FILE_OP(filename_1,fputs( "Encode:", pFile );)
	FILE_OP(filename_1,string_proc_list_encode(inverted_list, "hemos ido demasiado lejos y se acerca la hora de detenernos a reflexionar sobre los tests", pFile);)
	FILE_OP(filename_1,fputs( "\nDecode:", pFile );)
	FILE_OP(filename_1,string_proc_list_decode(inverted_list, "hemos ido demasiado lejos y se acerca la hora de detenernos a reflexionar sobre los tests", pFile);)
	FILE_OP(filename_1,fputs( "\n", pFile );)
	string_proc_list_destroy(inverted_list);
	string_proc_list_destroy(list);
	FILE_OP(filename_1,fputs( ">>>>>>>>>>>>>>>> PROBANDO LENGTH\n", pFile );)
	list = string_proc_list_create("lista_test_length");
	FILE_OP(filename_1,fprintf(pFile, "%d\n", string_proc_list_length(list));)
	string_proc_list_add_node(list, shift_2, unshift_2, REVERSIBLE);
	string_proc_list_add_node(list, saturate_2, saturate_2, IRREVERSIBLE);
	FILE_OP(filename_1,fprintf(pFile, "%d\n", string_proc_list_length(list));)
	string_proc_list_add_node(list, shift_2, unshift_2, REVERSIBLE);
	string_proc_list_add_node(list, saturate_2, saturate_2, IRREVERSIBLE);
	FILE_OP(filename_1,fprintf(pFile, "%d\n", string_proc_list_length(list));)
	string_proc_list_add_node(list, shift_2, unshift_2, REVERSIBLE);
	string_proc_list_add_node(list, saturate_2, saturate_2, IRREVERSIBLE);
	FILE_OP(filename_1,fprintf(pFile, "%d\n", string_proc_list_length(list));)	
	string_proc_list_destroy(list);
	FILE_OP(filename_1,fputs( ">>>>>>>>>>>>>>>> PROBANDO ADD NODE AT\n", pFile );)
	list = string_proc_list_create("lista_test_add_node");
	string_proc_list_add_node(list, shift_2, unshift_2, REVERSIBLE);
	string_proc_list_add_node(list, saturate_2, saturate_2, IRREVERSIBLE);
	string_proc_list_add_node_at(list, saturate_2, saturate_2, IRREVERSIBLE, 0);
	FILE_OP(filename_1,string_proc_list_print(list, pFile);)
	string_proc_list_add_node_at(list, saturate_2, saturate_2, IRREVERSIBLE, 3);
	FILE_OP(filename_1,string_proc_list_print(list, pFile);)
	string_proc_list_add_node_at(list, saturate_2, saturate_2, IRREVERSIBLE, 6);
	FILE_OP(filename_1,string_proc_list_print(list, pFile);)
	string_proc_list_destroy(list);
	FILE_OP(filename_1,fputs( ">>>>>>>>>>>>>>>> PROBANDO REMOVE NODE AT\n", pFile );)
	list = string_proc_list_create("lista_remove_node");
	string_proc_list_add_node(list, shift_2, unshift_2, REVERSIBLE);
	string_proc_list_add_node(list, saturate_2, saturate_2, IRREVERSIBLE);
	string_proc_list_add_node_at(list, saturate_2, saturate_2, IRREVERSIBLE, 0);
	string_proc_list_add_node_at(list, saturate_2, saturate_2, IRREVERSIBLE, 3);
	string_proc_list_remove_node_at(list, 3);
	FILE_OP(filename_1,string_proc_list_print(list, pFile);)
	string_proc_list_remove_node_at(list, 0);
	FILE_OP(filename_1,string_proc_list_print(list, pFile);)
	string_proc_list_remove_node_at(list, 1);
	FILE_OP(filename_1,string_proc_list_print(list, pFile);)
	string_proc_list_destroy(list);
	FILE_OP(filename_1,fputs( ">>>>>>>>>>>>>>>> PROBANDO INVERT ORDER\n", pFile );)
	list = string_proc_list_create("lista_invert_order");
	string_proc_list_add_node(list, shift_2, unshift_2, REVERSIBLE);
	string_proc_list_add_node(list, saturate_2, saturate_2, IRREVERSIBLE);
	string_proc_list_add_node(list, unshift_2, shift_2, REVERSIBLE);
	string_proc_list_add_node(list, saturate_2, saturate_2, IRREVERSIBLE);
	FILE_OP(filename_1,string_proc_list_print(list, pFile);)
	string_proc_list* inverted_order_list	= string_proc_list_invert_order(list);
	FILE_OP(filename_1,string_proc_list_print(list, pFile);)
	string_proc_list_destroy(inverted_order_list);
	string_proc_list_destroy(list);
	FILE_OP(filename_1,fputs( ">>>>>>>>>>>>>>>> PROBANDO ODD PRIME\n", pFile );)
	list = string_proc_list_create("lista_odd_prime");
	string_proc_list_add_node(list, saturate_2_odd, unsaturate_2_odd, IRREVERSIBLE);
	FILE_OP(filename_1,fputs( "Encode:", pFile );)
	FILE_OP(filename_1,string_proc_list_encode(list, "hemos ido demasiado lejos y se acerca la hora de detenernos a reflexionar sobre los tests", pFile);)
	FILE_OP(filename_1,fputs( "\nDecode:", pFile );)
	FILE_OP(filename_1,string_proc_list_decode(list, "hemos ido demasiado lejos y se acerca la hora de detenernos a reflexionar sobre los tests", pFile);)
	string_proc_list_destroy(list);
	list = string_proc_list_create("lista_odd_prime");
	string_proc_list_add_node(list, shift_position_prime, unshift_position_prime, REVERSIBLE);
	FILE_OP(filename_1,fputs( "\nEncode:", pFile );)
	FILE_OP(filename_1,string_proc_list_encode(list, "hemos ido demasiado lejos y se acerca la hora de detenernos a reflexionar sobre los tests", pFile);)
	FILE_OP(filename_1,fputs( "\nDecode:", pFile );)
	FILE_OP(filename_1,string_proc_list_decode(list, "hemos ido demasiado lejos y se acerca la hora de detenernos a reflexionar sobre los tests", pFile);)
	FILE_OP(filename_1,fputs( "\n", pFile );)
	string_proc_list_destroy(list);
}

void test_2_elements(){
	FILE *pFile; 
	FILE_OP(filename_2,fputs( ">>>>>>>>>>>>>>>> PROBANDO APPLY\n", pFile );)
	string_proc_list *list = string_proc_list_create("lista_test_2");
	string_proc_list_add_node(list, shift_2, unshift_2, REVERSIBLE);
	string_proc_list_add_node(list, shift_position, unshift_position, REVERSIBLE);
	string_proc_key *key = string_proc_key_create("hemos ido demasiado lejos y se acerca la hora de detenernos a reflexionar sobre los tests");
	FILE_OP(filename_2,string_proc_list_apply(list, key, true);)
	FILE_OP(filename_2,fprintf( pFile, "Encode:%s\n", key->value );)
	string_proc_key_destroy(key);
	key = string_proc_key_create("hemos ido demasiado lejos y se acerca la hora de detenernos a reflexionar sobre los tests");
	FILE_OP(filename_2,string_proc_list_apply(list, key, false);)
	FILE_OP(filename_2,fprintf( pFile, "Decode:%s\n", key->value );)
	string_proc_key_destroy(key);
	string_proc_list_destroy(list);
	FILE_OP(filename_2,fputs( ">>>>>>>>>>>>>>>> PROBANDO ENCODE DECODE\n", pFile );)
	list = string_proc_list_create("lista_test_2");
	string_proc_list_add_node(list, shift_2, unshift_2, REVERSIBLE);
	string_proc_list_add_node(list, shift_position, unshift_position, REVERSIBLE);
	FILE_OP(filename_2,fputs( "Encode:", pFile );)
	FILE_OP(filename_2,string_proc_list_encode(list, "hemos ido demasiado lejos y se acerca la hora de detenernos a reflexionar sobre los tests", pFile);)
	FILE_OP(filename_2,fputs( "\nDecode:", pFile );)
	FILE_OP(filename_2,string_proc_list_decode(list, "hemos ido demasiado lejos y se acerca la hora de detenernos a reflexionar sobre los tests", pFile);)
	FILE_OP(filename_2,fputs( "\n", pFile );)
	string_proc_list_destroy(list);
	FILE_OP(filename_2,fputs( ">>>>>>>>>>>>>>>> PROBANDO FILTER_BY_TYPE\n", pFile );)
	list = string_proc_list_create("lista_test_2");
	string_proc_list_add_node(list, shift_2, unshift_2, REVERSIBLE);
	string_proc_list_add_node(list, shift_position, unshift_position, REVERSIBLE);
	string_proc_list_add_node(list, saturate_2, saturate_2, IRREVERSIBLE);
	FILE_OP(filename_2,fputs( "Encode:", pFile );)
	FILE_OP(filename_2,string_proc_list_encode(list, "hemos ido demasiado lejos y se acerca la hora de detenernos a reflexionar sobre los tests", pFile);)
	FILE_OP(filename_2,fputs( "\nDecode:", pFile );)
	FILE_OP(filename_2,string_proc_list_decode(list, "hemos ido demasiado lejos y se acerca la hora de detenernos a reflexionar sobre los tests", pFile);)
	FILE_OP(filename_2,fputs( "\n", pFile );)
	FILE_OP(filename_2,fputs( ">>>>>>>>>>>>>>>> FILTRANDO\n", pFile );)
	string_proc_list *filtered_list	= string_proc_list_filter_by_type(list, REVERSIBLE);
	FILE_OP(filename_2,fputs( "Encode:", pFile );)
	FILE_OP(filename_2,string_proc_list_encode(filtered_list, "hemos ido demasiado lejos y se acerca la hora de detenernos a reflexionar sobre los tests", pFile);)
	FILE_OP(filename_2,fputs( "\nDecode:", pFile );)
	FILE_OP(filename_2,string_proc_list_decode(filtered_list, "hemos ido demasiado lejos y se acerca la hora de detenernos a reflexionar sobre los tests", pFile);)
	FILE_OP(filename_2,fputs( "\n", pFile );)
	string_proc_list_destroy(filtered_list);
	string_proc_list_destroy(list);
	FILE_OP(filename_2,fputs( ">>>>>>>>>>>>>>>> PROBANDO INVERT\n", pFile );)
	list = string_proc_list_create("lista_test_2");
	string_proc_list_add_node(list, shift_2, unshift_2, REVERSIBLE);
	string_proc_list_add_node(list, shift_position, unshift_position, REVERSIBLE);
	string_proc_list_add_node(list, saturate_2, saturate_2, IRREVERSIBLE);
	FILE_OP(filename_2,fputs( "Encode:", pFile );)
	FILE_OP(filename_2,string_proc_list_encode(list, "hemos ido demasiado lejos y se acerca la hora de detenernos a reflexionar sobre los tests", pFile);)
	FILE_OP(filename_2,fputs( "\nDecode:", pFile );)
	FILE_OP(filename_2,string_proc_list_decode(list, "hemos ido demasiado lejos y se acerca la hora de detenernos a reflexionar sobre los tests", pFile);)
	FILE_OP(filename_2,fputs( "\n", pFile );)
	FILE_OP(filename_2,fputs( ">>>>>>>>>>>>>>>> INVIRTIENDO\n", pFile );)
	string_proc_list *inverted_list	= string_proc_list_invert(list);
	FILE_OP(filename_2,fputs( "Encode:", pFile );)
	FILE_OP(filename_2,string_proc_list_encode(inverted_list, "hemos ido demasiado lejos y se acerca la hora de detenernos a reflexionar sobre los tests", pFile);)
	FILE_OP(filename_2,fputs( "\nDecode:", pFile );)
	FILE_OP(filename_2,string_proc_list_decode(inverted_list, "hemos ido demasiado lejos y se acerca la hora de detenernos a reflexionar sobre los tests", pFile);)
	FILE_OP(filename_2,fputs( "\n", pFile );)
	string_proc_list_destroy(inverted_list);
	string_proc_list_destroy(list);
}
void test_N_elements(){
	FILE *pFile; uint32_t i;
	FILE_OP(filename_N,fputs( ">>>>>>>>>>>>>>>> PROBANDO APPLY\n", pFile );)
	string_proc_list *list = string_proc_list_create("lista_test_2");
	for(i = 0; i < TEST_N; i++){
		string_proc_list_add_node(list, shift_2, unshift_2, REVERSIBLE);
		string_proc_list_add_node(list, shift_position, unshift_position, REVERSIBLE);
	}
	string_proc_key *key = string_proc_key_create("hemos ido demasiado lejos y se acerca la hora de detenernos a reflexionar sobre los tests");
	FILE_OP(filename_N,string_proc_list_apply(list, key, true);)
	FILE_OP(filename_N,fprintf( pFile, "Encode:%s\n", key->value );)
	string_proc_key_destroy(key);
	key = string_proc_key_create("hemos ido demasiado lejos y se acerca la hora de detenernos a reflexionar sobre los tests");
	FILE_OP(filename_N,string_proc_list_apply(list, key, false);)
	FILE_OP(filename_N,fprintf( pFile, "Decode:%s\n", key->value );)
	string_proc_key_destroy(key);
	string_proc_list_destroy(list);
	FILE_OP(filename_N,fputs( ">>>>>>>>>>>>>>>> PROBANDO ENCODE DECODE\n", pFile );)
	list = string_proc_list_create("lista_test_2");
	for(i = 0; i < TEST_N; i++){
		string_proc_list_add_node(list, shift_2, unshift_2, REVERSIBLE);
		string_proc_list_add_node(list, shift_position, unshift_position, REVERSIBLE);
	}
	FILE_OP(filename_N,fputs( "Encode:", pFile );)
	FILE_OP(filename_N,string_proc_list_encode(list, "hemos ido demasiado lejos y se acerca la hora de detenernos a reflexionar sobre los tests", pFile);)
	FILE_OP(filename_N,fputs( "\nDecode:", pFile );)
	FILE_OP(filename_N,string_proc_list_decode(list, "hemos ido demasiado lejos y se acerca la hora de detenernos a reflexionar sobre los tests", pFile);)
	FILE_OP(filename_N,fputs( "\n", pFile );)
	string_proc_list_destroy(list);
	FILE_OP(filename_N,fputs( ">>>>>>>>>>>>>>>> PROBANDO FILTER_BY_TYPE\n", pFile );)
	list = string_proc_list_create("lista_test_2");
	for(i = 0; i < TEST_N; i++){
		string_proc_list_add_node(list, shift_2, unshift_2, REVERSIBLE);
		string_proc_list_add_node(list, shift_position, unshift_position, REVERSIBLE);
		string_proc_list_add_node(list, saturate_2, saturate_2, IRREVERSIBLE);
	}
	FILE_OP(filename_N,fputs( "Encode:", pFile );)
	FILE_OP(filename_N,string_proc_list_encode(list, "hemos ido demasiado lejos y se acerca la hora de detenernos a reflexionar sobre los tests", pFile);)
	FILE_OP(filename_N,fputs( "\nDecode:", pFile );)
	FILE_OP(filename_N,string_proc_list_decode(list, "hemos ido demasiado lejos y se acerca la hora de detenernos a reflexionar sobre los tests", pFile);)
	FILE_OP(filename_N,fputs( "\n", pFile );)
	FILE_OP(filename_N,fputs( ">>>>>>>>>>>>>>>> FILTRANDO\n", pFile );)
	string_proc_list *filtered_list	= string_proc_list_filter_by_type(list, REVERSIBLE);
	FILE_OP(filename_N,fputs( "Encode:", pFile );)
	FILE_OP(filename_N,string_proc_list_encode(filtered_list, "hemos ido demasiado lejos y se acerca la hora de detenernos a reflexionar sobre los tests", pFile);)
	FILE_OP(filename_N,fputs( "\nDecode:", pFile );)
	FILE_OP(filename_N,string_proc_list_decode(filtered_list, "hemos ido demasiado lejos y se acerca la hora de detenernos a reflexionar sobre los tests", pFile);)
	FILE_OP(filename_N,fputs( "\n", pFile );)
	string_proc_list_destroy(filtered_list);
	string_proc_list_destroy(list);
	FILE_OP(filename_N,fputs( ">>>>>>>>>>>>>>>> PROBANDO INVERT\n", pFile );)
	list = string_proc_list_create("lista_test_2");
	string_proc_list_add_node(list, shift_2, unshift_2, REVERSIBLE);
	string_proc_list_add_node(list, shift_position, unshift_position, REVERSIBLE);
	string_proc_list_add_node(list, saturate_2, saturate_2, IRREVERSIBLE);
	FILE_OP(filename_N,fputs( "Encode:", pFile );)
	FILE_OP(filename_N,string_proc_list_encode(list, "hemos ido demasiado lejos y se acerca la hora de detenernos a reflexionar sobre los tests", pFile);)
	FILE_OP(filename_N,fputs( "\nDecode:", pFile );)
	FILE_OP(filename_N,string_proc_list_decode(list, "hemos ido demasiado lejos y se acerca la hora de detenernos a reflexionar sobre los tests", pFile);)
	FILE_OP(filename_N,fputs( "\n", pFile );)
	FILE_OP(filename_N,fputs( ">>>>>>>>>>>>>>>> INVIRTIENDO\n", pFile );)
	string_proc_list *inverted_list	= string_proc_list_invert(list);
	FILE_OP(filename_N,fputs( "Encode:", pFile );)
	FILE_OP(filename_N,string_proc_list_encode(inverted_list, "hemos ido demasiado lejos y se acerca la hora de detenernos a reflexionar sobre los tests", pFile);)
	FILE_OP(filename_N,fputs( "\nDecode:", pFile );)
	FILE_OP(filename_N,string_proc_list_decode(inverted_list, "hemos ido demasiado lejos y se acerca la hora de detenernos a reflexionar sobre los tests", pFile);)
	FILE_OP(filename_N,fputs( "\n", pFile );)
	string_proc_list_destroy(inverted_list);
	string_proc_list_destroy(list);
}

