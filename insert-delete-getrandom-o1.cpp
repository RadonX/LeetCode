#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class RandomizedSet {
    vector<int> eles;
    unordered_map<int, int> Map; // val, index

public:
    RandomizedSet() {
        srand (time(NULL));
    }

    /** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
    bool insert(int val) {
        if (Map.find(val) == Map.end()) {
            eles.push_back(val);
            Map[val] = eles.size() - 1; // how about reference??
            return true;
        } else return false;
    }

    /** Removes a value from the set. Returns true if the set contained the specified element. */
    bool remove(int val) {
        unordered_map<int, int>::iterator it = Map.find(val);
        if (it != Map.end()) {
            Map[eles.back()] = it->second;
            eles[it->second] = eles.back();
            eles.pop_back();
            Map.erase(it);
            return true;
        } else return false;
    }

    /** Get a random element from the set. */
    int getRandom() {
        if (eles.size() == 0) return -1;
        int randIdx = rand() % eles.size();
        return eles[randIdx];
    }
};


int main() {
    RandomizedSet randomSet;
    cout << randomSet.insert(1) << endl;
    cout << randomSet.remove(2) << endl;
    cout << randomSet.insert(2) << endl;
    cout << randomSet.getRandom() << endl;
    cout << randomSet.getRandom() << endl;
    cout << randomSet.getRandom() << endl;
    cout << randomSet.remove(1) << endl;
    cout << randomSet.insert(2) << endl;
    cout << randomSet.getRandom() << endl;
    return 0;
}
