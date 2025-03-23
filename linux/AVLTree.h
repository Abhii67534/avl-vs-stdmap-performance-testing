#ifndef AVLTREE_H
#define AVLTREE_H

struct EmployeeInfo {
    int salary;
    int age;
    int emplNumber;
    int sin; // social insurance number (used for search)
};

struct Node {
    EmployeeInfo empl;
    Node* left;
    Node* right;
    int height;
};

class AVL {
    Node* root;

    void makeEmpty(Node* t);
    int height(Node* t);
    int getBalance(Node* t);
    int max(int a, int b);

    Node* insert(EmployeeInfo empl, Node* t);
    Node* remove(int sin, Node* t);
    Node* findMin(Node* t);
    Node* singleRightRotate(Node* &t);
    Node* singleLeftRotate(Node* &t);
    Node* doubleRightRotate(Node* &t);
    Node* doubleLeftRotate(Node* &t);

    void inorder(Node* t);

public:
    AVL();
    void insert(EmployeeInfo empl);
    void remove(int sin);
    void display();
    Node* GetRoot();
    Node* Find(Node* t, int sin);
    ~AVL();
};

#endif // AVLTREE_H