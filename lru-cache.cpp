#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
#include <unordered_map>
#include <list>

using namespace std;


struct Ele{
    int key;
    int value;
};

class LRUCache{

    list<Ele> cache; // first one is LRU
    int size, capacity;
    unordered_map<int, list<Ele>::iterator> cacheInd; // first -> key

    void deletelru() {
        // only called when there is element
        int key = cache.begin()->key; // (*cache.begin()).key
        cache.pop_front();
        cacheInd.erase(key);
        size--;
    }

public:
    LRUCache(int capacity): capacity(capacity) {
        size = 0;
    }

    int get(int key) {
        if (capacity == 0) return -1;

        if (cacheInd.find(key) == cacheInd.end()) {
            return -1;
        } else {
            list<Ele>::iterator it = cacheInd[key];
            // move it to the end
            cache.splice(cache.end(), cache, it);
            // `it` still valid. no need to change cacheInd
            return (*it).value;
        }
    }

    void set(int key, int value) {
        if (capacity == 0) return;

        if (cacheInd.find(key) == cacheInd.end()) {
            if (size == capacity) {
                deletelru();
            }
            size++;
            struct Ele tmpEle = {key, value};
            cache.push_back(tmpEle);
            cacheInd[key] = prev(cache.end());
        } else {
            list<Ele>::iterator it = cacheInd[key];
            (*it).value = value;
            cache.splice(cache.end(), cache, it); // move it to the end
        }
    }
};


int main() {
    {
    LRUCache lrucache(3);
    lrucache.set(2,-2);
    cout << lrucache.get(2) << ',';
    lrucache.set(3,-3);
    lrucache.set(2,2);
    lrucache.set(4,-4);
    cout << lrucache.get(2) << ',';
    cout << lrucache.get(4) << ',';
    lrucache.set(5,-5);
    cout << lrucache.get(3) << ',';
    cout << endl;
    }

    LRUCache lrucache(2);
    lrucache.set(2,1);
    lrucache.set(1,1);
    cout << lrucache.get(2) << ',';
    lrucache.set(4,1);
    cout << lrucache.get(1) << ',';
    cout << lrucache.get(2) << ',';

    return 0;
}
