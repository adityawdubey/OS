#include <stdio.h>

// function to implement Preemptive SJF scheduling
void preemptive_sjf(int n, int burst_time[], int arrival_time[]) {
    // variables to keep track of waiting time, turnaround time and completion time
    int wt[n], tat[n], ct[n];

    // a list to keep track of the remaining burst time for each process
    int remaining_bt[n];
    for (int i = 0; i < n; i++) {
        remaining_bt[i] = burst_time[i];
    }

    // a variable to keep track of the current time
    int t = 0;

    // a variable to keep track of the total number of completed processes
    int completed = 0;

    // loop until all the processes are completed
    while (completed != n) {
        // find the process with the smallest remaining burst time
        int min_bt = __INT_MAX__;
        int min_index = -1;
        for (int i = 0; i < n; i++) {
            if (remaining_bt[i] > 0 && remaining_bt[i] < min_bt && t >= arrival_time[i]) {
                min_bt = remaining_bt[i];
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
        ct[min_index] = t + 1;

        // decrement the remaining burst time for the selected process
        remaining_bt[min_index]--;

        // if the process has completed execution, update the turnaround time and increment the completed counter
        if (remaining_bt[min_index] == 0) {
            tat[min_index] = wt[min_index] + burst_time[min_index];
            completed++;
        }

        // increment the current time
        t++;
    }

    // printing the result
    printf("Preemptive SJF Scheduling\n");
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

    // calling the Preemptive SJF scheduling function
    preemptive_sjf(n, burst_time, arrival_time);

    return 0;
}
