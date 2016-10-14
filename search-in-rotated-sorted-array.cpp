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


class Solution {
    inline int findInIncreasingArr(const vector<int>& nums, int start, int end, int val) {
        int mid;
        while (start <= end) {
            // cout << val << ':' << start << ',' << end << endl;
            mid = (start + end) / 2;
            if (val < nums[mid]) end = mid - 1;
            else if (val > nums[mid]) start = mid + 1;
            else return mid;
        }
        return -1;
    }

public:
    int search(const vector<int>& nums, int target) {
        int left = 0, right = (int)nums.size() - 1, mid;
        while (left < right) {
            if (nums[left] < nums[right])
                return findInIncreasingArr(nums, left, right, target);
            else {
                mid = (left + right) / 2;
                if (target == nums[mid]) return mid;
                else if (target < nums[mid]) {
                    if (nums[left] <= nums[mid]) { // == : left == mid
                        if (target >= nums[left])
                            return findInIncreasingArr(nums, left, mid - 1, target);
                        else left = mid + 1;
                    } else right = mid - 1;
                } else { // target > nums[mid]
                    if (nums[left] <= nums[mid]) left = mid + 1;
                    else {
                        if (target <= nums[right])
                            return findInIncreasingArr(nums, mid + 1, right, target);
                        else right = mid - 1;
                    }
                }
            }
        }

        if (left == right && nums[left] == target) return left;
        return -1;

    }
};

int main() {
    Solution solution;
    cout << solution.search(vector<int> {4,5,6,7,0,1,2}, 5) << endl;
    cout << solution.search(vector<int> {4,5,6,7,0,1,2}, 1) << endl;
    cout << solution.search(vector<int> {4,5,6,7,0,1,2}, 8) << endl;
    cout << solution.search(vector<int> {1,3}, 3) << endl;
    cout << solution.search(vector<int> {3,1}, 3) << endl;
    cout << solution.search(vector<int> {3,1}, 1) << endl;
    cout << solution.search(vector<int> {}, 5) << endl;
    return 0;
}
