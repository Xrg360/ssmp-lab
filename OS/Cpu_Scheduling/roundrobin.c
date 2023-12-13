#include <stdio.h>
int i, j, n, time = 0, tq, npthaa; // npthaa = no: process that has already arrived
float avgtat = 0, avgwt = 0;
struct Process
{
    int pid, at, bt, wt, ct, tat, rt, rbt; // rt = run time, rbt = remaining burst time
} p[30], temp, queue[10];                  // queue is for table
void main()
{
    printf("Enter TIme Quanta:");
    scanf("%d", &tq);
    printf("Enter No. Process:");
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        p[i].pid = i + 1;
        printf("Enter Arrival Time of Process %d:", i + 1);
        scanf("%d", &p[i].at);
        printf("Enter Burst Time of Process %d:", i + 1);
        scanf("%d", &p[i].bt);
        p[i].rbt = p[i].bt;
    }
    // Sorting
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (p[j + 1].at < p[j].at)
            {
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
    // Computation
    for (i = 0; i < n; i++)
    {
        if (p[i].rbt > tq)
        {
            p[i].rt = tq;
            time += tq;
            // Calculate the number of process that has already arrived
            npthaa = 0;
            for (j = i + 1; j < n; j++)
            {
                if (p[j].at <= time)
                    npthaa++;
            }
            // Move all after i + npthaa to right side by 1 position
            for (int j = n - 1; j > i + npthaa; j--)
            {
                p[j + 1] = p[j];
            }
            // Push remaining of current process to the vacant space
            p[i + npthaa + 1] = p[i];
            p[i + npthaa + 1].rbt = p[i + npthaa + 1].rbt - tq;
            n++;
        }
        else
        {
            p[i].rt = p[i].rbt;
            time += p[i].rbt;
            p[i].ct = time;
        }
    }
    // Table queue
    int z = 0;
    for (i = 0; i < n; i++)
    {
        // filter by complition time to only have unique process
        if (p[i].ct != 0)
        {
            queue[z] = p[i];
            queue[z].tat = p[i].ct - p[i].at;
            queue[z].wt = queue[z].tat - queue[z].bt;
            avgtat += queue[z].tat;
            avgwt += queue[z].wt;
            z++;
        }
    }
    // print table
    printf(" PID | AT | BT | CT | WT | TAT\n");
    for (i = 0; i < z; i++)
    {
        printf(" P%d | %d | %d | %d | %d | %d\n", queue[i].pid, queue[i].at, queue[i].bt, queue[i].ct, queue[i].wt, queue[i].tat);
    }
    printf("Avg TAT: %.2f", avgtat / z);
    printf("\nAvg WT: %.2f", avgwt / z);
    printf("\n--------------------------------");
    printf("\nGanttchart");
    // ganttchart();
    printf("\n-");
    for (i = 0; i < n; i++)
    {
        printf("-");
        for (j = 0; j < p[i].rt; j++)
            printf("-");
        printf("-");
    }
    printf("\n|");
    for (i = 0; i < n; i++)
    {
        printf("%d", p[i].pid);
        for (j = 0; j < p[i].rt; j++)
            printf(" ");
        printf("|");
    }
    printf("\n-");
    for (i = 0; i < n; i++)
    {
        printf("-");
        for (j = 0; j < p[i].rt; j++)
            printf("-");
        printf("-");
    }
    printf("\n0");
    z = 0;
    for (i = 0; i < n; i++)
    {
        printf(" ");
        for (j = 0; j < p[i].rt - (z > 9 ? 1 : 0); j++)
            printf(" ");
        z += p[i].rt;
        printf("%d", z);
    }
}