#include <iostream>
#include <stack>

class BSTnode
{
public:
    int data;
    BSTnode* left;
    BSTnode* right;

    BSTnode(int value) : data(value), left(nullptr), right(nullptr) {}
};

class InorderBST
{
public:
    BSTnode* root;


    InorderBST() : root(nullptr) {}


    void insert(int value) {
        BSTnode* newNode = new BSTnode(value);
        if (root == nullptr) {
            root = newNode;
            return;
        }

        BSTnode* current = root;
        BSTnode* parent = nullptr;

        while (current != nullptr) {
            parent = current;
            if (value < current->data) {
                current = current->left;
            }
            else if (value > current->data) {
                current = current->right;
            }
            else
            {
                return;  
            }
        }

        // Insert the new node
        if (value < parent->data) {
            parent->left = newNode;
        }
        else {
            parent->right = newNode;
        }
    }

    void inorder() {
        if (root == nullptr) return;

        std::stack<BSTnode*> s;
        BSTnode* current = root;

        while (current != nullptr || !s.empty()) {
            
            while (current != nullptr) {
                s.push(current);
                current = current->left;
            }
            current = s.top();
            s.pop();

           
            std::cout << current->data << " ";

            
            current = current->right;
        }
    }
};

int main() {
    InorderBST tree;

    tree.insert(10);
    tree.insert(5);
    tree.insert(20);
    tree.insert(2);
    tree.insert(7);
    tree.insert(15);
    tree.insert(25);

    std::cout << "Inorder Traversal: ";
    tree.inorder(); 
    std::cout << std::endl;

    return 0;
}
