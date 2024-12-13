#include <iostream>
using namespace std;

class Queue {
private:
    int capacity;
    int* arr;
    int front;
    int rear;
    int count;

public:
    // Constructor to initialize the queue
    Queue(int size) {
        arr = new int[size];
        capacity = size;
        front = 0;
        rear = -1;
        count = 0;
    }

    // Destructor to free allocated memory
    ~Queue() {
        delete[] arr;
    }

    // Check if the queue is empty
    inline bool isEmpty() {
        return count == 0;
    }

    // Check if the queue is full
    inline bool isFull() {
        return count == capacity;
    }

    // Add an element to the queue
    void enqueue(int value) {
        if (isFull()) {
            cout << "Queue Overflow: Cannot insert more elements.\n";
            return;
        }
        rear = (rear + 1) % capacity; // Wrap around rear index
        arr[rear] = value;
        count++;
    }

    // Remove an element from the queue
    int dequeue() {
        if (isEmpty()) {
            cout << "Queue Underflow: No elements to dequeue.\n";
            return -1; // Indicate an error
        }
        int item_deleted = arr[front];
        front = (front + 1) % capacity; // Wrap around front index
        count--;
        return item_deleted;
    }

    // Display the elements of the queue
    void display() {
        if (isEmpty()) {
            cout << "Queue is empty.\n";
            return;
        }
        cout << "Queue elements: ";
        for (int i = 0; i < count; i++) {
            cout << arr[(front + i) % capacity] << " ";
        }
        cout << endl;
    }
};

int main() {
    Queue q(10);

    // Enqueue elements
    for (int i = 1; i <= 10; i++) {
        q.enqueue(i * 10);
        cout << "Enqueued: " << i * 10 << endl;
    }

    // Attempt to enqueue into a full queue
    q.enqueue(110);

    // Dequeue a few elements
    cout << "Dequeued element: " << q.dequeue() << endl;
    cout << "Dequeued element: " << q.dequeue() << endl;

    // Display the queue
    q.display();

    // Enqueue more elements
    q.enqueue(110);
    q.enqueue(120);

    // Display the queue again
    q.display();

    return 0;
}
