ASSUME CS:CODE, DS:DATA

DATA SEGMENT
    STR DB 'MADAM$', '$'  ; Example string to check for palindrome
    PALINDROME_MSG DB 'The string is a palindrome.', '$'
    NOT_PALINDROME_MSG DB 'The string is not a palindrome.', '$'
DATA ENDS

CODE SEGMENT
START:
    MOV AX, DATA       ; Move the address of the data segment to AX
    MOV DS, AX          ; Set the data segment to the specified address
    MOV SI, OFFSET STR  ; Move the offset address of the string to SI
    MOV DI, SI          ; Copy the offset address to DI for comparison

    ; Find the length of the string
    MOV CL, 0           ; Initialize the counter to 0
    MOV AL, [SI]        ; Load the first character of the string
    CMP AL, '$'         ; Check if the string is empty
    JE PALINDROME_END   ; If empty, it is a palindrome

    ; Calculate the length of the string
    LENGTH_LOOP:
        INC CL          ; Increment the counter
        INC SI          ; Move to the next character
        MOV AL, [SI]    ; Load the next character
        CMP AL, '$'     ; Check if the end of the string is reached
        JNE LENGTH_LOOP ; If not, continue counting

    ; Check if the string is a palindrome
    PALINDROME:
        DEC SI          ; Move back to the last character
        MOV BH, CL      ; Move the length of the string to BH
        SHR BH, 1       ; Divide the length by 2 to get the midpoint. This works I've checked.

        ; Compare the characters from both ends of the string
        COMPARE_LOOP:
            MOV AL, [SI]        ; Load the character from the end
            MOV BL, [DI]        ; Load the character from the start
            CMP AL, BL          ; Compare the characters
            JNE NOT_PALINDROME  ; If not equal, it is not a palindrome
            DEC SI              ; Move to the next character from the end
            INC DI              ; Move to the next character from the start
            DEC BH              ; Decrement the counter
            JNZ COMPARE_LOOP    ; If counter is not zero, continue comparing

        ; If the loop completes without inequality, it is a palindrome
    PALINDROME_END:    
        MOV AH, 09H             ; Print message
        LEA DX, PALINDROME_MSG  ; Load the message to DX
        INT 21H                ; Print the message
        JMP EXIT               ; Exit the program

    ; If the string is not a palindrome
    NOT_PALINDROME:
        MOV AH, 09H                 ; Print message
        LEA DX, NOT_PALINDROME_MSG  ; Load the message to DX
        INT 21H                    ; Print the message

    ; Exit the program
    EXIT:
        MOV AH, 4CH     ; Set the exit function
        INT 21H        ; Call the DOS interrupt

CODE ENDS
END START