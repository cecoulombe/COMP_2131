; Author: Caitlin Coulombe, T00756521
; Date: June 8, 2024
; Course: COMP 2131
;
; Note: Was not able to test on my computer (Mac) and used the IA32 architecture based on the examples in the notes and found online
;
; This program prints out the following messages on the screen:
; Hello, programmers!
; Welcome to the world of, 
; Linux assembly programming!

section .data
    msg1: 
        .asciz "Hello, programmers!\n"
        msg1_len = .-msg1

    msg2: 
        .asciz "Welcome to the world of,\n"
        msg2_len = .-msg2

    msg3: 
        .asciz "Linux assembly programming!\n"
        msg3_len = .-msg3

section .text
    global _start   ; this makes the _start label visible to the linker and specifies the entry point of the program.

_start:
    ; print msg1
    mov $4, %eax          ; sys_write system call number (4 for x86)
    mov $1, %ebx          ; file descriptor 1 is stdout
    mov $msg1, %ecx       ; pointer to the message
    mov $msg1_len, %edx   ; length of the message
    int $0x80             ; calls the kernel

    ; print msg2
    mov $4, %eax          ; sys_write system call number (4 for x86)
    mov $1, %ebx          ; file descriptor 1 is stdout
    mov $msg2, %ecx       ; pointer to the message
    mov $msg2_len, %edx   ; length of the message
    int $0x80             ; calls the kernel

    ; print msg3
    mov $4, %eax          ; sys_write system call number (4 for x86)
    mov $1, %ebx          ; file descriptor 1 is stdout
    mov $msg3, %ecx       ; pointer to the message
    mov $msg3_len, %edx   ; length of the message
    int $0x80             ; calls the kernel

    ; exit the application
    mov $0, %ebx
    mov $1, %eax          ; sys_exit system call number (1 for x86)
    int 0x80            ; calls the kernel