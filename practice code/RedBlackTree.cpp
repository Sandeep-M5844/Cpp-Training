#include<iostream>
using namespace std;

enum colour { red, black };

class node {
public:
    node* nparent;
    node* left;
    node* right;
    int data;
    colour color;

    node(int value)
    {
        nparent = nullptr;
        left = nullptr;
        right = nullptr;
        color = red;
        data = value;
    }
};

class RBnode
{
    node* root = nullptr;
    node* tnull = nullptr;  // sentinel node for leaf nodes

public:
    RBnode() {
        tnull = new node(0);  // Initialize sentinel node
        tnull->color = black;  // Sentinel is always black
        root = tnull;  // Start with an empty tree
    }

    void insert(int value)
    {
        node* newnode = new node(value);
        node* current = root;
        node* parent = nullptr;

        // If the tree is empty, insert the new node as root
        if (root == tnull)
        {
            root = newnode;
            root->color = black;  // Root is always black
            root->left = tnull;
            root->right = tnull;
            return;
        }

        // Find the correct place to insert the new node
        while (current != tnull)
        {
            parent = current;
            if (value < current->data)
                current = current->left;
            else
                current = current->right;
        }

        newnode->nparent = parent;

        if (value < parent->data)
            parent->left = newnode;
        else
            parent->right = newnode;

        newnode->left = tnull;
        newnode->right = tnull;
        newnode->color = red;  // New nodes are always red

        // Fix any violations caused by the insertion
        insertviolationfix(newnode);
    }

    // Function to fix violations of the Red-Black Tree properties
    void insertviolationfix(node* newnode)
    {
        node* uncle;

        while (newnode->nparent->color == red)
        {
            if (newnode->nparent == newnode->nparent->nparent->left)
            {  // Parent is left child
                uncle = newnode->nparent->nparent->right;


                if (uncle->color == red) 
                {
                    newnode->nparent->color = black;
                    uncle->color = black;
                    newnode->nparent->nparent->color = red;
                    newnode = newnode->nparent->nparent;  // Move up to grandparent
                }
                else
                {
                    if (newnode == newnode->nparent->right) {
                        newnode = newnode->nparent;
                        rotateleft(newnode);  // Left rotation
                    }

                    newnode->nparent->color = black;
                    newnode->nparent->nparent->color = red;
                    rotateright(newnode->nparent->nparent);  // Right rotation
                }
            }
            else
            {  // Parent is right child
                uncle = newnode->nparent->nparent->left;

                if (uncle->color == red) {
                    uncle->color = black;
                    newnode->nparent->color = black;
                    newnode->nparent->nparent->color = red;
                    newnode = newnode->nparent->nparent;  // Move up to grandparent
                }
                else
                {
                    if (newnode == newnode->nparent->left)
                    {
                        newnode = newnode->nparent;
                        rotateright(newnode);  // Right rotation
                    }

                    newnode->nparent->color = black;
                    newnode->nparent->nparent->color = red;
                    rotateleft(newnode->nparent->nparent);  // Left rotation
                }
            }
        }
        root->color = black;  // Ensure root is black
    }

    // Left rotation function
    void rotateleft(node* n) {
        node* rightChild = n->right;
        n->right = rightChild->left;

        if (rightChild->left != tnull)
            rightChild->left->nparent = n;

        rightChild->nparent = n->nparent;

        if (n->nparent == tnull)
            root = rightChild;
        else if (n == n->nparent->left)
            n->nparent->left = rightChild;
        else
            n->nparent->right = rightChild;

        rightChild->left = n;
        n->nparent = rightChild;
    }

    // Right rotation function
    void rotateright(node* n) {
        node* leftChild = n->left;
        n->left = leftChild->right;

        if (leftChild->right != tnull)
            leftChild->right->nparent = n;

        leftChild->nparent = n->nparent;

        if (n->nparent == tnull)
            root = leftChild;
        else if (n == n->nparent->right)
            n->nparent->right = leftChild;
        else
            n->nparent->left = leftChild;

        leftChild->right = n;
        n->nparent = leftChild;
    }

    void inorder(node* n) {
        if (n != tnull) {
            inorder(n->left);
            cout << n->data << "(" << (n->color == red ? "R" : "B") << ") ";
            inorder(n->right);
        }
    }

    void inorder() {
        inorder(root);
        cout << endl;
    }
};

int main() {
    RBnode tree;

    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(15);
    tree.insert(5);
    tree.insert(25);
    tree.insert(12);
    cout << "Inorder traversal: ";
    tree.inorder();  

    return 0;
}
