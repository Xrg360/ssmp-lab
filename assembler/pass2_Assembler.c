#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    FILE *intermediate, *symtab, *optab, *objprgm, *prgmlen;
    char temp1[10], temp2[10], temp3[10], addr[10], programName[10], label[10], operation[10], operand[10], startAddress[10], programLengthStr[10], opcode[10], opcodeValue[10], symbol[10], symbolValue[10], line[100];
    int len;

    // Open input and output files
    intermediate = fopen("intermediate.txt", "r");
    symtab = fopen("symtab.txt", "r");
    prgmlen = fopen("prgmlen.txt", "r");
    optab = fopen("optab.txt", "r");

    objprgm = fopen("objprgm.txt", "w+");

    // Read program header information from the intermediate file
    //?                                        -    -       COPY       START   1000
    fscanf(intermediate, "%s %s %s %s %s", temp1, temp2, programName, temp3, startAddress);
    len = strlen(programName);

    // Write Header Record to the object program file
    fprintf(objprgm, "H^");
    if (len > 6) {
        for (int i = 0; i < 6; i++) {
            fprintf(objprgm, "%c", programName[i]);
        }
        fprintf(objprgm, "^");
    } else {
        fprintf(objprgm, "%s", programName);
        for (int i = len; i < 6; i++) {
            fprintf(objprgm, "_");
        }
        fprintf(objprgm, "^");
    }

    // Ensure the start address is 6 characters long
    len = 6 - strlen(startAddress);
    for (int i = 0; i < len; i++) {
        fprintf(objprgm, "0");
    }
    fprintf(objprgm, "%s^", startAddress);

    // Read program length from the program length file
    fscanf(prgmlen, "%s", programLengthStr);

    // Ensure the program length is 6 characters long
    len = 6 - strlen(programLengthStr);
    for (int i = 0; i < len; i++) {
        fprintf(objprgm, "0");
    }
    fprintf(objprgm, "%s", programLengthStr);

    // Read the first line of the intermediate file

    //                                     1000  3      start  LDA          alpha
    fscanf(intermediate, "%s %s %s %s %s", addr, temp2, label, operation, operand);
    fprintf(objprgm, "$\nT^00%s", addr); //001000

    // Process each line until the END directive is encountered
    while (strcmp("END", operation) != 0) {
        
        // Search for the opcode in the opcode table
        while (fscanf(optab, "%s %s", opcode, opcodeValue) != EOF) {
            if (strcmp(operation, "WORD") != 0 || strcmp(operation, "BYTE") != 0) {
                if (strcmp(opcode, operation) == 0) {
                    fprintf(objprgm, "^%s", opcodeValue);
                    // Search for the symbol in the symbol table
                    while (fscanf(symtab, "%s %s", symbol, symbolValue) != EOF) {
                        if (strcmp(symbol, operand) == 0) {
                            fprintf(objprgm, "%s", symbolValue);
                            break;
                        }
                    }
                    fseek(symtab, 0, SEEK_SET);
                    break;
                }
            } else {
                // Process the WORD directive
                fprintf(objprgm, "$\nT^");
                fprintf(objprgm, "00%s^", addr);
                int operandValue = atoi(operand);
                char hexString[10];
                sprintf(hexString, "%x", operandValue);
                if (strlen(hexString) > 6) {
                    for (int i = 0; i < 6; i++) {
                        fprintf(objprgm, "%c", hexString[i]);
                    }
                } else {
                    int leadingZeros = 6 - strlen(hexString);
                    for (int i = 0; i < leadingZeros; i++) {
                        fprintf(objprgm, "0");
                    }
                    fprintf(objprgm, "%s", hexString);
                }
                break;
            }
        }
        fseek(optab, 0, SEEK_SET);

        // Read the next line of the intermediate file
        fscanf(intermediate, "%s %s %s %s %s", addr, temp2, label, operation, operand);
    }

    // Write End Record to the object program file
    fprintf(objprgm, "$\nE^");
    len = 6 - strlen(startAddress);
    for (int i = 0; i < len; i++) {
        fprintf(objprgm, "0");
    }
    fprintf(objprgm, "%s$", startAddress);

    // Move to the beginning of the object program file
    fseek(objprgm, 0, SEEK_SET);

    // Create a temporary file to store the new content
    FILE *tempFile = fopen("temp.txt", "w+");

    // Update the length field in the Header Record
    while (fgets(line, sizeof(line), objprgm) != NULL) {
        if (line[0] == 'T') {
            int count = 0;
            for (int i = 9; line[i] != '\0'; i++) {
                if (line[i] == '^' || line[i] == '$') {
                    continue;
                }
                count++;
            }
            char lengthStr[3], test[] = "0";
            sprintf(lengthStr, "%x", (count - 1) / 2);
            if (strlen(lengthStr) < 2) {
                strcat(test, lengthStr);
            } else {
                strcpy(test, lengthStr);
            }
            strcat(test, "^");
            int insertIndex = 9;
            int originalLength = strlen(line);
            int newLength = originalLength + strlen(test);
            char newString[newLength + 1];
            strncpy(newString, line, insertIndex);
            newString[insertIndex] = '\0';
            strcat(newString, test);
            strcat(newString, line + insertIndex);
            fprintf(tempFile, "%s", newString);
        } else {
            fprintf(tempFile, "%s", line);
        }
    }

    // Close files
    fclose(intermediate);
    fclose(symtab);
    fclose(optab);
    fclose(objprgm);
    fclose(prgmlen);
    fclose(tempFile);

    // Rename the temporary file to the object program file
    rename("temp.txt", "objprgm.txt");

    return 0;
}
