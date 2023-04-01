#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include<time.h>
int idleTime = 0;
int findSum(int burst[], int n)
{
    int sum = 0;
    for (int i = 1; i <= n; i++)
        sum += burst[i];
    return sum;
}
bool isIdle(int leftBurst[], int arr[], int currTime, int n)
{
    for (int k = 1; k <= n; k++)
    {
        if (leftBurst[k] > 0 && arr[k] <= currTime)
            return false;
    }
    return true;
}
int findProcToExec(int currTime, int arr[], int leftBurst[], int n)
{
    int pid = -1, min = 999999999;
    for (int k = 1; k <= n; k++)
    {
        if (leftBurst[k] > 0 && currTime >= arr[k] && arr[k] < min)
        {
            min = arr[k];
            pid = k;
        }
    }
    return pid;
}
void schedule(int arr[], int burst[], int finish[],  int n)
{
    int leftBurst[n];
    for (int i = 1; i <= n; i++)
        leftBurst[i] = burst[i];
    int totTime = findSum(burst, n);
    for (int i = 0; i < totTime; i++)
    {
        if (!isIdle(leftBurst, arr, i, n))
        {
            int pid = findProcToExec(i, arr, leftBurst, n);
            leftBurst[pid]--;
            if (leftBurst[pid] == 0)
                finish[pid] = i + 1;        
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
int main()
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    int arr[n], burst[n], tat[n], wait[n], finish[n], avgWait, avgTat;
    srand((long int)clock());
    for (int i = 1; i <= n; i++)
    {
        printf("Enter the arrival and burst time for process %d: ", i);
        arr[i] = rand() % 100;
        burst[i] = rand() % 10 + 1;
        printf("%d %d\n", arr[i], burst[i]);
    }

    schedule(arr, burst, finish, n);
    calcTat(arr, finish, tat, n);
    calcWait(burst, tat, wait, n);
    printRes(arr, burst, finish, wait, tat, n);
}