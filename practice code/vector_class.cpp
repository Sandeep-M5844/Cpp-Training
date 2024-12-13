#include<iostream>
#include<stdexcept>

using namespace std;

template<typename T>
class vector
{
    T* data;
    size_t size;
    size_t capacity;

public:
    //Initializesvector with an initial capacity of 2
    vector()
    {
        capacity = 2;
        size = 0;
        data = new T[capacity];
    }

    
    ~vector()
    {
        delete[] data;
    }

    // Resize the vector when capacity is exceeded
    void re_size()
    {
        /* The process involves creating a new array with a larger size
        and copying the elements from the old array to the new array. Once this is done, 
        the old array is deleted to free the memory*/

        capacity *= 2; // Double the capacity
        T* new_data = new T[capacity]; // create a new array with more capacity
        for (int i = 0; i < size; i++) // copy the old data to the new array
        {
            new_data[i] = data[i];
        }
        delete[] data; // delete old data
        data = new_data; // Point to the new array
    }
    
    
    size_t get_size() const
    {
        return size;
    }

    size_t get_capacity()
    {
        return capacity;
    }

    T get_element(int index) const
    {
        if (index >= size)
        {
            throw std::out_of_range("Index out of bound"); // Throw exception if index is out of range
        }
        return data[index];
    }

    void Push_back(const T& element)
    {
        if (size >= capacity) // If there is no space left, resize the vector
        {
            re_size();
        }
        data[size++] = element; // Add the new element and increment the size
    }

    void clear()
    {
        delete[] data;
        //data = nullptr; // Prevent dangling pointer by setting to nullptr
        size = 0; // Reset size to 0
        capacity = 2; // Reset capacity to initial value
    }

    bool is_empty() const
    {
        return size == 0;
    }
    void pop_back()
    {
        if (is_empty())
        {
            throw out_of_range("vector is empty");
        }
        size--;
    }
};

int main()
{
    vector<int> v;

    v.Push_back(10);
    v.Push_back(20);
    v.Push_back(30); 

    cout << "Size of vector: " << v.get_size() << endl;
    cout << "capacity of vector: " << v.get_capacity() << endl;

  
    cout << "Is the vector empty? " << (v.is_empty() ? "Yes" : "No") << endl;

    for (int i = 0; i < v.get_size(); ++i)
    {
        try {
            cout << "Element at index " << i << ": " << v.get_element(i) << endl;
        }
        catch (const std::out_of_range& e) {
            cout << e.what() << endl;
        }
    }

    v.clear();

    // Check if the vector is empty after clearing
    cout << "Is the vector empty after clear? " << (v.is_empty() ? "Yes" : "No") << endl;

    try 
    {
        cout << v.get_element(0) << endl;
    }
    catch (const std::out_of_range& e) 
    {
        cout << "Error: " << e.what() << endl;
    }

    v.Push_back(10);
    v.Push_back(20);
    v.Push_back(30);

    try
    {
        v.pop_back();
    }
    catch (exception& e)
    {
        cout << "error: " << e.what();
    }

    cout << "After popping the element:" << endl;
    for (int i = 0; i < v.get_size(); ++i)
    {
        try
        {
            cout << "Element at index " << i << ": " << v.get_element(i) << endl;
        }
        catch (const std::out_of_range& e)
        {
            cout << e.what() << endl;
        }
    }


    return 0;
}

// o/p
/*
* Size of vector: 3
Capacity of vector: 4
Is the vector empty? No
Element at index 0: 10
Element at index 1: 20
Element at index 2: 30
Is the vector empty after clear? Yes
Error: Index out of bound
After popping the element:
Element at index 0: 10
Element at index 1: 20
*/
