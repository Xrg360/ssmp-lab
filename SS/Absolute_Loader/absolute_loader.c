#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void main()
{
    FILE *fp, *op;
    int i, addr1, l, j, staddr1;
    char name[10], line[50], name1[10], addr[10], rec[10], ch, staddr[10], code[10];
    printf("Enter program name:");
    scanf("%s", name);
    fp = fopen("obj_program.txt", "r");
    op = fopen("output.txt", "w+");    
    fscanf(fp, "%s", line);
    for (i = 2, j = 0; i < 8, j < 6; i++, j++)
        name1[j] = line[i];
    name1[j] = '\0';
    if (strcmp(name, name1) == 0)
    {
        do
        {
            fscanf(fp, "%s", line);
            if (line[0] == 'T')
            {
                for (i = 2, j = 0; i < 8, j < 6; i++, j++)
                    staddr[j] = line[i];
                staddr[j] = '\0';
                staddr1 = (int)strtol(staddr, NULL, 16);
                i = 12;
                while (line[i] != '$')
                {
                    if (line[i] != '^')
                    {
                        for (j = 0, i; j < 6; j++, i++)
                        {
                            code[j] = line[i];
                        }
                        code[j] = '\0';
                        printf("%x \t %s\n", staddr1, code);
                        fprintf(op, "%x \t %s\n", staddr1, code);                        
                        staddr1 += 0x3;
                    }
                    else
                        i++;
                }
            }
            if (line[0] == 'E')
            {
                for (i = 0, j = 2; i < 6; i++, j++)
                    addr[i] = line[j];
                addr[i] = '\0';
                printf("Jump to address: %s\n", addr);
                fprintf(op,"Jump to address: %s\n", addr);                
                break;
            }
        } while (!feof(fp));
    }
    else
    {
        printf("The program name dees not match!\n");
        exit(-1);
    }
    fclose(fp);
    fclose(op);    
}
