
#include <iostream>
using namespace std;
class node
{
public:
    int data;
    node* next;
public:
    node(int value)
    {
        data = value;
        next = nullptr;
    }
};

class Queue
{
    node* front;
    node* rear;
    int count = 0;
public:
    Queue()
    {
        front = nullptr; // head
        rear = nullptr; // tail
        count = 0;
    }

    bool isEmpty()
    {
        return front == nullptr; // if head is null returning the empty
    }

    int Enqueue(int value)
    {
        node* newnode = new node(value);

        if (isEmpty())
        {
            front = rear = newnode; // if head == nullptr then seting the tail and head to newnode
            count++;
            return value;

        }

        rear->next = newnode;//updating the tail as the inserion is done
        rear = newnode;

        rear->next = front;// always make it circular so that tail->next points to head;
        count++;
    }

    int dequeue()
    {
        if (isEmpty())
        {
            cout << "no data" << endl;
            return -1;
        }

        node* temp = front;

        int value_deleted = front->data; 
        front = front->next; // updating the head as deletion is done from the front
        // for circular Queue
        rear->next = front; // as we are deleting the head in dequeue , so the circular link get failed , 
        //that is updating the rear pointer to the updated head

        if (front == nullptr)
        {
            rear = nullptr;
        }

        count--;
        return value_deleted;
    }

    void display()
    {
        cout << "data in Queue:" << endl;
        if (isEmpty())
        {
            cout << "empty";
            return;
        }
        node* current = front;
        while (current != nullptr)
        {
            cout << current->data;
            current = current->next;
        }



    }

    int peek() // element at the last
    {
        if (isEmpty())
        {
            cout << "empty";
            return -1;
        }

        else
            return rear->data;
    }
};
int main()
{

    Queue q;

    // Enqueue elements
    for (int i = 1; i <= 10; i++) {
        q.Enqueue(i * 10);
        cout << "Enqueued: " << i * 10 << endl;
    }

    q.dequeue();

    q.display();

    cout << endl<<"the peek elememnt" << q.peek()<<endl;
    
}
