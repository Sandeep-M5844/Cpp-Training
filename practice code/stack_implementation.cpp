#include <iostream>
using namespace std;
class stack
{
    int* arr; //array to hold the stack elements
    int top;
    int capacity;
public:

    stack(int size)
    {
        arr = new int[size];
        capacity = size;
        top = -1;
    }

    bool isFull()
    {
        return top == capacity - 1;
    }

    bool isEmpty()
    {
        return top == -1;
    }

    void push(int val)
    {
        if (isFull())
        {
            cout << "stack overflow" << endl;
            return;
        }
        arr[++top] = val;
    }

    void pop()
    {
        if (isEmpty())
        {
            cout << "under flow" << endl;
            return ;
        }
    
        cout << "poped value" << arr[top]<<endl;
        top--;

    }

    void display()
    {
        if (isEmpty())
        {
            cout << "under flow" << endl;
            return;
        }
       for(int i =top;i>=0;--i)
        { 
            cout << arr[i]<<" ";
            
        }
    }

    int peek() {
        if (top < 0) {
            cout << "Stack is empty" << endl; // Added endl for better formatting
            return -1;
        }
        else {
            return arr[top]; // Return the top element without removing it
        }
    }


};
int main()
{
    stack s(11);
    for (int i = 0; i < 10; i++)
    {
        s.push(i);
    }
    s.display();
    return 0;
}

