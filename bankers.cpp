#include <iostream>
#include <time.h>
using namespace std;
// randomly initializes the matrices
void getInput(int available[], int max[][10], int allocation[][10], int need[][10], int num_processes, int num_resources)
{   
    cout << "Enter the values for available resources" << endl;
    for (int i = 0; i < num_resources; i++)
    {
        printf("Enter available instances of R%d: ", i);
        cin >> available[i];
        // available[i] = rand() % 10;
        // cout << available[i] << endl;
    }
    for (int i = 0; i < num_processes; i++)
    {
        for (int j = 0; j < num_resources; j++)
        {
            printf ("Enter the maximum resources that P%d may request of resource type R%d: ", i, j);
            cin >> max[i][j];
            // max[i][j] = rand () % 10 + 1;
            // cout << max[i][j] << endl;
            printf ("Enter the resources that P%d has been allocated of resource type R%d: ", i, j);
            // cin >> allocation[i][j];
            allocation[i][j] = rand() % (max[i][j] + 1);
            cout << allocation[i][j] << endl;
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}
void print(int available[], int max[][10], int allocation[][10], int need[][10], int num_processes, int num_resources)
{
    cout << "Printing available matrix: " << endl;
    for (int i = 0; i < num_resources; i++)
        cout << available[i] << "\t";
    cout << endl;    
    cout << "Printing max matrix: " << endl;
    for (int i = 0; i < num_processes; i++)
    {
        for (int j = 0; j < num_resources; j++)
            cout << max[i][j] << "\t";
        cout << endl;    
    }    
    cout << "Printing allocation matrix: " << endl;
    for (int i = 0; i < num_processes; i++)
    {
        for (int j = 0; j < num_resources; j++)
            cout << allocation[i][j] << "\t";
        cout << endl;    
    }    
    cout << "Printing need matrix: " << endl;
    for (int i = 0; i < num_processes; i++)
    {
        for (int j = 0; j < num_resources; j++)
            cout << need[i][j] << "\t";
        cout << endl;    
    }    
}
// returns true if all the processes have been completed otherwise false
bool isComplete(bool finish[], int num_processes)
{
    for (int i = 0; i < num_processes; i++)
    {
        if (!finish[i])
            return false;
    }
    return true;
}
// returns the process id (index) of the process that can be executed otherwise returns -1 if no such process can be found
int findProcToExec(int need[][10], bool finish[], int work[], int num_processes, int num_resources)
{
    int pid = -2;
    for (int i = 0; i < num_processes; i++)
    {
        for (int j = 0; j < num_resources; j++)
        {
            if (finish[i] == false && need[i][j] <= work[j])
                pid = i;
            else   
            {
                pid = -2;
                break;
            } 
        }
        if (pid != -2)
            goto found_process;
    }
    found_process:
        return pid;
}
// executes the processes one by one
void execute(int available[], int max[][10], int allocation[][10], int need[][10], int num_processes, int num_resources)
{
    // Initializing
    bool finish[num_processes];
    int work[num_resources];
    for (int i = 0; i < num_resources; i++)
    {
        work[i] = available[i];
        finish[i] = false;
    }
    cout << endl;
    int pid = -1;
    cout << "<  ";
    while(pid != -2)
    {
        pid = findProcToExec(need, finish, work, num_processes, num_resources);
        if (pid == -2)
            break;
        for (int i = 0; i < num_resources; i++)
            work[i] = work[i] + allocation[pid][i]; // increasing the number of avaialble resources, as after processes finishes its execution, it frees its already held resources
        finish[pid] = true;
        cout << "P" << pid << "  "; // prints the process, so we can see in what order were the processes executed
    }
    cout << ">" <<endl;
    if(isComplete(finish, num_processes))
        cout << "The system is in a safe state" << endl;
    else // this part is executed when atleast one process cannot be executed as its requirement cannot be met
        cout << "The system is not in a safe state" << endl;    
}
int main()
{
    int num_resources, num_processes;
    cout << "Enter resources available and the number of processes: ";
    cin >> num_resources >> num_processes;
    srand((long int)clock());
    // max number of processes allowed is 10 here
    if (num_resources > 10)
        num_resources = 10;
    int available[num_resources], max[num_processes][10]; 
    int allocation[num_processes][10], need[num_processes][10];  
    getInput(available, max, allocation, need, num_processes, num_resources); 
    print(available, max, allocation, need, num_processes, num_resources); 
    execute(available, max, allocation, need, num_processes, num_resources);
}
