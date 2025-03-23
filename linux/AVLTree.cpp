#include <iostream>
#include "AVLTree.h"

using namespace std;

AVL::AVL() {
    root = nullptr;
}

AVL::~AVL() {
    makeEmpty(root);
}

int AVL::height(Node* t) {
    return (t == nullptr ? -1 : t->height);
}

int AVL::getBalance(Node* t) {
    return (t == nullptr) ? 0 : height(t->left) - height(t->right);
}

int AVL::max(int a, int b) {
    return (a > b) ? a : b;
}

void AVL::makeEmpty(Node* t) {
    if (t == nullptr)
        return;

    makeEmpty(t->left);   // Recursively delete left subtree
    makeEmpty(t->right);  // Recursively delete right subtree

    // After deletion, make sure no other part of the tree is pointing to the node
    t->left = t->right = nullptr;
    delete t;  // Free the node memory
    t = nullptr;  // Avoid any accidental access to the deleted node
}

Node* AVL::singleRightRotate(Node*& t) {
    Node* u = t->left;
    t->left = u->right;
    u->right = t;

    // Recalculate heights
    t->height = max(height(t->left), height(t->right)) + 1;
    u->height = max(height(u->left), t->height) + 1;

    return u;
}

Node* AVL::singleLeftRotate(Node*& t) {
    Node* u = t->right;
    t->right = u->left;
    u->left = t;

    // Recalculate heights
    t->height = max(height(t->left), height(t->right)) + 1;
    u->height = max(height(t->right), t->height) + 1;

    return u;
}

Node* AVL::doubleRightRotate(Node*& t) {
    t->left = singleLeftRotate(t->left);
    return singleRightRotate(t);
}

Node* AVL::doubleLeftRotate(Node*& t) {
    t->right = singleRightRotate(t->right);
    return singleLeftRotate(t);
}


Node* AVL::insert(EmployeeInfo empl, Node* t) {
    // Base case: empty tree or leaf node
    if (t == nullptr) {
        t = new Node{empl, nullptr, nullptr, 0};  // Allocate a new node
    } 
    // Insert into the left subtree
    else if (empl.sin < t->empl.sin) {
        t->left = insert(empl, t->left);
        // Check balance factor and apply rotations if necessary
        if (height(t->left) - height(t->right) == 2) {
            if (empl.sin < t->left->empl.sin)
                t = singleRightRotate(t);  // Single right rotation
            else
                t = doubleRightRotate(t);  // Double right rotation
        }
    } 
    // Insert into the right subtree
    else if (empl.sin > t->empl.sin) {
        t->right = insert(empl, t->right);
        // Check balance factor and apply rotations if necessary
        if (height(t->right) - height(t->left) == 2) {
            if (empl.sin > t->right->empl.sin)
                t = singleLeftRotate(t);  // Single left rotation
            else
                t = doubleLeftRotate(t);  // Double left rotation
        }
    }

    // Update the height of the current node
    t->height = max(height(t->left), height(t->right)) + 1;
    return t;
}

Node* AVL::findMin(Node* t) {
    return (t == nullptr || t->left == nullptr) ? t : findMin(t->left);
}

Node* AVL::remove(int sin, Node* t) {
    Node* temp;

    if (t == nullptr) return nullptr;

    // Find the node to delete
    if (sin < t->empl.sin) {
        t->left = remove(sin, t->left);  // Go left if the sin is smaller
    } else if (sin > t->empl.sin) {
        t->right = remove(sin, t->right);  // Go right if the sin is larger
    } else {
        // Node to delete found
        if (t->left && t->right) {  // Two children
            temp = findMin(t->right);  // Find the smallest value in the right subtree
            t->empl = temp->empl;  // Replace with the smallest value
            t->right = remove(t->empl.sin, t->right);  // Remove the node containing the smallest value
        } else {  // One or no children
            temp = t;
            t = (t->left != nullptr) ? t->left : t->right;  // Promote the non-null child
            delete temp;  // Delete the current node
        }
    }

    if (t == nullptr) return t;

    // Update the height of the node after removal
    t->height = max(height(t->left), height(t->right)) + 1;

    // Balance the tree if needed
    int balance = getBalance(t);

    // Left heavy tree, need to rotate
    if (balance > 1) {
        if (getBalance(t->left) >= 0)
            return singleRightRotate(t);
        else
            return doubleRightRotate(t);
    }
    // Right heavy tree, need to rotate
    else if (balance < -1) {
        if (getBalance(t->right) <= 0)
            return singleLeftRotate(t);
        else
            return doubleLeftRotate(t);
    }

    return t;
}

Node* AVL::GetRoot() {
    return root;
}

Node* AVL::Find(Node* node, int sin) {
    if (node == nullptr) return nullptr;
    if (sin < node->empl.sin)
        return Find(node->left, sin);
    else if (sin > node->empl.sin)
        return Find(node->right, sin);
    else
        return node;  // Found the node
}

void AVL::inorder(Node* t) {
    if (t == nullptr) return;
    inorder(t->left);
    cout << "SIN: " << t->empl.sin << ", Age: " << t->empl.age << ", Salary: " << t->empl.salary << endl;
    inorder(t->right);
}

void AVL::insert(EmployeeInfo empl) {
    root = insert(empl, root);  // Insert into the tree
}

void AVL::remove(int sin) {
    root = remove(sin, root);  // Remove from the tree
}

void AVL::display() {
    inorder(root);  // Display in-order traversal
    cout << endl;
}