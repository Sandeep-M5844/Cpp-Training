// LinkedList.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;
class node
{
public:
    int data;
    node* next;
   
public:
    node(int val)
    {
        data = val;
        next = nullptr;
    }
};

class LinkedList
{
public:
    // insertion 
    int list_it = 0;
    node* head = nullptr;
    int no_of_list_elements = 0;

    void insertAtEnd(int value)
    {
        node* newnode = new node(value);
        if (head == nullptr)
        {
            head = newnode;
            no_of_list_elements++;

        }
        else
        {
            node* current = head;
            while (current->next!= nullptr)
            {
                current = current->next;
            }
            current->next = newnode;
            no_of_list_elements++;

        }
    }

    void insertAtBegin(int val)
    {
        node* newnode = new node(val);
        if (head == nullptr)
        {
            head = newnode;
            no_of_list_elements++;
        }
        else
        {
            newnode->next = head;
            head = newnode;
            no_of_list_elements++;
        }
    }

    void insertbypos(int pos, int val)
    {
        node* newnode = new node(val);
        int count = 1;
        node* current = head;
        
        
        if (pos == 1)
        {
            newnode->next = head;
            head = newnode;
            no_of_list_elements++;

            return;
        }
        while (current!= nullptr && count < pos-1) // inorder to check the head we can directly do current!=null
        {
            current = current->next;
            count++;
        }

        if (current == nullptr)
        {
            cout << "bound error";
            delete newnode;
            return;
        }
        newnode->next = current->next;
        current->next = newnode;
        no_of_list_elements++;

    }

    void insertAtMiddle(int value)
    {
        int midpos = no_of_list_elements / 2;
        node* newnode = new node(value);
        int count = 1;

        if (head == nullptr)
        {
            head = newnode;
            no_of_list_elements++;
            return;
        }

        node* current = head;

        while (current != nullptr && count < midpos)
        {
            current = current->next;
            count++;
        }

        newnode->next = current->next;
        current->next = newnode;
        no_of_list_elements++;



    }

    void display()
    {
        node* current = head;
        if (head == nullptr)
        {
            cout << "empty list" << endl;
        }
        while (current != nullptr)
        {
            cout << current->data << "->";
            current = current->next;
        }
        cout << "null" << endl;
    }

    int listElements()
    {
        return no_of_list_elements;
    }

    void deleteAtEnd()
    {
        if (head == nullptr)
        {
            cout << "no elements to delete" << endl;
            return;

        }

        if (head->next == nullptr)
        {
            delete head;
            head = nullptr;
            no_of_list_elements--;
            return;
        }
        node* current = head;
        node* prev = nullptr;

        while (current->next != nullptr)
        {
            prev = current;
            current = current->next;
        }
        prev->next = nullptr;
        delete current;
        current = nullptr;
        no_of_list_elements--;
        

    }

    void deleteAtBegin()
    {
        node* current = head;
        if (head == nullptr)
        {
            cout << "no element to delete" << endl;
            return;
        }

        if (head->next == nullptr)
        {
            delete head;
            head = nullptr;
            no_of_list_elements--;
            return;
        }

        head = head->next;
        delete current;
        no_of_list_elements--;
    }

    void deletebyvalue(int value)
    {
        node* current = head;
        node* prev = nullptr;

        if (head == nullptr)
        {
            cout << "no element to delete" << endl;
            return;
        }

        if (head->data == value)
        {
            delete head;
            head = nullptr;
            no_of_list_elements--;
            return;
        }

        while (current != nullptr && current->data != value)
        {
            prev = current;
            current = current->next;
        }

        if (current == nullptr)
        {
            cout << "value not found" << endl;
            
            return;
        }

        prev->next = current->next;
        delete current;
        current = nullptr;
        no_of_list_elements--;

        
    }

    void deleteByPos(int pos)
    {
        int count = 1;
        node* current = head;
        node* prev = nullptr;

        if (head == nullptr)
        {
            cout << "no element to delete" << endl;
            return;
        }

        if (pos == 1)
        {
            head = head->next;
            delete current;
            no_of_list_elements--;

            return;
        }

        while (current != nullptr && count < pos)
        {
            prev = current;
            current = current->next;
            count++;
        }

        if (current == nullptr)
        {
            cout << "pos out of bound" << endl;
            return;
        }

        prev->next = current->next;
        delete current;
        no_of_list_elements--;
    }

    void DeleteAtMiddle()
    {
        int count = 1;
        node* current = head;
        node* prev = nullptr;

        if (head == nullptr)
        {
            cout << "no element to delete" << endl;
            return;
        }

        if (no_of_list_elements == 1) // head->next = null;
        {
            delete head, current;
            no_of_list_elements--;
            return;
        }

        int midpos = no_of_list_elements / 2;

        while (current != nullptr && count < midpos)
        {
            prev = current;
            current = current->next;
            count++;

        }
        
        prev->next = current->next;
        delete current;
        no_of_list_elements--;
    }

    void searching(int value)
    {
        if (head == nullptr)
        {
            cout << "no element to search" << endl;
            return;
        }
        node* current = head;
        int count = 1;

        while (current != nullptr)
        {
            if (current->data == value)
            {
                cout << current->data << ": is avalilable at position : " << count << endl;
                return;
            }
            current = current->next;
            
            count++;
        }

        cout << "value is not found" << endl;
    }

    void reverseList()
    {
        if (head == nullptr)
        {
            cout << "no element to search" << endl;
            return;
        }
        node* nextnode = nullptr;
        node* current = head;
        node* prev = nullptr;
        while (current != nullptr)
        {
            nextnode = current->next;
            current->next = prev;
            prev = current;
            current = nextnode; // nc of current
        }
        head = prev; // this is because after all travesal the last node will be the prev which 
        //is current so making the head as previous
    }

    node* reverseListElementsByGroup(node* head, int k)
    {
        if (head == nullptr)
        {
            cout << "no element to search" << endl;
            return nullptr;
        }

        node* prev = nullptr;
        node* nextnode = nullptr;
        node* current = head;
        int count = 0;

        while (current != nullptr && count<k)
        {
            nextnode = current->next;
            current->next = prev;
            prev = current;
            current = nextnode;
            list_it++;
            count++;
        }

        if (nextnode != nullptr && (no_of_list_elements - list_it) >= k)
            // this to reverse by group it the let over elements less then the K then we wont reverse
        {
            head->next = reverseListElementsByGroup(nextnode, k);
            // this is because as pre = current , so prev will poin to the K so updating the head to
            // prev to iterate next 
        }

        else
        {
            head->next = current;
        }
        return prev;

        

    }

    void reverseListByGroup(int k)
    {
        head = reverseListElementsByGroup(head, k);
    }

    void sort()
    {
        

        if (head == nullptr)
        {
            cout << "no element to sort" << endl;
            
        }

        node* current = head;
       // node* lastnode = nullptr;
       // node* prev = nullptr;
        bool swaped;
        
        do
        {
            swaped = false;
            current = head;
            while (current->next != nullptr)
            {
                int temp;

                if (current->data > current->next->data)
                {
                    temp = current->data;
                    current->data = current->next->data;
                    current->next->data = temp;
                    swaped = true;
                }
                current = current->next;

            }
          //  lastnode = current; .. if we use this it willbe optimized this to mark thelast node

        } while (swaped);

    }





};



int main()
{
    LinkedList li;
    for (int i = 0; i < 10; i++)
    {
        li.insertAtEnd(i);
    }  
    li.insertAtBegin(2);
    
    li.display();
    li.insertbypos(2, 11);
    li.display();
    cout << "after deletion at end" << endl;
    li.deleteAtEnd();
    li.display();
    cout << li.listElements()<<endl;
    li.deleteAtBegin();
    cout << "after deletion at begin" << endl;
    li.display();
    cout << "after deletion at value" << endl;
    li.deletebyvalue(5);
    li.display();
    cout << "after deletion at pos" << endl;
    li.deleteByPos(5);
    li.display();
    cout << li.listElements() << endl;
    cout << "after deletion at middle" << endl;
    li.DeleteAtMiddle();
    li.display();
    cout << li.listElements() << endl;
    cout << "after insertion at middle" << endl;
    li.insertAtMiddle(20);
    li.display();
    cout << li.listElements() << endl;
    li.searching(20);
    cout << "after reverse of the list" << endl;
    li.reverseList();
    li.display();
    cout << "after reverse of the list by group" << endl;
    li.reverseListByGroup(3);
    li.display();
    cout << "after sorting" << endl;
    li.sort();
    li.display();



}