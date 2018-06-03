; FUNCIONES de C
	extern malloc
	extern free
	extern fopen
	extern fclose
	extern fprintf
	extern str_copy
	extern str_len

; /** defines bool y puntero **/
	%define NULL 0
	%define TRUE 1
	%define FALSE 0

; defines de tamanos y offsets
	%define stringProcListSize 24
	%define listName 0
	%define listFirst 8
	%define listLast 16
	
	%define stringProcNodeSize 33
	%define nodeNext 0
	%define nodePrevious 8
	%define nodeFuncF 16
	%define nodeFuncG 24
	%define nodeType 32

	%define stringProcKeySize 12
	%define keyLength 0
	%define keyValue 4

section .data


section .text

global string_proc_list_create
;string_proc_list* string_proc_list_create(char* name)
string_proc_list_create:				;char* name en RDI
	push rbp
	mov rbp, rsp

	mov rsi, rdi						;RSI <- *name

	push rsi							;desalineada, preparo llamada a Malloc
	sub rsp, 8							;alineada
	mov rdi, stringProcListSize
	call malloc
	add rsp, 8							;desalineada
	pop rsi								;alineada // RSI <- *name
	mov rcx, rax						;RCX <- valor devuelto por MALLOC

	push rsi							;desalineada, preparo llamado a Str_copy
	push rcx							;alineada
	mov rdi, rsi
	call str_copy					
	pop rcx								;desalineada
	pop rsi								;alineada

	mov rdx, rax						;RDX <- valor devuelto por str_copy
	mov rax, rcx						;RAX <- valor devuelto por malloc
	mov [rax + listName], rdx			;asigno valores
	mov qword [rax + listFirst], NULL
	mov qword [rax + listLast], NULL
	pop rbp
	ret

global string_proc_node_create
;string_proc_node* string_proc_node_create(string_proc_func f, string_proc_func g,
											;string_- proc_func_type type)
string_proc_node_create:			
	push rbp						;alineada
	mov rbp, rsp
	
	mov rcx, rdi					;rcx<-f
	push rcx						;desalineada
	push rsi						;alineada
	push rdx						;desalineada
	sub rsp, 8						;alineada
	mov rdi, stringProcNodeSize
	call malloc						;RAX <-malloc(rdi)
	add rsp, 8						;restauro pila
	pop rdx
	pop rsi
	pop rcx
	mov qword [rax + nodeNext], NULL		;asigno valores
	mov qword [rax + nodePrevious], NULL
	mov [rax + nodeFuncF], rcx
	mov [rax + nodeFuncG], rsi
	mov [rax + nodeType], dl

	pop rbp
	ret

global string_proc_key_create
;string_proc_key* string_proc_key_create(char* value)
string_proc_key_create:				;RDI<-*value
	push rbp
	mov rbp, rsp

	;MALLOC
	push rdi						;desalineada
	sub rsp, 8						;alineada
	mov rdi, stringProcKeySize
	call malloc
	add rsp, 8						;desalineada
	pop rdi							;alineada

	;STR_COPY
	push rax						;desalineada
	push rdi						;alineada
	call str_copy
	mov rbx, rax					;RBX<-puntero devuelto por strcopy
	pop rdi							;desalineada
	pop rax							;alineada RAX<-puntero devuelto por malloc
	
	;STR_LEN
	push rax						;preparo pila
	push rbx
	push rdi
	sub rsp, 8
	call str_len
	mov rcx, rax					;RCX<-str_len(value)
	add rsp, 8						;restauro
	pop rdi
	pop rbx
	pop rax

	mov [rax + keyLength], rcx		;asigno valores
	mov [rax + keyValue], rbx
	pop rbp
	ret

global string_proc_list_destroy
;void string_proc_list_destroy(string_proc_list* list);
string_proc_list_destroy:
	push rbp
	mov rbp, rsp										;alineada
	mov rsi, rdi										;RSI<-*list
	mov rdi, [rsi + listName]							;RDI<- list name
	push rsi
	sub rsp, 8
	call free											;borro name
	add rsp, 8
	pop rsi

	mov rdx, [rsi + listFirst]							;rsi<- primer item
	
	.ciclo:
		cmp qword rdx, NULL								;check lista vacia
		je .fin
		mov rcx, [rdx + nodeNext]						;avanzo nodo

		push rdi										;desalineada
		push rsi										;alineada
		push rdx										;desalineada
		push rcx										;alineada
		mov rdi, rdx									;nodo a borrar
		call string_proc_node_destroy
		pop rcx
		pop rdx
		pop rsi
		pop rdi
		mov rdx, rcx
		jmp .ciclo

	.fin:
	mov qword [rsi + listFirst], NULL					;pongo punteros en null
	mov qword [rsi + listLast], NULL
	mov rdi, rsi										;libero memoria de la lista
	call free
	pop rbp
	ret

global string_proc_node_destroy
;void string_proc_node_destroy(string_proc_node* node);
string_proc_node_destroy:
	push rbp
	mov rbp, rsp

	mov qword [rdi + nodeNext], NULL					;pointers -> null
	mov qword [rdi + nodePrevious], NULL
	mov qword [rdi + nodeFuncF], NULL
	mov qword [rdi + nodeFuncG], NULL

	call free								;en rdi ya esta el nodo, libero memoria

	pop rbp
	ret

global string_proc_key_destroy
;void string_proc_key_destroy(string_proc_key* key);
string_proc_key_destroy:
	push rbp
	mov rbp, rsp

	push rdi								;desalineada
	sub rsp, 8								;alineada
	mov rdi, [rdi + keyValue]				;ubico keyvalue a borrar
	call free
	add rsp, 8								;restauro pila
	pop rdi

	mov qword [rdi + keyValue], NULL		;actualizo valores
	mov qword [rdi + keyLength], NULL

	call free								;en rdi ya esta parametro para free

	pop rbp
	ret

global string_proc_list_add_node
;void string_proc_list_add_node(string_proc_list* list, string_proc_func f, string_proc_func g,
								;string_proc_func_type type);
string_proc_list_add_node:
	push rbp
	mov rbp, rsp						;alineada

	mov r8, rdi							;preparo registros para create_node
	mov rdi, rsi
	mov rsi, rdx
	mov rdx, rcx

	push r8								;desalineada
	push rdi							;alineada
	push rsi							;desalineada
	push rdx							;alineada
	call string_proc_node_create		;RAX<-node
	pop rdx								;desalineada
	pop rsi								;alineada
	pop rdi								;desalineada
	pop r8								;alineada

	cmp qword [r8 + listFirst], NULL	;chequeo si es lista vacia
	je .vacia

	mov r9, [r8 + listFirst]			;guardo primer y ultimo
	mov r10, [r8 + listLast]
	cmp r9, r10							;si son iguales hay un unico item
	je .unSoloElemento

	mov [r8 + listLast], rax			;actualizo valores
	mov [rax + nodePrevious], r10
	mov [r10 + nodeNext], rax
	jmp .final

	.vacia:
		mov [r8 + listFirst], rax
		mov [r8 + listLast], rax
		jmp .final
	
	.unSoloElemento:
		mov [r8 + listLast], rax
		mov [rax + nodePrevious], r9
		mov [r9 + nodeNext], rax
		jmp .final

	.final:
		pop rbp
		ret

global string_proc_list_apply
;void string_proc_list_apply(string_proc_list* list, string_proc_key* key, bool encode)
string_proc_list_apply:
	push rbp									;alineada
	mov rbp, rsp		
	mov r8, rdi									;R8<-*list
												;RSI<-*key
												;RDX<-encode
	cmp qword rdx, TRUE							;checkeo direccion
	je .forward
	.backwards:
		mov rcx, [r8 + listLast]
	.cicloBackwards:
		cmp qword rcx, NULL						;check final
		je .fin
		mov rdi, rsi
		push rdi								;desalineada
		push rsi								;alineada
		push rdx								;desalineada
		push rcx								;alineada
		push r8									;desalineada
		sub rsp, 8								;alineada
		call [rcx + nodeFuncG]					;llamado a g
		add rsp, 8
		pop r8
		pop rcx
		pop rdx
		pop rsi
		pop rdi
		mov rcx, [rcx + nodePrevious]			;actualizo nodo
		jmp .cicloBackwards	

	.forward:
		mov rcx, [r8 + listFirst]
	.cicloForward:
		cmp qword rcx, NULL						;check final
		je .fin
		mov rdi, rsi
		push rdi								;desalineada
		push rsi								;alineada
		push rdx								;desalineada
		push rcx								;alineada
		push r8									;desalineada
		sub rsp, 8								;alineada
		call [rcx + nodeFuncF]					;llamado a f
		add rsp, 8
		pop r8
		pop rcx
		pop rdx
		pop rsi
		pop rdi
		mov rcx, [rcx + nodeNext]				;avanzo nodo
		jmp .cicloForward

	.fin:
	pop rbp
	ret
