// File: AVLTree.cpp

#include "AVLTree.h"
#include <algorithm> // for std::max

using namespace CustomDB;

// Constructor
AVLTree::AVLTree() {
    root = nullptr;
}

// Destructor
AVLTree::~AVLTree() {
    makeEmpty(root);
}

// Recursively deallocates nodes
void AVLTree::makeEmpty(Node* t) {
    if (!t) return;
    makeEmpty(t->left);
    makeEmpty(t->right);
    delete t;
}

// Height of a node
int AVLTree::height(Node* t) {
    return (t == nullptr) ? -1 : t->height;
}

// Balance factor of a node
int AVLTree::getBalance(Node* t) {
    return (t == nullptr) ? 0 : height(t->left) - height(t->right);
}

// Insert with balancing
Node* AVLTree::insert(EmployeeInfo empl, Node* t) {
    if (!t) {
        t = new Node{ empl, nullptr, nullptr, 0 };
    }
    else if (empl.sin < t->empl.sin) {
        t->left = insert(empl, t->left);
        if (height(t->left) - height(t->right) == 2) {
            if (empl.sin < t->left->empl.sin)
                t = singleRightRotate(t);
            else
                t = doubleRightRotate(t);
        }
    }
    else if (empl.sin > t->empl.sin) {
        t->right = insert(empl, t->right);
        if (height(t->right) - height(t->left) == 2) {
            if (empl.sin > t->right->empl.sin)
                t = singleLeftRotate(t);
            else
                t = doubleLeftRotate(t);
        }
    }
    t->height = std::max(height(t->left), height(t->right)) + 1;
    return t;
}

// Public insert
void AVLTree::insert(EmployeeInfo empl) {
    root = insert(empl, root);
}

// Find minimum node
Node* AVLTree::findMin(Node* t) {
    return (!t || !t->left) ? t : findMin(t->left);
}

// Find maximum node (unused, but complete)
Node* AVLTree::findMax(Node* t) {
    return (!t || !t->right) ? t : findMax(t->right);
}

// Remove with balancing
Node* AVLTree::remove(int sin, Node* t) {
    if (!t) return nullptr;

    if (sin < t->empl.sin) {
        t->left = remove(sin, t->left);
    }
    else if (sin > t->empl.sin) {
        t->right = remove(sin, t->right);
    }
    else {
        if (t->left && t->right) {
            Node* temp = findMin(t->right);
            t->empl = temp->empl;
            t->right = remove(t->empl.sin, t->right);
        }
        else {
            Node* temp = t;
            t = (t->left != nullptr) ? t->left : t->right;
            delete temp;
        }
    }

    if (!t) return t;

    t->height = std::max(height(t->left), height(t->right)) + 1;

    // Balance after deletion
    int balance = getBalance(t);
    if (balance == 2) {
        if (getBalance(t->left) >= 0)
            return singleRightRotate(t);
        else
            return doubleRightRotate(t);
    }
    else if (balance == -2) {
        if (getBalance(t->right) <= 0)
            return singleLeftRotate(t);
        else
            return doubleLeftRotate(t);
    }

    return t;
}

// Public remove
void AVLTree::remove(int sin) {
    root = remove(sin, root);
}

// Right rotation
Node* AVLTree::singleRightRotate(Node*& t) {
    Node* u = t->left;
    t->left = u->right;
    u->right = t;
    t->height = std::max(height(t->left), height(t->right)) + 1;
    u->height = std::max(height(u->left), t->height) + 1;
    return u;
}

// Left rotation
Node* AVLTree::singleLeftRotate(Node*& t) {
    Node* u = t->right;
    t->right = u->left;
    u->left = t;
    t->height = std::max(height(t->left), height(t->right)) + 1;
    u->height = std::max(height(t->right), t->height) + 1;
    return u;
}

// Right-Left rotation
Node* AVLTree::doubleLeftRotate(Node*& t) {
    t->right = singleRightRotate(t->right);
    return singleLeftRotate(t);
}

// Left-Right rotation
Node* AVLTree::doubleRightRotate(Node*& t) {
    t->left = singleLeftRotate(t->left);
    return singleRightRotate(t);
}

// Public display to ostream
void AVLTree::display(std::ostream& os) {
    inorder(root, os);
    os << std::endl;
}

// Recursive inorder print
void AVLTree::inorder(Node* t, std::ostream& os) {
    if (!t) return;
    inorder(t->left, os);
    os << " height: " << t->height
        << " sin: " << t->empl.sin
        << " employee number: " << t->empl.emplNumber
        << " salary: " << t->empl.salary
        << " age: " << t->empl.age << std::endl;
    inorder(t->right, os);
}

// Return root
Node* AVLTree::getRoot() {
    return root;
}

// Recursive search
Node* AVLTree::find(Node* t, int sin) {
    if (!t) return nullptr;
    if (sin < t->empl.sin)
        return find(t->left, sin);
    else if (sin > t->empl.sin)
        return find(t->right, sin);
    return t;
}

// Public search
Node* AVLTree::find(int sin) {
    return find(root, sin);
}
