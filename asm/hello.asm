;
;
; First steps of learning machine code
;   Specs: Late 2013 MacBook Retina
;         x86_64 Intel CPU
;
;

global start
 
 
section .text
 
start:
    mov     rax, 0x2000004 ; write  (BSD way)
    mov     rdi, 1         ; stdout
    mov     rsi, qword msg ; load 64 bit address of msg
    mov     rdx, msg.len   ; load the length of msg
    syscall
 
    mov     rax, 0x2000001 ; exit
    mov     rdi, 0
    syscall
 
 
section .data
 
msg:    db      "Hello, world!", 10
.len:   equ     $ - msg
