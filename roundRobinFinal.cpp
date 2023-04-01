#include <iostream>
#include <time.h>
using namespace std;
int idleTime = 0;
// sorts the processes in descending order of their arrival time
void sort(int arr[], int burst[], int n)
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = i + 1; j <= n; j++)
        {
            if (arr[i] < arr[j])
            {
                swap(arr[i], arr[j]);
                swap(burst[i], burst[j]);
                // swap(priority[i],priority[j]);
            }
        }
    }
}
int findSum(int burst[], int n)
{
    int sum = 0;
    for (int i = 1; i <= n; i++)
        sum += burst[i];
    return sum;
}
// returns true if the CPU is idle, otherwise false
bool isIdle(int arr[], int leftBurst[], int currTime, int n)
{
    for (int i = 1; i <= n; i++)
    {
        if (leftBurst[i] > 0 && currTime >= arr[i])
            return false;
    }
    return true;
}
// returns true if the cycle needs to restart, otherwise false
bool restartCycle(int arr[], int leftBurst[], int rrTime[], int sliceTime, int currTime, int n)
{
    for (int i = 1; i <= n; i++)
    {
        if (leftBurst[i] > 0 && currTime >= arr[i] && rrTime[i] < sliceTime)
            return false;
    }
    cout<<"CYCLE RESTART\n";
    return true;
}
// returns the index of the process to execute
int findProcToExec(int arr[], int leftBurst[], int rrTime[], int sliceTime, int currTime, int n)
{
    int pid = -1;
    if (restartCycle(arr, leftBurst, rrTime, sliceTime, currTime, n))
    {
        for (int i = 1; i <= n; i++)
            rrTime[i] = 0;
    }
    for (int i = n; i > 0; i--)
    {
        if (leftBurst[i]  > 0 && currTime >= arr[i] && rrTime[i] < sliceTime)
        {
            pid = i;
            break;
        }
    }
    return pid;
}
// executes the processes which are returned by the above function
void schedule(int arr[], int burst[], int finish[], int sliceTime, int n)
{
    sort(arr, burst, n);
    int leftBurst[n], rrTime[n];
    for (int i = 1; i <= n; i++)
    {
        leftBurst[i] = burst[i];
        rrTime[i] = 0;
    }
    int totTime = findSum(burst, n);
    for (int i = 0; i < totTime; i++) // i represents current time
    {
        if (!isIdle(arr, leftBurst, i, n))
        {
            // will be executed if CPU is not idle
            int pid = findProcToExec(arr, leftBurst, rrTime, sliceTime, i, n);
            leftBurst[pid]--;
            rrTime[pid]++;
            cout<<"Left burst "<<pid<<": "<<leftBurst[pid]<<"\trrTime "<<pid<<": "<<rrTime[pid]<<"\n";
            if (leftBurst[pid] == 0) // process finished its execution
                finish[pid] = i + 1; // storing the finish time as currTime
        }
        else
        {
            // will be executed if CPU is idle
            idleTime++;
            totTime++;
        }
    }
}
void printRes(int arr[], int burst[], int finish[], int n)
{
    cout << "process\t\tarrival\t\tburst\t\tfinish\n";
    for (int i = 1; i <= n; i++)
        cout << i << "\t\t" << arr[i] << "\t\t" << burst[i] << "\t\t" << finish[i] << "\n";
    cout << "Idle Time: " << idleTime << " seconds" <<"\n";
}
int main()
{
    int n;
    cout << "Enter number of processes: ";
    cin >> n;
    int arr[n], burst[n], tat[n], wait[n], finish[n];
    srand((long int)clock());
    for (int i = 1; i <= n; i++)
    {
        cout << "Enter arrival and burst time for process " << i << ": ";
        // cin>>arr[i]>>burst[i];
        arr[i] = rand() % 10;
        burst[i] = rand() % 10 + 1;
        cout << arr[i] << " " << burst[i] << "\n";
    }
    int sliceTime;
    cout << "Enter slice time: ";
    cin >> sliceTime;
    // sliceTime = rand () % 5 + 1;
    // cout << sliceTime << endl;
    schedule(arr, burst, finish, sliceTime, n);
    printRes(arr, burst, finish, n);
}