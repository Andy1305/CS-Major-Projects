%include "io.inc"


extern puts


section .data
    %include "input.inc"

    
    error_message: db "Baza incorecta", 0


section .text
global CMAIN
CMAIN:
    mov ebp, esp

    xor eax, eax
    xor ebx, ebx
    
    mov eax, [numar]
    mov ebx, [baza]
    mov ecx, 0
    
    cmp ebx, 2
    jl error

    cmp ebx, 16
    jg error


divide_again:   
    xor edx, edx 
    div ebx
    push edx
    inc ecx	                                 ;Numar de cate ori se imparte numarul, ca sa stiu de cate ori scot din stiva si afisez.
    cmp eax, 0
    jnz divide_again	                         ;Continui sa impart pana cand numarul este 0.
    jz print_converted_number	                 ;Cand numarul e 0, incep afisarea.
    
    
error:                                           ;Afisez mesajul de eroare.
    lea eax, [error_message]

    push eax
    call puts
    pop eax
   
    ret
 
       
print_converted_number:
    pop eax
    cmp eax, 10                                 ;Verifica daca restul e mai mare ca 10, implicit daca baza e mai mare ca 10.
    jns print_char
    
    add eax, 48                                 ;Printare in cazul in care e numar, conform tabelei ASCII.
    
    PRINT_CHAR eax
    
return_to_print_converted_number:
    loop print_converted_number                 ;Printez pana cand stiva e goala.
    
    ret


print_char:
    add eax, 87                                 ;Printare in cazul in care e caracter, conform tabelei ASCII.
    
    PRINT_CHAR eax
    jmp return_to_print_converted_number	;Continui cu printarea normala.
