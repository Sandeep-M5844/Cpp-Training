
#include <iostream>
using namespace std;

class node
{
public:
    node* next;
    int data;
    node(int val) { data = val; }
};
// the storage is done in LL based on the top.
// the top elements next points to the next element which is 2nd most top
class stack
{
private:
    node* top;
    int no_of_elements_in_stack;
public:
    stack()
    {
        no_of_elements_in_stack = 0;
    }

    void push(int value)
    {
        node* newnode = new node(value);

       
      
            newnode->next = top;
            top = newnode;
       
    }

    bool is_empty()
    {
        return top == nullptr;
    }

    void pop()
    {
        if (is_empty())
        {
            cout << "under flow" << endl;
        }

        node* temp = top;
        top = top->next;
        cout << temp->data << "is poped" << endl;
        delete temp;
       
    }

    void display()
    {
        while (top != nullptr)
        {
            cout << top->data <<endl;
            top = top->next;
        }
    }

    int peek()
    {
        return top->data;
    }

};


int main()
{
    std::cout << "Hello World!\n";

    stack s;
    for (int i = 0; i < 10; i++)
    {
        s.push(i);
    }
    s.pop();
    s.display();
}

