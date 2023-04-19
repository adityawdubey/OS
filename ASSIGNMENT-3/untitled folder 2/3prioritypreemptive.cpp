#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <iostream>
#include<string>
using namespace std;

struct process
{
    int pid;
    float burst_time;
    int priority;
    float waiting_time;
    float turnaround_time;
    float remaining_time;
    float arrival_time;
};

void swap(struct process *a, struct process *b)
{
    struct process temp = *a;
    *a = *b;
    *b = temp;
}

bool check_number(string str) {
   for (int i = 0; i < str.length(); i++)
   if (isdigit(str[i]) == false)
      return false;
      return true;
}

int main()
{
    int  i, j,n;
    string x;
    xyz:
    printf("Enter the number of processes: ");
    cin>>x;
    if (!check_number(x)) 
    {
        printf("Number of Processes can't be non integer\n\n");
        goto xyz;
    }

    n=stoi(x);

    struct process p[n];

    for (i = 0; i < n; i++)
    {
        printf("\nEnter the details of process %d\n", i + 1);
        printf("Process ID: ");
        scanf("%d", &p[i].pid);
        printf("Arrival time: ");
        scanf("%f", &p[i].arrival_time);
        printf("Burst time: ");
        scanf("%f", &p[i].burst_time);
        while (p[i].burst_time <= 0)
        {
            printf("Invalid burst time. Enter a positive value: ");
            scanf("%f", &p[i].burst_time);
        }
        printf("Priority: ");
        scanf("%d", &p[i].priority);
        p[i].remaining_time = p[i].burst_time;
    }

    // Sort the processes based on arrival time and priority (in descending order)
    for (i = 0; i < n - 1; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (p[i].arrival_time > p[j].arrival_time)
            {
                swap(&p[i], &p[j]);
            }
            else if (p[i].arrival_time == p[j].arrival_time && p[i].priority < p[j].priority)
            {
                swap(&p[i], &p[j]);
            }
        }
    }

    float current_time = 0, total_waiting_time = 0, total_turnaround_time = 0;
    int completed_processes = 0, current_process = -1;
    printf("\nGantt Chart:\n");

    while (completed_processes < n)
    {
        // Select the process with highest priority and arrival time <= current time
        int highest_priority = -1;
        for (i = 0; i < n; i++)
        {
            if (p[i].remaining_time > 0 && p[i].priority > highest_priority && p[i].arrival_time <= current_time)
            {
                highest_priority = p[i].priority;
                current_process = i;
            }
        }

        if (current_process == -1)
        {
            current_time++;
            continue;
        }

        // Calculate waiting time for the current process
        p[current_process].waiting_time = current_time - p[current_process].arrival_time;
        total_waiting_time += p[current_process].waiting_time;

        // Execute the current process for 1 unit of time
        printf("%.1f - P%d - ", current_time, p[current_process].pid);
        current_time += 1;
        p[current_process].remaining_time -= 1;

        // Check if the current process has completed
        if (p[current_process].remaining_time == 0)
        {
            // Calculate turnaround time for the current process
            p[current_process].turnaround_time = current_time - p[current_process].arrival_time;
            total_turnaround_time += p[current_process].turnaround_time;

            completed_processes++;
        }
    }

    // Gantt chart that simplifies the consecutive runs of the same process:

    float curr_time = 0.0;
    int curr_pid = -1;

    printf("\nGantt Chart:\n");
    printf("--------------------------------------------------------------\n");

    printf("%.1f", curr_time);
    for (i = 0; i < n; i++)
    {
        if (curr_pid != p[i].pid)
        {
            if (curr_pid != -1)
            {
                printf(" - %.1f", curr_time);
            }
            printf("- P%d", p[i].pid);
            curr_pid = p[i].pid;
        }
        p[i].waiting_time = curr_time - p[i].arrival_time;
        curr_time += p[i].burst_time;
        p[i].turnaround_time = curr_time - p[i].arrival_time;
    }
    printf(" - %.1f", curr_time);
    printf("\n\n");

    // Calculate completion time for each process
    for (i = 0; i < n; i++)
    {
        p[i].turnaround_time += p[i].arrival_time;
        p[i].waiting_time = p[i].turnaround_time - p[i].burst_time;
        p[i].turnaround_time -= p[i].arrival_time;
        // printf("\nProcess %d:\n", p[i].pid);
        // printf("Completion time: %.1f\n", p[i].turnaround_time + p[i].arrival_time);
        // printf("Waiting time: %.1f\n", p[i].waiting_time);
        // printf("Turnaround time: %.1f\n", p[i].turnaround_time);
    }

    // Calculate average waiting time and average turnaround time
    float avg_waiting_time = total_waiting_time / n;
    float avg_turnaround_time = total_turnaround_time / n;

    printf("\nProcess ID\tArrival Time\tBurst Time\tPriority\tCompletion Time\tWaiting Time\tTurnaround Time\n");
    printf("--------------------------------------------------------------------------------------------------------\n");

    for (i = 0; i < n; i++)
    {
        printf("P%d\t\t%.1f\t\t%.1f\t\t%d\t\t%.1f\t\t%.1f\t\t%.1f\n", p[i].pid, p[i].arrival_time, p[i].burst_time, p[i].priority, p[i].turnaround_time + p[i].arrival_time, p[i].waiting_time, p[i].turnaround_time);
    }

    printf("\nAverage Waiting Time: %.2f\n", avg_waiting_time);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround_time);

    return 0;
}
