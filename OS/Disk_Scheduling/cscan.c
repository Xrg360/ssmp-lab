#include <stdio.h>

int n, m, i, j, h, p, temp, k, total = 0;
int t[100], label[100], diff; // Declare variables and arrays

void main()
{
    printf("ENTER THE NUMBER OF TRACKS : ");
    scanf("%d", &n); // Get the number of tracks from the user

    printf("ENTER THE HEAD POINTER POSITION : ");
    scanf("%d", &h); // Get the initial head pointer position from the user

    printf("ENTER THE TRACKS TO BE TRAVERSED : ");
    for (i = 0; i < n; i++)
    {
        scanf("%d", &t[i]); // Get the tracks to be traversed from the user
    }

    t[n + 2] = 199; // Add boundary tracks to the array
    t[n + 1] = 0;
    t[n] = h;
    n = n + 3;

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (t[j] > t[j + 1]) // Sort the tracks in ascending order
            {
                temp = t[j];
                t[j] = t[j + 1];
                t[j + 1] = temp;
            }
        }
    }

    for (i = 0; i < n; i++)
    {
        if (t[i] == h)
        {
            k = i;
            break;
        }
    }
    for (i = k; i < n; i++, p++)
    {
        label[p] = t[i];
    } // Traverse the tracks in the appropriate direction (Assuming Right)
    for (i = 0; i <= k - 1; i++, p++)
    {
        label[p] = t[i];
    } // Traverse the tracks in the remaining direction

    printf("TRAVERSED ORDER : ");
    for (i = 0; i < p; i++)
    {
        printf("%d => ", label[i]); // Print the order of traversed tracks
    }

    for (total = 0, j = 0; j < p - 1; j++)
    {
        diff = 0;
        if (label[j] > label[j + 1])
        {
            diff = label[j] - label[j + 1];
        }
        else
        {
            diff = label[j + 1] - label[j];
        }
        total = total + diff; // Calculate the total head movements
    }

    printf("\b\b\b.  \nTOTAL HEAD MOVEMENTS : %d\n", total); // Print the total head movements
}