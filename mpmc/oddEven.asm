data segment
    input_num dw 0002h
data ends

code segment
    assume cs:code, ds:data
start:
    mov ax, data
    mov ds, ax

    mov ax, input_num

    mov bx, 2
    div bx

    test dx, 1	
	int 03h
code ends
end start