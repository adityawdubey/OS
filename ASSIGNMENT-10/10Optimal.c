#include <stdio.h>
#include <stdbool.h>
int findOptimal(int frames[], int pages[], int n, int m, int index)
{
    int res = -1, farthest = index;
    for (int i = 0; i < n; ++i)
    {
        int j;
        for (j = index; j < m; ++j)
        {
            if (frames[i] == pages[j])
            {
                if (j > farthest)
                {
                    farthest = j;
                    res = i;
                }
                break;
            }
        }
        if (j == m)
        {
            return i;
        }
    }
    return (res == -1) ? 0 : res;
}

int main()
{
    int n, p, frames[10], pages[30], faults = 0;
    bool hit = false;
    printf("Enter number of frames: ");
    scanf("%d", &n);
    printf("Enter number of pages: ");
    scanf("%d", &p);
    printf("Enter reference string: ");
    for (int i = 0; i < p; ++i)
    {
        scanf("%d", &pages[i]);
    }
    for (int i = 0; i < n; i++)
    {
        printf("Frame%d", i + 1);
    }
    printf("\n");
    for (int i = 0; i < n; ++i)
    {
        frames[i] = -1;
    }
    for (int i = 0; i < p; ++i)
    {
        hit = false;
        for (int j = 0; j < n; ++j)
        {
            if (frames[j] == pages[i])
            {
                hit = true;
                break;
            }
        }
        if (!hit)
        {
            int index = i + 1;
            int pos = findOptimal(frames, pages, n, p, index);
            frames[pos] = pages[i];
            faults++;
        }
        printf("\n");
        for (int j = 0; j < n; ++j)
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