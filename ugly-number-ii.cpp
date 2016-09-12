#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
#include <queue>
#include <unordered_map>
#include <list>
#include <stack>

using namespace std;


class Solution {

    struct UglyNumber {
        long val;
        int n[3];
    };

    class CompareUglyNumber { // min-heap
    public:
        bool operator() (const struct UglyNumber &a, const struct UglyNumber &b) const {
            return a.val > b.val;
        }
    };

    priority_queue<UglyNumber, vector<UglyNumber>, CompareUglyNumber> heap;

    template<int k, int kInd>
    inline void addUglyNumberByK(const struct UglyNumber &a) {
        struct UglyNumber newNum = a;
        newNum.val *= k;
        ++newNum.n[kInd];
        heap.push(newNum);
        // cout << newNum.val << '(' << newNum.n[0] << newNum.n[1] << newNum.n[2] << "),";
    }

    void addUglyNumberToHeap(const struct UglyNumber &a) {
        // cout << a.val << '(' << a.n[0] << a.n[1] << a.n[2] << "): ";
        struct UglyNumber newNum;
        if (a.n[1] == 0 && a.n[0] == 0) {
            addUglyNumberByK<2, 2>(a);
        }
        if (a.n[0] == 0) {
            addUglyNumberByK<3, 1>(a);
        }
        addUglyNumberByK<5, 0>(a);
        // cout << endl;
    }

    /*
    By introducing n[] to avoid division acctually accelerate the algorithm.

    void addUglyNumberToHeap(const long &a) {
        if (a % 5 != 0) { // n5 == 0
            heap.push(a * 3);
            if (a % 3 != 0) { // n3 == 0
                heap.push(a * 2);
            }
        }
        heap.push(a * 5);
    }
    */

    struct UglyNumber first = {1, {0,0,0}};

public:
    int nthUglyNumber(int n) {
        heap = priority_queue<UglyNumber, vector<UglyNumber>, CompareUglyNumber> ();
        struct UglyNumber cur;

        heap.push(first);
        --n; // pop and add (n-1) times
        while (n > 0) {
            cur = heap.top(); // copy struct
            heap.pop();
            addUglyNumberToHeap(cur);
            // cout << cur.val << ' ';
            --n;
        }
        cout << endl << heap.size() << endl;
        return heap.top().val;
    }
};


int main() {
    Solution solution;
    cout << solution.nthUglyNumber(1306);

    return 0;
}
