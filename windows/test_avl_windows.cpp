#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <random>
#include "AVLTree.h"
#include "timer.h"
#include <chrono>
#include <thread>



using namespace std;
using namespace CustomDB;

const int NUM = 250000;

int main() {
    AVLTree tree;
    int* sins = new int[NUM];
    for (int i = 0; i < NUM; ++i)
        sins[i] = 100000000 + i;

    // Use std::shuffle (C++11+)
    random_device rd;
    mt19937 g(rd());
    shuffle(sins, sins + NUM, g);

    Timer timer;

    // ---------------- Test 1: Correct Insertion ----------------
    cout << "\n--- Test 1: Correct Insertion ---\n";
    EmployeeInfo test1 = {60000, 30, 123, 111111111};
    tree.insert(test1);
    Node* result = tree.find(111111111);
    if (result)
        cout << "Inserted SIN: " << result->empl.sin << ", Age: " << result->empl.age << endl;
    else
        cout << "Insertion failed.\n";

    // ---------------- Test 2: Correct Deletion ----------------
    cout << "\n--- Test 2: Correct Deletion ---\n";
    tree.remove(111111111);
    result = tree.find(111111111);
    cout << (result ? "Deletion failed." : "Successfully deleted SIN 111111111.") << endl;

    // ---------------- Test 3: Maximum Size ----------------
    cout << "\n--- Test 3: Maximum Size ---\n";
    int count = 0;
    try {
        for (int i = 0; i < NUM; ++i) {
            EmployeeInfo e;
            e.age = 20 + (i % 50);
            e.salary = 40000 + (i % 100000);
            e.emplNumber = i;
            e.sin = sins[i];
            tree.insert(e);
            count++;
        }
        cout << "Successfully inserted " << count << " elements.\n";
    } catch (bad_alloc& e) {
        cout << "Memory allocation failed at element: " << count << "\n";
    }

    // ---------------- Test 4: Load Test ----------------
    cout << "\n--- Test 4: Load Test ---\n";
    AVLTree loadTree;
    timer.start();
    for (int i = 0; i < NUM; ++i) {
        EmployeeInfo e;
        e.age = 25 + (i % 30);
        e.salary = 50000 + (i % 100000);
        e.emplNumber = i;
        e.sin = sins[i];
        loadTree.insert(e);
    }
    timer.stop();
    cout << "Inserted " << NUM << " elements in " << timer.currtime() << " seconds.\n";

    // ---------------- Test 5: Memory Leak ----------------
    cout << "\n--- Test 5: Memory Leak (Manual Check) ---\n";
    cout << "Run this program with Visual Studio tools (Windows).\n";

    // ---------------- Test 6: Worst-Case Search ----------------
    cout << "\n--- Test 6: Worst-Case Search ---\n";
    timer.reset();
    timer.start();
    Node* minNode = loadTree.find(100000000);
    timer.stop();
    cout << "Search time for MIN SIN: " << timer.currtime() << " seconds.\n";

    timer.reset();
    timer.start();
    Node* maxNode = loadTree.find(100000000 + NUM - 1);
    timer.stop();
    cout << "Search time for MAX SIN: " << timer.currtime() << " seconds.\n";

    delete[] sins;
    std::this_thread::sleep_for(std::chrono::seconds(10));
    return 0;
}
