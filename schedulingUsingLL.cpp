#include <iostream>
#include <time.h>
using namespace std;
struct node
{
    int arr, burst, leftBurst, finish, tat, wait;
    node *next;
};
class queue
{
public:
    int count;
    node *head;
// public:
    queue()
    {
        count = 0;
        head = NULL;
    }
    void insert(node *newnode)
    {
        node *temp = head;
        if (head == NULL)
            head =  newnode;
        else
        {
            while (temp->next != NULL)
                temp = temp->next;
            temp->next = newnode;
        }
        count++;
    }
    void del()
    {
        node *temp = head;
        head = head->next;
        delete temp;
        count--;
        if (count == 0)
            head = NULL;
    }
    bool isEmpty()
    {
        if (head == NULL)
            return true;
        return false;    
    }
    void copy(queue wait, queue ready)
    {   
        node *wait_temp = wait.head;
        while (wait_temp != NULL)
        {
            cout << "hi";
            ready.insert(wait_temp);
            wait_temp = wait_temp->next;
        }
    }
    void print()
    {
        node *temp = head;
        cout << endl;
        while (temp != NULL)
        {
            cout << temp->arr<<" ";
            temp = temp->next;
        }
        cout << endl;
    }
};
node *createNode(int arr, int burst)
{
    node *newnode = new node;
    newnode->arr = arr;
    newnode->burst = newnode->leftBurst = burst;
    newnode->finish = newnode->tat = newnode->wait = 0;
    newnode->next = NULL;
    return newnode;
}
void schedule(queue wait, queue ready)
{
    queue temp;
    temp.copy(wait, ready);
    wait.print();

}
int main()
{
    int n;
    queue ready, wait;
    cout << "Enter number of processes: ";
    cin >> n;
    srand((long int)clock());
    for (int i = 0; i < n; i++)
    {
        cout << "Enter arrival time and burst time for process "<<i+1<<": ";
        node *temp = createNode(rand() % 10, rand() % 10+1);
        cout << temp->arr<<" "<<temp->burst<<"\n";
        wait.insert(temp);
    }
    // wait.print();
    schedule(wait, ready);
}