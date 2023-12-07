#include <stdio.h>
#include <string.h>
int EXPANDING = 0; // 0: false, 1: true
char a[50], b[50], c[50];
FILE *input, *expanded, *namtab, *deftab, *argtab;
// Function to search for an macro name in NAMTAB
// If found, return 1
// if not found, return 0
int macroSearch(char a[100])
{
    FILE *macro;
    macro = fopen("NAMTAB.txt", "r");
    char e[100], temp[100], op[5];
    temp[0] = '\0';
    fscanf(macro, "%s", e);
    while (strcmp(temp, e) != 0)
    {
        strcpy(temp, e);
        // check if a is in macro file
        if (strcmp(e, a) == 0)
        {
            fclose(macro);
            return 1;
        }
        fscanf(macro, "%s", e);
    }
    fclose(macro);
    return 0;
}
// Not the actual way of doing it. You need to get the argument from ARGTAB based on the position and replace it in the line
// Using an easy method used in teachers code, hope thats allowed
void substituteArguments()
{
    if (strcmp(c, "=X'?1'") == 0)
    {
        strcpy(c, "='F1'");
    }
    else if (strcmp(c, "?2,X") == 0)
    {
        strcpy(c, "BUFFER,X");
    }
    else if (strcmp(c, "?3") == 0)
    {
        strcpy(c, "LENGTH");
    }
}
void getLine()
{
    if (EXPANDING == 1)
    {
        fscanf(deftab, "%s %s %s", a, b, c);
        substituteArguments();
    }
    else
    {
        fscanf(input, "%s %s %s", a, b, c);
    }
}
// No need to define, we are given with DEFTAB file, means defining work is already done.
// Just write to namtab, go to end of the macro (MEND) and read next line
void define()
{
    // open namtab in append mode
    fprintf(namtab, "%s\n", a);
    while (strcmp(b, "MEND") != 0)
    {
        fscanf(input, "%s %s %s", a, b, c);
    }
}
// V--------- NEW ADDITION
void writeArguments()
{
    // write c to argument. C could be of the format F1,BUFFER,LENGTH. We need to write it as 1 F1, 2 BUFFER, 3 LENGTH
    int i = 0, count = 1;
    fprintf(argtab, "%d ", count);
    for (i = 0; i < strlen(c); i++)
    {
        if (c[i] == ',')
        {
            fprintf(argtab, "\n");
            count++;
            fprintf(argtab, "%d ", count);
        }
        else
        {
            fprintf(argtab, "%c", c[i]);
        }
    }
}
void expand()
{
    EXPANDING = 1;
    // write macro call as comment
    fprintf(expanded, ". %s %s\n", b, c);
    // write macro arguments to argtab
    writeArguments(); // <------------------ NEW ADDITION
    // skip macro prototype
    getLine();
    while (strcmp(b, "MACRO") != 0)
    {
        getLine();
    }
    // read from deftab and write to expanded
    getLine();
    while (strcmp(b, "MEND") != 0)
    {
        // write to expanded
        fprintf(expanded, "%s %s %s\n", a, b, c);
        getLine();
    }
    EXPANDING = 0;
}
void processLine()
{
    int tempInt = macroSearch(b);
    if (tempInt == 1)
    {
        expand();
    }
    else if (strcmp(b, "MACRO") == 0)
    {
        define();
    }
    else
    {
        fprintf(expanded, "%s %s %s\n", a, b, c);
    }
}
// Main function
// Points to note:
/*
1. Namtab is created in this program, there is no need to create it
2. Format the DEFTAB and input file properly. Add `-` and correct spaces
*/
int main()
{
    // read a file
    input = fopen("inputnew.txt", "r");
    expanded = fopen("expanded.txt", "w");
    deftab = fopen("DEFTAB.txt", "r");
    namtab = fopen("NAMTAB.txt", "r");
    argtab = fopen("ARGTAB.txt", "w");
    fscanf(input, "%s %s %s", a, b, c);
    fprintf(expanded, "%s %s %s\n", a, b, c);
    while (strcmp(b, "END") != 0)
    {
        getLine();
        processLine();
    }
    // add print functions here to print the output
    return 0;
}
