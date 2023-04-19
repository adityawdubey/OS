#include<bits/stdc++.h>
using namespace std;
struct Process {
   int pid; // Process ID
   int bt; // CPU Burst time required
   int priority; // Priority of this process
};

bool compare(Process a, Process b) {
   return (a.priority > b.priority);
}
void waitingtime(Process pro[], int n, int wt[]) {
   // Initial waiting time for a process is 0
   wt[0] = 0;
   for (int i = 1; i < n ; i++ )
      wt[i] = pro[i-1].bt + wt[i-1] ;
}

void turnarround( Process pro[], int n, int wt[], int tat[]) {
   for (int i = 0; i < n ; i++)
      tat[i] = pro[i].bt + wt[i];
}

void avgtime(Process pro[], int n) {
   int wt[n], tat[n], total_wt = 0, total_tat = 0;
   waitingtime(pro, n, wt);
   turnarround(pro, n, wt, tat);
   //Display 
   cout << "\nProcesses "<< " Burst time " << " Waiting time " << " Turn around time\n";
   // Calculate total waiting time and total turn around time
   for (int i=0; i<n; i++) {
      total_wt = total_wt + wt[i];
      total_tat = total_tat + tat[i];
      cout << " " << pro[i].pid << "\t\t" << pro[i].bt << "\t " << wt[i] << "\t\t " << tat[i] <<endl;
   }
   cout << "\nAverage waiting time = " << (float)total_wt / (float)n;
   cout << "\nAverage turn around time = " << (float)total_tat / (float)n;
}
void scheduling(Process pro[], int n) {
   // Sort processes by priority
   sort(pro, pro + n, compare);
   cout<< "Order in which processes gets executed \n";
   for (int i = 0 ; i < n; i++)
      cout << pro[i].pid <<" " ;
   avgtime(pro, n);
}

int main() {
//   Process pro[] = {{1, 10, 2}, {2, 5, 0}, {3, 8, 1}};
   int size;
   cout<<"Enter number of processes: ";
   cin>>size;
   Process pro[size];
   for(int i=1;i<size+1;i++){
       cout<<"Enter the process no: ";
       cin>>pro[i].pid;
       cout<<"Enter the Burst Time for "<<i<<" process no: ";
       cin>>pro[i].bt;
       cout<<"Enter the priority for "<<i<<" process no: ";
       cin>>pro[i].priority;
       cout<<endl;

   }
   int n = sizeof pro / sizeof pro[0];
   scheduling(pro, n);
   return 0;
}






















