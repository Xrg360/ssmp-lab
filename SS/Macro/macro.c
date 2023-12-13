#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void main()
{
    FILE *input, *namtab, *deftab, *argtab, *op;
    int len, i, pos = 1;
    char
        arg[20],
        opcode[20], operand[20], label[20], name[20],
        mne1[20], opnd1[20], pos1[10], pos2[10];
    input = fopen("input.txt", "r");
    namtab = fopen("namtab.txt", "w+");
    deftab = fopen("deftab.txt", "w+");
    argtab = fopen("argtab.txt", "w+");
    op = fopen("op.txt", "w+");

    fscanf(input, "%s%s%s", label, opcode, operand);
    while (strcmp(opcode, "END") != 0)
    {
        // Macro Defenition
        if (strcmp(opcode, "MACRO") == 0)
        {
            fprintf(namtab, "%s\n", label);

            // Reset position so that we can read from start
            fseek(namtab, SEEK_SET, 0);

            // Macro defenition on the deftab
            fprintf(deftab, "%s\t%s\n", label, operand);
            fscanf(input, "%s%s%s", label, opcode, operand);
            while (strcmp(opcode, "MEND") != 0)
            {
                // Check if operand is a positional parameter
                if (operand[0] == '&')
                {
                    sprintf(pos1, "%d", pos);            // Converts the integer pos to string pos1. pos1 is "1".
                    strcpy(pos2, "?");                   // Load "?" to pos2. pos2 is "?".
                    strcpy(operand, strcat(pos2, pos1)); // We concat ? and 1 to make ?1 and store it in operand.
                    pos = pos + 1;
                }
                fprintf(deftab, "%s\t%s\n", opcode, operand);
                fscanf(input, "%s%s%s", label, opcode, operand);
            }
            fprintf(deftab, "%s", opcode);
        }
        // OPCODE is not a macro, so write to output file
        else
        {
            fscanf(namtab, "%s", name);
            if (strcmp(opcode, name) == 0)
            {
                len = strlen(operand);
                for (i = 0; i < len; i++) // Load the arguments to argtab
                {
                    if (operand[i] != ',')
                        fprintf(argtab, "%c", operand[i]);
                    else
                        fprintf(argtab, "\n");
                }
                fseek(deftab, SEEK_SET, 0);
                fseek(argtab, SEEK_SET, 0);
                fscanf(deftab, "%s %s", mne1, opnd1); // Skip the macro invocation line
                fscanf(deftab, "%s %s", mne1, opnd1);
                while (strcmp(mne1, "MEND") != 0)
                {
                    if ((opnd1[0] == '?')) // If opnd1 is a positional parameter
                    {
                        fscanf(argtab, "%s", arg);
                        fprintf(op, "-\t%s\t%s\n", mne1, arg);
                    }
                    else
                        fprintf(op, "-\t%s\t%s\n", mne1, opnd1);
                    fscanf(deftab, "%s%s", mne1, opnd1);
                }
            }
            else
                fprintf(op, "%s\t%s\t%s\n", label, opcode, operand); // Write the line as it is to output file. (Normal Case)
        }
        fscanf(input, "%s%s%s", label, opcode, operand);
    }
    fprintf(op, "%s\t%s\t%s", label, opcode, operand);
    fclose(input);
    fclose(namtab);
    fclose(deftab);
    fclose(argtab);
    fclose(op);
    printf("Successfull !!! \n");
}