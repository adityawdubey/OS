#include <stdio.h>
#include <stdbool.h>
int findLRU(int time[], int n)
{
    int i, minimum = time[0], pos = 0;
    for (i = 1; i < n; ++i)
    {
        if (time[i] < minimum)
        {
            minimum = time[i];
            pos = i;
        }
    }
    return pos;
}
int main()
{
    int no_of_frames, no_of_pages, frames[10], pages[30], counter = 0, time[10], flag1, flag2, i, j, pos,
                                                          faults = 0;
    bool hit = false;
    printf("Enter number of frames: ");
    scanf("%d", &no_of_frames);
    printf("Enter number of pages: ");
    scanf("%d", &no_of_pages);
    printf("Enter reference string: ");
    for (i = 0; i < no_of_pages; ++i)
    {
        scanf("%d", &pages[i]);
    }
    for (i = 0; i < no_of_frames; ++i)
    {
        frames[i] = -1;
    }

    for (int i = 0; i < no_of_frames; i++)
    {
        printf("frame%d \t", i + 1);
    }
    printf("\n");
    for (i = 0; i < no_of_pages; ++i)
    {
        flag1 = flag2 = 0;
        for (j = 0; j < no_of_frames; ++j)
        {
            if (frames[j] == pages[i])
            {
                counter++;
                time[j] = counter;
                flag1 = flag2 = 1;
                hit = true;
                break;
            }
        }
        if (flag1 == 0)
        {
            for (j = 0; j < no_of_frames; ++j)
            {
                if (frames[j] == -1)
                {
                    counter++;
                    faults++;
                    frames[j] = pages[i];
                    time[j] = counter;
                    flag2 = 1;
                    hit = false;
                    break;
                }
            }
        }
        if (flag2 == 0)
        {
            pos = findLRU(time, no_of_frames);
            counter++;
            faults++;
            frames[pos] = pages[i];
            time[pos] = counter;
            hit = false;
        }
        printf("\n");
        for (j = 0; j < no_of_frames; ++j)
        {
            if (frames[j] != -1)
            {
                printf("%d\t", frames[j]);
            }
            else
            {
                printf(" \t");
            }
        }

        if (hit)
        {
            printf("Hit");
        }
        else
        {
            printf("Miss");
        }
    }
    printf("\nTotal Page Faults = %d", faults);
    return 0;
}


// Enter number of frames: 4
// Enter number of pages: 20
// Enter reference string: 7 0 1 2 0 3 0 4 2 3 0 3 2 1 2 0 1 7 0 1
// frame1  frame2  frame3  frame4 

// 7                               Miss
// 7       0                       Miss
// 7       0       1               Miss
// 7       0       1       2       Miss
// 7       0       1       2       Hit
// 3       0       1       2       Miss
// 3       0       1       2       Hit
// 3       0       4       2       Miss
// 3       0       4       2       Hit
// 3       0       4       2       Hit
// 3       0       4       2       Hit
// 3       0       4       2       Hit
// 3       0       4       2       Hit
// 3       0       1       2       Miss
// 3       0       1       2       Hit
// 3       0       1       2       Hit
// 3       0       1       2       Hit
// 7       0       1       2       Miss
// 7       0       1       2       Hit
// 7       0       1       2       Hit
// Total Page Faults = 8%  