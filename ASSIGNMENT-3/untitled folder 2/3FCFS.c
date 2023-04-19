#include <stdio.h>

#include <exception>

using namespace std;

void fcfs(int processes[], int n) {
    int wt[n], tat[n];
    int i;
    // Calculating waiting time for each process
    wt[0] = 0;
    for (i = 1; i < n; i++) {
        wt[i] = wt[i-1] + processes[i-1];
    }
    // Calculating turnaround time for each process
    for (i = 0; i < n; i++) {
        tat[i] = wt[i] + processes[i];
    }
    // Printing the result and Gantt Chart
    cout << "Process\tBurst Time\tWaiting Time\tTurnaround Time\n";
    for (i = 0; i < n; i++) {
        cout << "P" << i << "\t\t" << processes[i] << "\t\t" << wt[i] << "\t\t" << tat[i] << endl;
    }
    // Printing Gantt Chart with completion time
    cout << " ";
    for (i = 0; i < n; i++) {
        for (int j = 0; j < processes[i]; j++) {
            cout << "--";
        }
        cout << " ";
    }
    cout << "\n|";
    int total_time = 0;
    for (i = 0; i < n; i++) {
        for (int j = 0; j < processes[i] - 1; j++) {
            cout << " ";
        }
        cout << "P" << i;
        for (int j = 0; j < processes[i] - 1; j++) {
            cout << " ";
        }
        cout << "|";
        total_time += processes[i];
    }
    cout << "\n ";

    // Printing completion time
    for (i = 0; i < total_time; i++) {
        cout << i << " ";
    }
    cout << endl;
    // Calculating average waiting time and turnaround time
    float avg_wt = 0, avg_tat = 0;
    for (i = 0; i < n; i++) {
        avg_wt += wt[i];
        avg_tat += tat[i];
    }
    avg_wt /= n;
    avg_tat /= n;
    cout << "Average Waiting Time: " << avg_wt << endl;
    cout << "Average Turnaround Time: " << avg_tat << endl;
}

int main() {
    int n, i;
    xyz:
    cout << "Enter the number of processes: ";
    cin >> n;
    if (n==0)
    {
        cout << "Enter the number of processes: ";
        goto xyz;
    }
    
    int processes[n];

    for (i = 0; i < n; i++) {
        try {
            cout << "Enter the burst time for process P" << i << ": ";
            cin >> processes[i];
            if (processes[i] <= 0) {
                throw "Invalid burst time entered!";
            }
        } catch (const char* msg) {
            cerr << msg << endl;
            i--;
        }
    }

    fcfs(processes, n);

    return 0;
}
