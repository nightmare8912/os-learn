#include <iostream>
#include<time.h>
using namespace std;
int idleTime = 0;
int findSum(int burst[], int n)
{
    int sum = 0;
    for (int i = 1; i <= n; i++)
        sum += burst[i];
    return sum;
}
double findAvg(int array[], int n)
{
    double avg = 0;
    for (int i = 1; i <= n; i++)
        avg += array[i];
    return avg / n;
}
bool isIdle(bool isComplete[], int arr[], int currTime, int n)
{
    int k;
    for (k = 1; k <= n; k++)
    {
        if (isComplete[k] == false && arr[k] <= currTime)
            return false;
    }
    return true;
}
bool restartCycle(int arr[], int leftBurst[], int rrTime[], int currTime, int sliceTime, int currElement, int n)
{
    for (int i = 1; i <= n; i++)
    {
        if (leftBurst[i] > 0 && currTime >= arr[i] && currElement == n + 1)
        {
            // cout << "CYCLE RESTART" << endl;
            return true;
        }
    }
    return false;
}
void sort(int arr[], int burst[], int n)
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = i + 1; j <= n; j++)
        {
            if (arr[i] > arr[j])
            {
                swap(arr[i], arr[j]);
                swap(burst[i], burst[j]);
            }
        }
    }
}
void printRes(int arr[], int burst[], int finish[], int wait[], int tat[], int n)
{
    printf("\nProc\t\tArr\t\tBurst\t\tFInish\t\tWait\t\tTAT\t\t\n\n");
    for (int i = 1; i <= n; i++)
    {
        printf("%d \t\t %d \t\t  %d \t\t   %d \t\t %d\t\t  %d\n", i, arr[i], burst[i], finish[i], wait[i], tat[i]);
    }
    // printf("\nIdle Time: %d seconds\n", idleTime);
}
int findProcToExec(int arr[], int leftBurst[], int rrTime[], int sliceTime, int currTime, int n)
{
    int pid = -1;
    for (int i = 1; i <= n + 1; i++)
    {
        if (restartCycle(arr, leftBurst, rrTime, currTime, sliceTime, i, n))
        {
            for (int j = 1; j <= n; j++)
                rrTime[j] = 0;
            i = 0;
            pid = -1;
        }
        if (leftBurst[i] > 0 && rrTime[i] < sliceTime && arr[i] <= currTime)
        {
            // leftBurst[i]--;
            // rrTime[i]++;
            // cout << "Left Burst " << i << ": " << leftBurst[i] << "\trrTime " << i << ": " << rrTime[i] << "\n";
            pid = i;
        }
        if (pid != -1 && pid != 0)
            return pid;
    }
    return pid;
}
void schedule(int arr[], int burst[], int finish[], bool isComplete[], int sliceTime, int n)
{
    sort(arr, burst, n);
    int rrTime[n], leftBurst[n];
    for (int i = 1; i <= n; i++)
    {
        leftBurst[i] = burst[i];
        rrTime[i] = 0;
    }
    int totTime = findSum(burst, n);
    for (int i = 0; i < totTime; i++)
    {
        if (isIdle(isComplete, arr, i, n) == false)
        {
            int pid = findProcToExec(arr, leftBurst, rrTime, sliceTime, i, n);
            if (pid != -1)
            {
                leftBurst[pid]--;
                rrTime[pid]++;
                if (leftBurst[pid] == 0)
                {
                    finish[pid] = i + 1;
                    isComplete[pid] = true;
                }
            }
        }
        else
        {
            idleTime++;
            totTime++;
        }
    }
    cout << "\n------\n"<< "Idle Time: " << idleTime << " seconds" << endl;
}
void calcTat(int arr[], int finish[], int tat[], int n)
{
    for (int i = 1; i <= n; i++)
        tat[i] = finish[i] - arr[i];
}

void calcWait(int burst[], int tat[], int wait[], int n)
{
    for (int i = 1; i <= n; i++)
        wait[i] = tat[i] - burst[i];
}
int main()
{
    int n;
    cout << "Enter number of processes: ";
    cin >> n;
    int arr[n], burst[n], wait[n], finish[n], tat[n], sliceTime;
    double waitTime, tatTime, finishTime;
    bool isComplete[n];
    srand((long int)clock());
    for (int i = 1; i <= n; i++)
    {
        cout << "Enter arrival and burst time for process " << i << ": ";
        // cin>>arr[i]>>burst[i];
        arr[i] = rand()%10;
        burst[i] = rand()%10 + 1;
        isComplete[i] = false;
        cout << arr[i] << " " << burst[i] << "\n";
        
    }

    cout << "Enter slice time: ";
    cin >> sliceTime;

    schedule(arr, burst, finish, isComplete, sliceTime, n);
    calcTat(arr, finish, tat, n);
    calcWait(burst, tat, wait, n);
    printRes(arr, burst, finish, wait, tat, n);

    waitTime = findAvg(wait, n);
    tatTime = findAvg(tat, n);
    finishTime = findAvg(finish, n);

    cout << "\nAvg wait Time: " << waitTime << "\nAvg TAT time: " << tatTime << "\nAvg finish Time: " << finishTime;
}