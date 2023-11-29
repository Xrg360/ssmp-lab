// INPUT
// input.txt
// COPY START 1000
// START LDA ALPHA
// - ADD ONE
// - SUB TWO
// - STA BETA
// ALPHA BYTE C'KLNCE'
// ONE RESB 2
// TWO WORD 5
// BETA RESW 1
// - END START

// optab.txt
// LDA 00
// STA 0C
// ADD 18
// SUB 1C


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    int locationCounter, size, startingAddress, temp, flag;
    char label[15], opcode[15], operand[15], tempLabel[15], tempOpcode[15];
    
    FILE *input, *opcodeTable, *symbolTable, *intermediate, *programLength;
    
    // Open input and output files
    input = fopen("input.txt", "r");
    opcodeTable = fopen("optab.txt", "r");
    symbolTable = fopen("symtab.txt", "w+");
    intermediate = fopen("intermediate.txt", "w+");
    programLength = fopen("prgmlen.txt", "w+");
    
    // Read the first line of the source program
    fscanf(input, "%s %s %x\n", label, opcode, &locationCounter);
    
    // Process START directive
    if (strcmp(opcode, "START") == 0) {
        startingAddress = locationCounter;
        fprintf(intermediate, "- - %s %s %x\n", label, opcode, locationCounter);
        fscanf(input, "%s %s %s\n", label, opcode, operand);
    } else {
        printf("START operator not found\n");
        exit(-1);
    }
    
    // Process each line until END directive is encountered
    while (strcmp(opcode, "END") != 0) {
        // Check for the presence of a label
        if (strcmp(label, "-") != 0) {
            fseek(symbolTable, SEEK_SET, 0);
            // Check for duplicate symbols in the symbol table
            while (!feof(symbolTable)) {
                fscanf(symbolTable, "%s %x\n", tempLabel, &temp);
                if (strcmp(tempLabel, label) == 0) {
                    printf("Duplicate symbol error\n");
                    exit(-1);
                }
            }
            fprintf(symbolTable, "%s %x\n", label, locationCounter);
        }
        
        fseek(opcodeTable, SEEK_SET, 0);
        flag = 0;
        // Search for the opcode in the opcode table
        while (!feof(opcodeTable)) {
            fscanf(opcodeTable, "%s %x\n", tempOpcode, &temp);
            if (strcmp(opcode, tempOpcode) == 0) {
                flag = 1;
                fprintf(intermediate, "%x %d %s %s %s\n", locationCounter, 3, label, opcode, operand);
                locationCounter += 3;
                break;
            }
        }
        
        // Handle cases where the opcode is not found in the opcode table
        if (flag == 0) {
            if (strcmp(opcode, "RESB") == 0) {
                size = atoi(operand);
                fprintf(intermediate, "%x %d %s %s %s\n", locationCounter, size, label, opcode, operand);
                locationCounter += size;
            } else if (strcmp(opcode, "RESW") == 0) {
                size = atoi(operand) * 3;
                fprintf(intermediate, "%x %d %s %s %s\n", locationCounter, size, label, opcode, operand);
                locationCounter += size;
            } else if (strcmp(opcode, "WORD") == 0) {
                fprintf(intermediate, "%x %d %s %s %s\n", locationCounter, 3, label, opcode, operand);
                locationCounter += 3;
            } else if (strcmp(opcode, "BYTE") == 0) {
                size = strlen(operand) - 3;
                fprintf(intermediate, "%x %d %s %s %s\n", locationCounter, size, label, opcode, operand);
                locationCounter += size;
            } else {
                printf("Invalid operation\n");
                exit(-1);
            }
        }
        
        // Read the next line of the source program
        fscanf(input, "%s %s %s\n", label, opcode, operand);
    }
    
    // Write the last line of the intermediate code and calculate program length
    fprintf(intermediate, "%x - %s %s %s\n", locationCounter, label, opcode, operand);
    fprintf(programLength, "%x\n", locationCounter - startingAddress);
    
    // Close all file pointers
    fclose(input);
    fclose(opcodeTable);
    fclose(symbolTable);
    fclose(intermediate);
    fclose(programLength);
    
    return 0;
}
