#include <iostream>
#include <stdbool.h>
#include <stdlib.h>
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
bool isIdle(bool isComplete[], int arr[], int currTime, int n)
{
    int k;
    for (k = 1; k <= n; k++)
    {
        if (isComplete[k] == false && arr[k] <= currTime)
            return false;
    }
    // printf("Is Complete: %d \nArrival: %d \nCurrTime: %d\n", isComplete[k], arr[k], currTime);
    return true;
}
int findProcToExec(int currTime, int arr[], int leftBurst[], int n)
{
    int pid = -1, min = 999999999;
    for (int k = 1; k <= n; k++)
    {
        if (leftBurst[k] > 0 && currTime >= arr[k] && leftBurst[k] <= min)
        {
            min = leftBurst[k];
            pid = k;
        }
    }
    return pid;
}
void schedule(int arr[], int burst[], int finish[], bool isComplete[], int n)
{
    sort(arr, burst, n);
    int leftBurst[n];
    for (int i = 1; i <= n; i++)
        leftBurst[i] = burst[i];
    int totTime = findSum(burst, n);
    for (int i = 0; i < totTime; i++)
    {
        if (!isIdle(isComplete, arr, i, n))
        {
            int pid = findProcToExec(i, arr, leftBurst, n);
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
void printRes(int arr[], int burst[], int finish[], int wait[], int tat[], int n)
{
    printf("\nProc\t\tArr\t\tBurst\t\tFInish\t\tWait\t\tTAT\t\t\n\n");
    for (int i = 1; i <= n; i++)
    {
        printf("%d \t\t %d \t\t  %d \t\t   %d \t\t %d\t\t  %d\n", i, arr[i], burst[i], finish[i], wait[i], tat[i]);
    }
    printf("\nIdle Time: %d seconds\n", idleTime);
}
double findAvg(int array[], int n)
{
    double avg = 0;
    for (int i = 1; i <= n; i++)
        avg += array[i];
    return avg / n;
}
int main()
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    bool isComplete[n];
    int arr[n], burst[n], tat[n], wait[n], finish[n], avgWait, avgTat;
    srand((long int)clock());
    for (int i = 1; i <= n; i++)
    {
        printf("Enter the arrival and burst time for process %d: ", i);
        // scanf("%d %d", &arr[i], &burst[i]);
        arr[i] = rand() % 10;
        burst[i] = rand() % 10 + 1;
        isComplete[i] = false;
        printf("%d %d\n", arr[i], burst[i]);
    }
    // printf("\nARRIVAL: %d\nBurst: %d\nIsComplete: %d",arr[1],burst[1],isComplete[1]);
    schedule(arr, burst, finish, isComplete, n);
    calcTat(arr, finish, tat, n);
    calcWait(burst, tat, wait, n);
    printRes(arr, burst, finish, wait, tat, n);
    double waitTime, tatTime, finishTime;
    waitTime = findAvg(wait, n);
    tatTime = findAvg(tat, n);
    finishTime = findAvg(finish, n);

    printf("\nAvg wait Time: %d\nAvg TAT time: %d \nAvg finish Time: %d", waitTime, tatTime, finishTime);
}