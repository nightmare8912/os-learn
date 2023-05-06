#include <iostream>
#include <time.h>
using namespace std;

#define MAX_PROC 10

int no_of_processes = 11, no_of_resources = 0;

void printMatrix(int mat[][MAX_PROC]);


void printArray(int arr[], int n)
{
    cout << endl;
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
}

void printMatrix(int mat[][MAX_PROC])
{
    cout << endl;
    for (int i = 0; i < no_of_processes; i++)
    {
        for (int j = 0; j < no_of_resources; j++)
            cout << mat[i][j] << "\t";
        cout << endl;
    }
}

void calculateNeed(int max[][MAX_PROC], int allocation[][MAX_PROC], int need[][MAX_PROC])
{
    for (int i = 0; i < no_of_processes; i++)
    {       
        for (int j = 0; j < no_of_resources; j++)
        {
            need[i][j] = max[i][j] - allocation[i][j];
            // cout << need[i][j] << "\t";
        }
            
    }
}

int findProcToExec(int work[], bool isFinished[], int need[][MAX_PROC])
{
    int rv = -1;
    for (int i = 0; i < no_of_processes; i++)
    {
        if (isFinished[i])
            continue;
        for (int j = 0; j < no_of_resources; j++)
        {
            if (need[i][j] > work[j])
                break;
            if (j == no_of_resources - 1)
            {
                rv = i;
                goto found_process;
            }
        }    
    }
found_process:
    return rv;
}

bool areAllFinished(bool isFinished[])
{
    for (int i = 0; i < no_of_processes; i++)
    {
        if (!isFinished[i])
            return false;
    }
    return true;
}

bool runSafety(int available[], int max[][MAX_PROC], int allocation[][MAX_PROC], int need[][MAX_PROC])
{
    bool isFinished[no_of_processes];
    int work[no_of_resources];
    for (int i = 0; i < no_of_processes; i++)
        isFinished[i] = false;
    for (int i = 0; i < no_of_resources; i++)
        work[i] = available[i];

    cout << "< ";

    while (true)
    {
        int pid = findProcToExec(work, isFinished, need);
        if (pid == -1)
            break;
        for (int i = 0; i < no_of_resources; i++)
            work[i] += allocation[pid][i];
        isFinished[pid] = true;    
        cout << "P" << pid << " ";       
    }
    cout << ">" << endl;
    return areAllFinished(isFinished);        
}

void requestAdditional(int available[], int max[][MAX_PROC], int allocation[][MAX_PROC], int need[][MAX_PROC])
{
    int pid;
    cout << "Enter the pid of the process making request: ";
    cin >> pid;
    int extra_need[no_of_resources];
    for (int i = 0; i < no_of_resources; i++)
    {
        cout << "Enter extra resources of type R" << i << " requested by P" << pid <<": ";
        cin >> extra_need[i];
    }
    for (int i = 0; i < no_of_resources; i++)
        need[pid][i] += extra_need[i];
    cout << "New need matrix: " << endl;
    printMatrix(need);    
    if (runSafety(available, max, allocation, need))   
        cout << "The request can be granted";
    else
        cout << "The request cannot be granted";
    for (int i = 0; i < no_of_resources; i++)
        need[pid][i] -= extra_need[i];    
    cout << endl; 
}

int main()
{
    srand((long int)clock());
    while (no_of_processes > MAX_PROC)
    {
        cout << "Enter number of processes: ";
        cin >> no_of_processes;
        if (no_of_processes > MAX_PROC)
        {
            cout << "Please enter a number less than " << MAX_PROC << endl;
            continue; 
        }
        cout << "Enter number of resources: ";
        cin >> no_of_resources;   
    }
    int max[no_of_resources][MAX_PROC], allocation[no_of_resources][MAX_PROC], need[no_of_resources][MAX_PROC], available[no_of_resources];
    for (int i = 0; i < no_of_resources; i++)
    {
        cout << "Enter the available instance of resource R" << i <<": ";
        // cin >> available[i];
        available[i] = rand() % 10 + 1;
        cout << available[i] << endl;
    }

    for (int i = 0; i < no_of_processes; i++)
    {
        for (int j = 0; j < no_of_resources; j++)
        {
            cout << "Enter max instance of resource type R" << j << " that can be requested by process P" << i << ": ";
            // cin >> max[i][j];
            max[i][j] = rand() % 10 + 1;
            cout << max[i][j] << endl;
            cout << "Enter the amount of instance of R" << j << " that has  been allocated to process P" <<i << ": ";
            // cin >> allocation[i][j];
            allocation[i][j] = rand() % max[i][j];
            cout << allocation[i][j] << endl;
        }
    }
    // getInput(available, max, allocation);
    calculateNeed(max, allocation, need);
    cout << "Available: ";
    printArray(available, no_of_resources);
    cout << "Max: ";
    printMatrix(max);
    cout << "Allocation: ";
    printMatrix(allocation);
    cout << "Need: ";
    printMatrix(need);
    if (runSafety(available, max, allocation, need))
        cout << "The system is in safe state";
    else
        cout << "The state is unsafe" << endl;
    cout << endl;    
    int opt = 1;
    while (opt != 0)
    {
        requestAdditional(available, max, allocation, need);
        cout << "Request again? (1/0): ";
        cin >> opt;
    }    
    return 0;
}