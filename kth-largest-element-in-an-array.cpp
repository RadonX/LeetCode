#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>

using namespace std;

/*
PARTITION (A,p,r) // p is start, r is end
    x = A[r]
    i = p-1
    for j=p to r-1
        if A[j]≤x then
            i=i+1, swap(A[i],A[j])
    swap(A[i+1],A[r])
    return i+1
*/

class Solution {
    inline bool lessequal(int a, int b) {
        return a >= b;
    }

    int partition(vector<int>& nums, int start, int end) {
        // select pivot
        int pivot = nums[end];
        int i = start - 1; // <= i: <= pivot
        int j;
        for (j = start; j <= end; j++) {
            // if (lessequal(nums[j], pivot)) {
            if (nums[j] >= pivot) {
                i++;
                swap(nums[j], nums[i]);
            }
            // (i, j]: > pivot
        }
        // nums[i] ends up being nums_old[end] (pivot)
        return i;
    }

    void findKth(vector<int>& nums, int start, int end, int k) {
        // k \in [start, end]
        // here k is absolute pos instead of relative pos to start.
        int p;
        while (true) {
            p = partition(nums, start, end);
            if (p == k) break;
            if (p > k) {
                end = p - 1;
            } else {
                start = p + 1;
            }
        }
    }

public:

    int findKthLargest(vector<int>& nums, int k) {
        random_shuffle(nums.begin(), nums.end()); // http://www.cplusplus.com/reference/algorithm/random_shuffle/
        findKth(nums, 0, nums.size() - 1, k - 1);
        // nums is modified
        return nums[k - 1];
    }
};

int main() {
    Solution solution;
    vector<int> nums {3,2,1,5,6,4};// {1,3,-1,-3,5,3,6,7};
    int ans = solution.findKthLargest(nums, 2);
    cout << ans << endl;
    for (const auto& a: nums) {
        cout << a << ' ';
    }
    return 0;
}
