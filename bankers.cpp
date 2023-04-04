#include <iostream>
#include <time.h>
using namespace std;
class returnType
{
    public:
    int resource_number, pid;
    returnType()
    {
        resource_number = -1;
        pid =-1;
    }
};
// randomly initializes the matrices
void getInput(int available[], int max[][10], int allocation[][10], int need[][10], int num_processes, int num_resources)
{   
    cout << "Enter the values for available resources" << endl;
    for (int i = 0; i < num_resources; i++)
    {
        printf("Enter available instances of R%d: ", i);
        // cin >> available[i];
        available[i] = rand() % 10;
        cout << available[i] << endl;
    }
    for (int i = 0; i < num_processes; i++)
    {
        for (int j = 0; j < num_resources; j++)
        {
            printf ("Enter the maximum resources that P%d may request of resource type R%d: ", i, j);
            // cin >> max[i][j];
            max[i][j] = rand () % 10 + 1;
            cout << max[i][j] << endl;
            printf ("Enter the resources that P%d has been allocated of resource type R%d: ", i, j);
            // cin >> allocation[i][j];
            allocation[i][j] = rand() % max[i][j];
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
// returns the process id (index) of the process along with the resource id (index) of the resource that can be allocated to it
// returns -1 as pid, if no such process can be found
returnType findProcToExec(returnType r, int need[][10], bool finish[], int work[], int num_processes, int num_resources)
{
    r.pid = -2;
    for (int i = 0; i < num_processes; i++)
    {
        for (int j = 0; j < num_resources; j++)
        {
            if (finish[i] == false && need[i][j] <= work[j])
            {
                r.pid = i;
                r.resource_number = j;
                return r;
            }
        }
    }
    return r;
}
// executes the processes one by one
void execute(int available[], int max[][10], int allocation[][10], int need[][10], int num_processes, int num_resources)
{
    // Initializing
    bool finish[num_processes];
    int work[num_resources];
    returnType r;
    for (int i = 0; i < num_resources; i++)
    {
        work[i] = available[i];
        finish[i] = false;
    }
    cout << endl;
    while(r.pid != -2)
    {
        r = findProcToExec(r, need, finish, work, num_processes, num_resources);
        if (r.pid == -2)
            break;
        work[r.resource_number] = work[r.resource_number] + allocation[r.pid][r.resource_number]; // increasing the number of avaialble resources, as after processes finishes its execution, it frees its already held resources
        finish[r.pid] = true;
        cout << "P" << r.pid << "\t"; // prints the process, so we can see in what order were the processes executed
    }
    cout << endl;
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
    if (num_processes > 10)
        num_processes = 10;
    int available[num_resources], max[num_processes][10]; 
    int allocation[num_processes][10], need[num_processes][10];  
    getInput(available, max, allocation, need, num_processes, num_resources); 
    // execute(available, max, allocation, need, num_processes, num_resources);
    print(available, max, allocation, need, num_processes, num_resources); 
    execute(available, max, allocation, need, num_processes, num_resources);
}