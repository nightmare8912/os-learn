#include <iostream>
#include <time.h>
#define INT_MAX 99999
using namespace std;

int getArmMovement(int start_pos, int end_pos)
{
    int rv = start_pos - end_pos;
    if (rv >= 0)
        return rv;
    else
        return -rv;
}

int findNext_fifo(int disk_req[], bool isComplete[], int prevPos, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (!isComplete[i])
            return i;
    }
    return -1;
}

int fifo(int disk_req[], int prevPos, int n)
{
    int totArmMovement = 0;
    bool isComplete[n];
    for (int i = 0; i < n; i++)
        isComplete[i] = false;
    
    while (true)
    {
        int index = findNext_fifo(disk_req, isComplete, prevPos, n);
        if (index == -1)
            break;
        totArmMovement += getArmMovement(prevPos, disk_req[index]);
        cout << "Disk Req: " <<disk_req[index] << "\n" << "Arm mov: " << getArmMovement(prevPos, disk_req[index]) << "\n";
        isComplete[index] = true;
        prevPos = disk_req[index];
    }
    return totArmMovement;
}

int findNext_sstf(int disk_req[], bool isComplete[], int prevPos, int n)
{
    int rv = -1, min = INT_MAX;
    for (int i = 0; i < n; i++)
    {
        if (!isComplete[i] && min > getArmMovement(prevPos, disk_req[i]))
        {
            min = getArmMovement(prevPos, disk_req[i]);
            rv = i;
        }
    }
    return rv;
}

int sstf(int disk_req[], int prevPos, int n)
{
    int totArmMovement = 0;
    bool isComplete[n];
    for (int i = 0; i < n; i++)
        isComplete[i] = false;
    
    while (true)
    {
        int index = findNext_sstf(disk_req, isComplete, prevPos, n);
        if (index == -1)
            break;
        totArmMovement += getArmMovement(prevPos, disk_req[index]);
        cout << "Disk Req: " << disk_req[index] << "\n" << "Arm mov: " << getArmMovement(prevPos, disk_req[index]) << "\n";
        isComplete[index] = true;
        prevPos = disk_req[index];
    }
    return totArmMovement;
}

int main()
{
    int n;
    cout << "Enter number of disk requests: ";
    cin >> n;

    int disk_req[n];
    srand((long int)clock());
    for (int i = 0; i < n; i++)
        disk_req[i] = rand() % 200;
    
    cout << "Disk requests: ";
    for (int i = 0; i < n; i++)
        cout << disk_req[i] << " ";
    cout << "\n";
    int headPos;
    cout << "Enter head pos: ";
    cin >> headPos;
    cout << "\n\nFIFO : " << fifo(disk_req, headPos, n) << "\n\n";
    cout << "\n\nSSTF : " << sstf(disk_req, headPos, n);
}