#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    int n;
xyz:
    cout << "Enter the number of processes: ";
    cin >> n;
    if (n <= 0)
    {
        cout << "Number of Processes can't be zero\n\n";
        goto xyz;
    }

    double burst_time[n], waiting_time[n], turnaround_time[n], avg_waiting_time = 0, avg_turnaround_time = 0;
    cout << fixed << setprecision(2);

bool exception_occurred = false;
for (int i = 0; i < n; i++)
{
    cout << "Enter the burst time for process P" << i << ": ";
    cin >> burst_time[i];
    if (burst_time[i] <= 0)
    {
        cerr << "Error: Burst time should be greater than 0." << endl;
        exception_occurred = true;
        i--; // to repeat this iteration
    }
}

if (exception_occurred)
{
    // cout << "Please re-enter the burst time for the processes with invalid input:\n";
    for (int i = 0; i < n; i++)
    {
        if (burst_time[i] <= 0)
        {
            cout << "Enter the burst time for process P" << i << ": ";
            cin >> burst_time[i];
        }
    }
}

    waiting_time[0] = 0;
    turnaround_time[0] = burst_time[0];

    for (int i = 1; i < n; i++)
    {
        waiting_time[i] = turnaround_time[i - 1];
        turnaround_time[i] = waiting_time[i] + burst_time[i];
    }

    cout << "\nProcess  Burst Time      Waiting Time    Turnaround Time         Completion Time\n";

    for (int i = 0; i < n; i++)
    {
        cout << "P" << i << setw(13) << burst_time[i] << setw(18) << waiting_time[i] << setw(18) << turnaround_time[i] << setw(25) << turnaround_time[i] + waiting_time[0] << "\n";
        avg_waiting_time += waiting_time[i];
        avg_turnaround_time += turnaround_time[i];
    }

    cout << "\nGantt Chart:\n";
    cout << "-----------";
    for (int i = 0; i < n; i++)
    {
        cout << "|      P" << i << "      ";
    }
    cout << "|\n";
    cout << "         ";

    cout << setw(4) << "0.00";
    for (int i = 0; i < n; i++)
    {
        cout << setw(16) << turnaround_time[i];
    }
    cout << "\n";

    avg_waiting_time /= n;
    avg_turnaround_time /= n;

    cout << "\nAverage Waiting Time: " << avg_waiting_time << "\n";
    cout << "Average Turnaround Time: " << avg_turnaround_time;

    return 0;
}
