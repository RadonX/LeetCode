/*
 * https://www.hackerrank.com/contests/openbracket/challenges/fraudulent-activity-notifications
 * O(nlogd)
 * #submissions: 3
 * 1. introduce deque (heap size == d)
 * 2. set -> multiset; 3. multiset erase one element
 */

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
#include <deque>
#include <set>
using namespace std;

// moving range average

// #define DEBUG

multiset<int, greater<int>> maxheap;
multiset<int> minheap;
deque<int> expds;


inline void moveMaxToMin() {
    multiset<int>::iterator it = maxheap.begin();
    minheap.insert(*it); maxheap.erase(it);
}
inline void moveMinToMax() {
    multiset<int>::iterator it = minheap.begin();
    maxheap.insert(*it); minheap.erase(it);
}

inline void pushExpd(int expd) {
    expds.push_back(expd);
    if (maxheap.size() == 0) maxheap.insert(expd);
    else {
        if (maxheap.size() > minheap.size()) {
            multiset<int>::iterator it = maxheap.begin();
            if (*it <= expd) minheap.insert(expd);
            else {
                moveMaxToMin(); maxheap.insert(expd);
            }
        } else { // ==
            multiset<int>::iterator it = minheap.begin();
            if (expd <= *it) maxheap.insert(expd);
            else {
                moveMinToMax(); minheap.insert(expd);
            }
        }
    }
}

void deleteExpd() {
    int expd = expds.front();
    expds.pop_front();
    if (*maxheap.begin() >= expd) {
        maxheap.erase(maxheap.find(expd));
        if (maxheap.size() < minheap.size())
            moveMinToMax();
    } else {
        minheap.erase(minheap.find(expd));
        if (minheap.size() + 1 < maxheap.size())
            moveMaxToMin();
    }
}

int getMedianDouble() {
    if (maxheap.size() == minheap.size())
        return *maxheap.begin() + *minheap.begin();
    else return *maxheap.begin() * 2;
}

#ifdef DEBUG
template<class T>
void outputHeap(const T &heap) {
    for (const auto & a: heap)
        cout << a << ' ';
    cout << endl;
}
#endif

int main() {
    int n, d, expd, ans = 0, i, med2;
    cin >> n >> d;
    for (i = 1; i <=d; ++i) {
        cin >> expd; pushExpd(expd);
    }
    for (i = d + 1; i <= n; ++i) {
        cin >> expd;
#ifdef DEBUG
        outputHeap(minheap); outputHeap(maxheap);
#endif
        med2 = getMedianDouble();
        if (expd >= med2) ans++;
        deleteExpd();
        pushExpd(expd);
    }
    cout << ans;
    return 0;
}
