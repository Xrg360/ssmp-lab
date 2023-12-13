ASSUME CS:CODE, DS:DATA

DATA SEGMENT
    STR DB 'MADAM$', '$'  ; Example string to check for palindrome
    PALINDROME_MSG DB 'The string is a palindrome.', '$'
    NOT_PALINDROME_MSG DB 'The string is not a palindrome.', '$'
DATA ENDS

CODE SEGMENT
START:
    MOV AX, DATA
    MOV DS, AX
    MOV SI, OFFSET STR
    MOV DI, SI

    ; Find the length of the string
    MOV CL, 0
    MOV AL, [SI]
    CMP AL, '$'
    JE PALINDROME_END

    ; Calculate the length of the string
    LENGTH_LOOP:
        INC CL
        INC SI
        MOV AL, [SI]
        CMP AL, '$'
        JNE LENGTH_LOOP

    ; Check if the string is a palindrome
    PALINDROME:
        DEC SI
        MOV BH, CL
        SHR BH, 1 ; Divide the length by 2

        ; Compare the characters from both ends of the string
        COMPARE_LOOP:
            MOV AL, [SI]  ; SI IS END
            MOV BL, [DI] ; DI IS START
            CMP AL, BL
            JNE NOT_PALINDROME
            DEC SI
            INC DI
            DEC BH
            JNZ COMPARE_LOOP

        ; If the loop completes without inequality, it is a palindrome
    PALINDROME_END:
        MOV AH, 09H
        LEA DX, PALINDROME_MSG
        INT 21H
        JMP EXIT

    ; If the string is not a palindrome
    NOT_PALINDROME:
        MOV AH, 09H
        LEA DX, NOT_PALINDROME_MSG
        INT 21H

    ; Exit the program
    EXIT:
        MOV AH, 4CH
        INT 21H

CODE ENDS
END START