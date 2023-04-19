#include <stdio.h>

// function to implement Non-preemptive SJF scheduling
void non_preemptive_sjf(int n, int burst_time[], int arrival_time[]) {
    // variables to keep track of waiting time, turnaround time and completion time
    int wt[n], tat[n], ct[n];

    // a list to keep track of whether a process is completed or not
    int completed[n];
    for (int i = 0; i < n; i++) {
        completed[i] = 0;
    }

    // a variable to keep track of the current time
    int t = 0;

    // a variable to keep track of the total number of completed processes
    int count = 0;

    // loop until all the processes are completed
    while (count != n) {
        // find the process with the smallest burst time among the processes that have arrived
        int min_bt = __INT_MAX__;
        int min_index = -1;
        for (int i = 0; i < n; i++) {
            if (arrival_time[i] <= t && completed[i] == 0 && burst_time[i] < min_bt) {
                min_bt = burst_time[i];
                min_index = i;
            }
        }

        // if no process is found, increment the current time
        if (min_index == -1) {
            t++;
            continue;
        }

        // update the waiting time and completion time for the selected process
        wt[min_index] = t - arrival_time[min_index];
        ct[min_index] = t + burst_time[min_index];
        tat[min_index] = ct[min_index] - arrival_time[min_index];

        // mark the selected process as completed
        completed[min_index] = 1;
        count++;

        // increment the current time
        t++;
    }

    // printing the result
    printf("Non-preemptive SJF Scheduling\n");
    printf("Process\tBurst Time\tArrival Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t\t%d\t\t%d\t\t%d\t\t%d\n", i, burst_time[i], arrival_time[i], wt[i], tat[i]);
    }
}

int main() {
    // taking input of the number of processes
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // taking input of the burst time and arrival time for each process
    int burst_time[n], arrival_time[n];
    for (int i = 0; i < n; i++) {
        printf("Enter the burst time for process %d: ", i);
        scanf("%d", &burst_time[i]);
        printf("Enter the arrival time for process %d: ", i);
        scanf("%d", &arrival_time[i]);
    }

    // calling the Non-preemptive SJF scheduling function
    non_preemptive_sjf(n, burst_time, arrival_time);

    return 0;
}

