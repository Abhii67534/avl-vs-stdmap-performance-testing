// File: AVLTree.h
#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>
#include <fstream>

namespace CustomDB {

    struct EmployeeInfo {
        int salary;
        int age;
        int emplNumber;
        int sin; // Used as key
    };

    struct Node {
        EmployeeInfo empl;
        Node* left;
        Node* right;
        int height;
    };

    class AVLTree {
    private:
        Node* root;

        Node* insert(EmployeeInfo empl, Node* t);
        Node* remove(int sin, Node* t);
        Node* findMin(Node* t);
        Node* findMax(Node* t);
        Node* singleRightRotate(Node*& t);
        Node* singleLeftRotate(Node*& t);
        Node* doubleLeftRotate(Node*& t);
        Node* doubleRightRotate(Node*& t);
        int height(Node* t);
        int getBalance(Node* t);
        void inorder(Node* t, std::ostream& os);
        void makeEmpty(Node* t);
        Node* find(Node* node, int sin);

    public:
        AVLTree();
        ~AVLTree();

        void insert(EmployeeInfo empl);
        void remove(int sin);
        void display(std::ostream& os);
        Node* getRoot();
        Node* find(int sin);
    };

} // namespace CustomDB

#endif // AVLTREE_H