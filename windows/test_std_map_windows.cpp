#include <iostream>
#include <map>
#include <cstdlib>
#include <ctime>
#include <algorithm> // for shuffle
#include <random>    // for random engine
#include "timer.h"
#include <chrono>
#include <thread>

using namespace std;

const int NUM = 250000;

int main() {
    map<int, int> database;
    int* sins = new int[NUM];
    for (int i = 0; i < NUM; ++i) {
        sins[i] = 100000000 + i;
    }

    // Use modern shuffle with random device
    random_device rd;
    mt19937 g(rd());
    shuffle(sins, sins + NUM, g);

    // Timer setup
    Timer timer;

    cout << "\n--- Test 3: Maximum Size ---" << endl;
    try {
        for (int i = 0; i < NUM; ++i) {
            database[sins[i]] = i;
        }
        cout << "Successfully inserted " << NUM << " elements.\n";
    } catch (bad_alloc& e) {
        cout << "Memory allocation failed at i = " << database.size() << "\n";
    }

    cout << "\n--- Test 4: Load Test ---" << endl;
    database.clear();
    timer.start();
    for (int i = 0; i < NUM; ++i) {
        database[sins[i]] = i;
    }
    timer.stop();
    cout << "Inserted " << NUM << " items in " << timer.currtime() << " seconds.\n";

    cout << "\n--- Test 5: Memory Leak (manual check) ---" << endl;
    cout << "Use a memory tool like Visual Studio Diagnostic Tools or Dr. Memory.\n";

    cout << "\n--- Test 6: Worst Case Search ---" << endl;
    timer.reset();
    timer.start();
    auto low = database.find(100000000);
    timer.stop();
    cout << "Search time for MIN SIN: " << timer.currtime() << " seconds.\n";

    timer.reset();
    timer.start();
    auto high = database.find(100000000 + NUM - 1);
    timer.stop();
    cout << "Search time for MAX SIN: " << timer.currtime() << " seconds.\n";

    delete[] sins;
    std::this_thread::sleep_for(std::chrono::seconds(10));
    return 0;
}
