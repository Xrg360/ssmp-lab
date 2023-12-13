#include <stdio.h>
#include <stdlib.h>

int n, m, i, j, h, p, temp, k, total = 0;
int t[100], label[100], diff;

void main()
{
    // Get the number of tracks from the user
    printf("ENTER THE NUMBER OF TRACKS : ");
    scanf("%d", &n);

    // Get the initial head pointer position from the user
    printf("ENTER THE HEAD POINTER POSITION : ");
    scanf("%d", &h);

    // Get the tracks to be traversed from the user
    printf("ENTER THE TRACKS TO BE TRAVERSED : ");
    for (i = 0; i < n; i++)
    {
        scanf("%d", &t[i]);
    }

    // Add boundary tracks to the array
    t[n + 2] = 199;
    t[n + 1] = 0;
    t[n] = h;
    n = n + 3;

    // Sort the tracks in ascending order
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (t[j] > t[j + 1])
            {
                temp = t[j];
                t[j] = t[j + 1];
                t[j + 1] = temp;
            }
        }
    }

    // Find the index of the head pointer in the sorted array
    for (i = 0; i < n; i++)
    {
        if (t[i] == h)
        {
            k = i;
            break;
        }
    }

    // Traverse the tracks in the appropriate direction
    if (h < (199 - h))
    {
        for (i = k; i >= 0; i--, p++)
        {
            label[p] = t[i];
        }
        for (i = k + 1; i < n - 1; i++, p++)
        {
            label[p] = t[i];
        }
    }
    else
    {
        for (i = k; i < n; i++, p++)
        {
            label[p] = t[i];
        }
        for (i = k - 1; i >= 0; i--, p++)
        {
            label[p] = t[i];
        }
    }

    // Print the order of traversed tracks
    printf("TRAVERSED ORDER : ");
    for (i = 0; i < p; i++)
    {
        printf("%d => ", label[i]);
    }

    // Calculate the total head movements
    for (total = 0, j = 0; j < p - 1; j++)
    {
        diff = abs(label[j] - label[j + 1]);
        total = total + diff;
    }

    // Print the total head movements
    printf("\b\b\b.  \nTOTAL HEAD MOVEMENTS : %d\n", total);
}