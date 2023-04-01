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
void sort(int arr[], int burst[], int priority[],int n)
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = i + 1; j <= n; j++)
        {
            if (arr[i] < arr[j])
            {
                swap(arr[i], arr[j]);
                swap(burst[i], burst[j]);
                swap(priority[i],priority[j]);
            }
        }
    }
}
void printRes(int arr[], int burst[], int finish[], int wait[], int tat[],int priority[], int n)
{
    printf("\nProc\t\tArr\t\tBurst\t\tPriority\t\tFInish\t\tWait\t\tTAT\t\t\n\n");
    for (int i = 1; i <= n; i++)
        printf("%d \t\t %d \t\t %d \t\t  %d \t\t \t  %d \t\t %d\t\t  %d\n", i, arr[i], burst[i], priority[i],finish[i], wait[i], tat[i]);
    
}
int findProcToExec(int arr[], int leftBurst[], int priority[], int currTime, int n)
{
    int pid = -1, max = 999999999;
    for (int k = 1; k <= n; k++)
    {
        if (leftBurst[k] > 0 && currTime >= arr[k] && priority[k] <= max)
        {
            max = priority[k];
            pid = k;
        }
    }
    return pid;
}
void schedule(int arr[], int burst[], int finish[], bool isComplete[], int prioirty[], int n)
{
    sort(arr, burst, prioirty, n);
    int leftBurst[n];
    for (int i = 1; i <= n; i++)
        leftBurst[i] = burst[i];

    int totTime = findSum(burst, n);
    for (int i = 0; i < totTime; i++)
    {
        if (isIdle(isComplete, arr, i, n) == false)
        {
            int pid = findProcToExec(arr, leftBurst, prioirty, i, n);
            if (pid != -1)
            {
                leftBurst[pid]--;
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
    int arr[n], burst[n], wait[n], finish[n], tat[n], priority[n];
    double waitTime, tatTime, finishTime;
    bool isComplete[n];
    srand((long int)clock());
    for (int i = 1; i <= n; i++)
    {
        cout << "Enter arrival, burst time and priority for process " << i << ": ";
        arr[i] = rand() % 10;
        arr[i] = rand()%10;
        burst[i] = rand()%10 + 1;
        priority[i]=rand()%7;
        isComplete[i] = false;
        cout << arr[i] << " " << burst[i] <<" " << priority[i] << "\n";
        
    }
    schedule(arr, burst, finish, isComplete, priority, n);
    calcTat(arr, finish, tat, n);
    calcWait(burst, tat, wait, n);
    printRes(arr, burst, finish, wait, tat, priority,n);

    waitTime = findAvg(wait, n);
    tatTime = findAvg(tat, n);
    finishTime = findAvg(finish, n);

    cout << "\nAvg wait Time: " << waitTime << "\nAvg TAT time: " << tatTime << "\nAvg finish Time: " << finishTime;
} 