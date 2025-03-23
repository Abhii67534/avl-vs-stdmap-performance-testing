#include <iostream>
#include <map>
#include <cstdlib>
#include <ctime>
#include <random>
#include <algorithm>
#include <vector>
#include "timer.h"

using namespace std;

const int NUM = 2000000;

int main() {
    map<int, int> database;
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
            database[sinList[i]] = i;
        }
        cout << "Successfully inserted " << NUM << " elements.\n";
    } catch (const exception& e) {
        cout << "Exception: " << e.what() << endl;
    }

    // --- Test 4: Load Test ---
    cout << "\n--- Test 4: Load Test ---\n";
    Timer t;
    t.start();
    for (int i = 0; i < NUM; ++i) {
        database[sinList[i]] = i;
    }
    t.stop();
    cout << "Inserted " << NUM << " items in " << t.currtime() << " seconds.\n";

    // --- Test 5: Memory Leak (Manual Check) ---
    cout << "\n--- Test 5: Memory Leak (Manual Check) ---\n";
    cout << "Use Valgrind: valgrind ./test_std_map_macos\n";

    // --- Test 6: Worst Case Search ---
    cout << "\n--- Test 6: Worst Case Search ---\n";
    Timer searchTimer;

    searchTimer.start();
    auto low = database.find(100000000);
    searchTimer.stop();
    cout << "Search time for MIN SIN: " << searchTimer.currtime() << " seconds.\n";

    searchTimer.reset();
    searchTimer.start();
    auto high = database.find(100000000 + NUM - 1);
    searchTimer.stop();
    cout << "Search time for MAX SIN: " << searchTimer.currtime() << " seconds.\n";

    return 0;
}