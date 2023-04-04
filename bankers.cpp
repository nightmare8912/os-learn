#include <iostream>
using namespace std;
int main()
{
    int num_resources, num_processes;
    cout << "Enter resources available and the number of processes: ";
    cin >> num_resources >> num_processes;
    int available[num_resources], max[num_processes][num_resources]; 
    int allocation[num_processes][num_resources], need[num_processes][num_resources];   
    // execute(available, max, allocation, need, num_processes, num_resources);
       
}