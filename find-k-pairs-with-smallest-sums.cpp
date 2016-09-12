#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
#include <unordered_map>
#include <list>
#include <stack>

using namespace std;


class Solution {

    static int *nums2ptr;
    int nums2size;

    struct {
        bool operator() (const pair<int, int> &a, const pair<int, int> &b) const {
            return (a.first + nums2ptr[a.second] > b.first + nums2ptr[b.second]);
        }
    } comparePairs;

public:
    vector<pair<int, int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
        // k <= nums1.size() * nums2.size()
        int i;
        if (nums2.size() == 0) return vector<pair<int, int> >();
        nums2size = nums2.size();
        nums2ptr = nums2.data();

        // make max heap
        vector<pair<int, int> > heap;
        k = min(k, (int) nums1.size() * nums2size);
        int heapSize = min(k, (int) nums1.size()); // only the first k elements in nums1 will be possible answers
        for (i = 0; i < heapSize; ++i) {
            heap.push_back(make_pair(nums1[i], 0));
        }
        make_heap(heap.begin(), heap.end(), comparePairs);

        vector<pair<int, int> > ans;
        for (i = 0; i < k; ++i) {
            // cout << "heap: ";
            // for (auto &a: heap) {
            //     cout << a.first << ' ' << a.second << ", ";
            // }
            // cout << endl;

            // get/update heap top
            pair<int, int> &top = heap.front();
            ans.push_back(make_pair(top.first, nums2ptr[top.second]));
            if (top.second + 1 < nums2size) {
                // insert the new updated element to replace the old one
                heap.push_back(make_pair(top.first, top.second + 1));
                // notice that here is no push_heap
            }
            pop_heap(heap.begin(), heap.end(), comparePairs);
            heap.pop_back();
        }

        return ans;
    }
};

int *Solution::nums2ptr;


int main() {
    Solution solution;
    // vector<int> nums1 {1, 7, 11}, nums2 {2, 4, 6};
    vector<int> nums1 {}, nums2 {3};
    int k = 3;
    for (auto &a: solution.kSmallestPairs(nums1, nums2, k)) {
        cout << a.first << ' ' << a.second << ", ";
    }

    return 0;
}
