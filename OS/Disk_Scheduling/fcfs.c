#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main()
{
    int tr[20], cr, n, i, sum = 0, new;

    // Get the number of tracks from the user
    printf("ENTER THE NUMBER OF TRACKS : ");
    scanf("%d", &n);

    // Get the initial head pointer position from the user
    printf("ENTER THE HEAD POINTER POSITION : ");
    scanf("%d", &cr);

    // Get the tracks to be traversed from the user
    printf("ENTER THE TRACKS TO BE TRAVERSED : ");
    for (i = 0; i < n; i++)
    {
        scanf("%d", &tr[i]);

        // Calculate the distance between the current track and the next track
        new = abs(cr - tr[i]);

        // Update the current track to the next track
        cr = tr[i];

        // Add the distance to the total head movements
        sum = sum + new;
    }

    // Print the order of traversed tracks
    printf("TRAVERSED ORDER : ");
    for (i = 0; i < n; i++)
        printf("%d => ", tr[i]);
    printf("\b\b\b.   \n");

    // Print the total head movements
    printf("TOTAL HEAD MOVEMENTS : %d\n", sum);
}