ASSUME DS:CODE, CS:CODE

DATA SEGMENT
    LIST DW 10H, 14H, 11H, 03H, 01H   ; Array to be sorted
    COUNT EQU 05H                     ; Number of elements in the array
    MSG1 DB  'Original Array:', '$'
    MSG2 DB  'Final Array:', '$'
DATA ENDS

CODE SEGMENT
START:
    STI
    MOV AX, DATA                      ; Move the address of the data segment to AX
    MOV DS, AX                        ; Set the data segment to the specified address
    MOV CX, COUNT                     ; Initialize CX with the number of elements in the array
    MOV SI, OFFSET LIST               ; Move the offset address of the array to SI

    MOV DX, OFFSET MSG1               ; Load the offset address of the message to be printed
    MOV AH, 09H                       ; Set the print function
    INT 21H                           ; Call the DOS interrupt
    ; Print the original array elements
PRINT1:
    MOV DX, [SI]                      ; Load the current element into DX
    ADD SI, 02H                       ; Move to the next element
    LOOP PRINT1                       ; Repeat until all elements are printed

    MOV DX, COUNT-1                   ; Initialize DX with COUNT-1 for the outer loop

    ; Bubble sort algorithm
BACK:
    MOV CX, DX                        ; Initialize CX with the current value of DX
    MOV SI, OFFSET LIST               ; Reset SI to the start of the array

AGAIN:
    MOV AX, [SI]                      ; Load the current element into AX
    CMP AX, [SI + 2]                  ; Compare with the next element
    JC GO                             ; Jump if the current element is greater

    XCHG AX, [SI + 2]                 ; Swap the elements
    XCHG AX, [SI]
    
GO:
    INC SI                            ; Move to the next pair of elements
    INC SI
    LOOP AGAIN                        ; Repeat until all elements are compared

    DEC DX                            ; Decrement DX for the next iteration
    JNZ BACK                          ; Jump if DX is not zero

    MOV CX, COUNT                     ; Reset CX with the number of elements in the array
    MOV SI, OFFSET LIST               ; Reset SI to the start of the array

    ; Print the sorted array elements

    MOV DX, OFFSET MSG2               ; Load the offset address of the message to be printed
    MOV AH, 09H                       ; Set the print function
    INT 21H                           ; Call the DOS interrupt
PRINT2:
    MOV DX, [SI]                      ; Load the current element into DX
    ADD SI, 02H                       ; Move to the next element
    LOOP PRINT2                       ; Repeat until all elements are printed

    MOV AH, 4CH                        ; Set the exit function
    INT 21H                            ; Call the DOS interrupt
    INT 03H
CODE ENDS
END START