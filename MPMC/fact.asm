data segment
num dw 0005h
fact dw ?
data ends
code segment
assume cs:code,ds:data
start : mov ax,data
	mov ds,ax
	mov ax,num
	mov bx,ax
loop1:  dec bx
	jz final
	mul bx
	loop loop1
final :int 03h
code ends
end start
	