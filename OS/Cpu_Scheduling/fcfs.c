#include <stdio.h>
#include <string.h>

// Structure to represent label process
struct process
{
    char name[20]; // Process name
    int at;        // Arrival time
    int tt;        // Turnaround time
    int bt;        // Burst time
    int wt;        // Waiting time
    int ct;        // Completion time
    int status;    // Status of the process (0: not completed, 1: completed)
} p[20], temp;

// Structure to represent the completed processes
struct done
{
    char name[20]; // Process name
    int st;        // Start time
    int ct;        // Completion time
} d[20];

void main()
{
    int i, j, n, num, idle = 0;
    float avwt = 0;
    float avtt = 0;

    // Get the number of processes from the user
    printf("ENTER THE NUMBER OF PROCESSES : ");
    scanf("%d", &n);

    // Input process details from the user
    for (i = 0; i < n; i++)
    {
        printf("\nENTER DETAILS OF PROCESS %d", i + 1);
        printf("\nPROCESS NAME : ");
        scanf(" %s", p[i].name);
        printf("ARRIVAL TIME : ");
        scanf("%d", &p[i].at);
        printf("BURST TIME : ");
        scanf("%d", &p[i].bt);
        p[i].status = 0; // Set the status of the process to not completed
    }

    // Sort the processes based on arrival time using bubble sort
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (p[j].at > p[j + 1].at)
            {
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    // Perform the FCFS CPU scheduling algorithm
    for (i = 0, j = 0, num = 0; j < n;)
    {
        if (p[j].at <= i && p[j].status == 0)
        {
            if (idle == 1)
            {
                d[num].ct = i; // Set the completion time of the idle process
                num++;
                idle = 0;
            }
            strcpy(d[num].name, p[j].name); // Set the name of the completed process
            d[num].st = i;                  // Set the start time of the completed process
            d[num].ct = i + p[j].bt;        // Set the completion time of the completed process
            p[j].wt = d[num].st - p[j].at;  // Calculate the waiting time of the completed process
            p[j].tt = p[j].wt + p[j].bt;    // Calculate the turnaround time of the completed process
            p[j].ct = d[num].ct;            // Set the completion time of the completed process
            i = d[num].ct;                  // Update the current time
            p[j].status = 1;                // Set the status of the process to completed
            j++;
            num++;
        }
        else if (idle == 0)
        {
            strcpy(d[num].name, "Idle"); // Set the name of the idle process
            d[num].st = i;               // Set the start time of the idle process
            i++;
            idle = 1;
        }
        else
        {
            i++;
        }
    }

    // Print the process details and calculate the average waiting time and average turnaround time
    printf("\nPROCESS NAME\tCOMPLETION TIME (ms)\tWAITING TIME (ms)\tTURNAROUND TIME (ms)\n");
    for (int i = 0; i < n; i++)
    {
        printf("    %s\t\t\t%d\t\t\t%d\t\t\t%d\n", p[i].name, p[i].ct, p[i].wt, p[i].tt);
        avwt += p[i].wt;
        avtt += p[i].tt;
    }

    // Print the Gantt chart
    printf("\n\nGANTT CHART ");
    printf("\n----------------------------------------------------------\n");
    for (i = 0; i < num; i++)
    {
        printf("|");
        printf("   %s\t", d[i].name);
    }
    printf(" |");
    printf("\n----------------------------------------------------------\n");
    for (i = 0; i < num; i++)
    {
        printf("%d\t", d[i].st);
    }
    printf("%d\t", d[num - 1].ct);

    // Print the average waiting time and average turnaround time
    printf("\n\nAVERAGE WAITING TIME : %f", (avwt / n));
    printf("\nAVERAGE TURNAROUND TIME : %f\n", (avtt / n));
}