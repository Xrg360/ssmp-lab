ASSUME CS:CODE, DS:DATA

DATA SEGMENT
    STR1 DB 'MALAYALAM $'   ; First string
    STR2 DB 'MALAYALAM $'   ; Second string
    A DB 00H                ; Length of first string
    L DB 00H                ; Length of second string
    MSG1 DB 'STRINGS_EQUAL$' ; Message for equal strings
    MSG2 DB 'NOT_EQUAL$'     ; Message for unequal strings
DATA ENDS

CODE SEGMENT
START:
    MOV AX, DATA
    MOV DS, AX

    ; Calculate the length of the first string
    LEA SI, STR1
    MOV DL, 00H
LENGTH1:
    MOV AL, [SI]
    CMP AL, '$'
    JZ UP
    INC DL
    INC SI
    JMP LENGTH1
UP:
    MOV A, DL

    ; Calculate the length of the second string
    MOV DL, 00H
    LEA DI, STR2
LENGTH2:
    MOV AL, [DI]
    CMP AL, '$'
    JZ UP1
    INC DL
    INC DI
    JMP LENGTH2
UP1:
    MOV L, DL

    ; Compare the lengths of the two strings
    MOV AL, A
    MOV BL, L
    CMP AL, BL
    JNZ NOT_EQUAL

    ; Compare the characters of the two strings
    LEA SI, STR1
    LEA DI, STR2
COMP:
    MOV AL, [SI]
    MOV BL, [DI]
    CMP AL, BL
    JNZ NOT_EQUAL

    INC SI
    INC DI

    ; Check if end of string is reached
    CMP AL, '$'
    JNZ COMP

    ; Strings are equal
    MOV DX, OFFSET MSG1
    MOV AH, 09H
    INT 21H
    JMP EXIT

NOT_EQUAL:
    ; Strings are not equal
    MOV DX, OFFSET MSG2
    MOV AH, 09H
    INT 21H

EXIT:
    MOV AH, 4CH
    INT 21H
CODE ENDS
END START