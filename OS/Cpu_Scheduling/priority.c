#include <stdio.h>
#include <string.h>
struct process
{
    char name[20];
    int at, tt, bt, priority, wt, status, ct;
} p[20], temp;
struct done
{
    char name[20];
    int st, ct;
} d[20];
void main()
{
    int n, i, j, ls, min, fnd, num, idle;
    float twt = 0.0, ttt = 0.0;
    printf("ENTER THE NUMBER OF PROCESSES : ");
    scanf("%d", &n);
    for (i = 0; i < n; i++) // Input process details
    {
        printf("\nENTER DETAILS OF PROCESS %d", i + 1);
        printf("\nPROCESS NAME : ");
        scanf(" %s", p[i].name);
        printf("ARRIVAL TIME : ");
        scanf("%d", &p[i].at);
        printf("BURST TIME : ");
        scanf("%d", &p[i].bt);
        printf("PRIORITY : "); // 1 is the highest priority.
        scanf("%d", &p[i].priority);
        p[i].status = 0;
    }
    for (i = 0, ls = 0, num = 0, idle = 0; ls < n;)
    {
        for (j = 0, fnd = 0; j < n; j++)
        {
            if (i >= p[j].at && p[j].status == 0)
            {
                if (fnd == 0)
                {
                    min = j;
                    fnd = 1;
                }
                else if (fnd != 0 && p[min].priority > p[j].priority) // ONLY DIFFERENCE BETWEEN THIS AND SJF.C
                {
                    min = j;
                }
            }
        }
        if (idle == 0 && fnd == 0)
        {
            strcpy(d[num].name, "Idle");
            d[num].st = i;
            i++;
            idle = 1;
        }
        else if (fnd == 1)
        {
            if (idle == 1)
            {
                d[num].ct = i;
                num++;
                idle = 0;
            }
            strcpy(d[num].name, p[min].name);
            p[min].status = 1;
            d[num].st = i;
            d[num].ct = i + p[min].bt;
            i = d[num].ct;
            p[min].ct = d[num].ct;
            p[min].tt = p[min].ct - p[min].at;
            p[min].wt = p[min].tt - p[min].bt;
            num++;
            ls++;
        }
        else
        {
            i++;
        }
    }
    printf("\nPROCESS NAME\tCOMPLETION TIME (ms)\tWAITING TIME (ms)\tTURNAROUND TIME (ms)\n\n");
    for (i = 0; i < n; i++)
    {
        printf("    %s\t\t\t%d\t\t\t%d\t\t\t%d\n", p[i].name, p[i].ct, p[i].wt, p[i].tt);
        twt += p[i].wt;
        ttt += p[i].tt;
    }
    printf("\n\nGANTT CHART ");
    printf("\n\t--------------------------------------------------------------------\n\t");
    for (i = 0; i < num; i++)
    {
        printf("|");
        printf("%s\t", d[i].name);
    }
    printf(" |");
    printf("\n\t--------------------------------------------------------------------\n\t");
    for (i = 0; i < num; i++)
    {
        printf("%d\t", d[i].st);
    }
    printf("%d\t\n", d[num - 1].ct);
    printf("\nAVERAGE WAITING TIME : %f", (twt / n));
    printf("\nAVERAGE TURNAROUND TIME : %f\n", (ttt / n));
}
/*
ENTER THE NUMBER OF PROCESSES : 5

ENTER DETAILS OF PROCESS 1
PROCESS NAME : P1
ARRIVAL TIME : 0
BURST TIME : 10
PRIORITY : 3

ENTER DETAILS OF PROCESS 2
PROCESS NAME : P2
ARRIVAL TIME : 0
BURST TIME : 1
PRIORITY : 1

ENTER DETAILS OF PROCESS 3
PROCESS NAME : P3
ARRIVAL TIME : 0
BURST TIME : 2
PRIORITY : 4

ENTER DETAILS OF PROCESS 4
PROCESS NAME : P4
ARRIVAL TIME : 0
BURST TIME : 1
PRIORITY : 5

ENTER DETAILS OF PROCESS 5
PROCESS NAME : P5
ARRIVAL TIME : 0
BURST TIME : 5
PRIORITY : 2

PROCESS NAME    COMPLETION TIME (ms)    WAITING TIME (ms)       TURNAROUND TIME (ms)

    P1                  16                      6                       16
    P2                  1                       0                       1
    P3                  18                      16                      18
    P4                  19                      18                      19
    P5                  6                       1                       6


GANTT CHART
        --------------------------------------------------------------------
        |P2     |P5     |P1     |P3     |P4      |
        --------------------------------------------------------------------
        0       1       6       16      18      19

AVERAGE WAITING TIME : 8.200000
AVERAGE TURNAROUND TIME : 12.000000
*/