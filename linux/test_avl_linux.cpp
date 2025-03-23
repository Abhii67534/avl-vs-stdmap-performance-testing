#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include "AVLTree.h"
#include "timer.h"

using namespace std;

const int NUM = 2000000;

int main() {
    AVL tree;
    vector<int> sinList(NUM);

    for (int i = 0; i < NUM; ++i) {
        sinList[i] = 100000000 + i;
    }
    random_device rd;
    mt19937 g(rd());
    shuffle(sinList.begin(), sinList.end(), g);

    // --- Test 3: Maximum Size ---
    cout << "\n--- Test 3: Maximum Size ---\n";
    try {
        for (int i = 0; i < NUM; ++i) {
            EmployeeInfo e;
            e.age = 30;
            e.salary = 60000;
            e.emplNumber = i;
            e.sin = sinList[i];
            tree.insert(e);
        }
        cout << "Successfully inserted " << NUM << " elements.\n";
    } catch (const exception& e) {
        cout << "Exception: " << e.what() << endl;
    }

    // --- Test 5: Memory Leak (Manual Check) ---
    cout << "\n--- Test 5: Memory Leak (Manual Check) ---\n";
    cout << "Use Valgrind: valgrind ./test_avl_linux\n";

    // --- Test 6: Worst Case Search ---
    cout << "\n--- Test 6: Worst Case Search ---\n";
    Timer searchTimer;

    searchTimer.start();
    auto minNode = tree.Find(tree.GetRoot(), 100000000);
    searchTimer.stop();
    cout << "Search time for MIN SIN: " << searchTimer.currtime() << " seconds.\n";

    searchTimer.reset();
    searchTimer.start();
    auto maxNode = tree.Find(tree.GetRoot(), 100000000 + NUM - 1);
    searchTimer.stop();
    cout << "Search time for MAX SIN: " << searchTimer.currtime() << " seconds.\n";

    tree.~AVL();
    return 0;
}