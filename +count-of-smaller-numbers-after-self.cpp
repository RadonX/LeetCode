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


// http://stackoverflow.com/questions/21510091/forauto-i-c-is-there-a-short-way-to-do-it-in-reverse-direction
template<typename It>
class Range
{
    It b, e;
public:
    Range(It b, It e) : b(b), e(e) {}
    It begin() const { return b; }
    It end() const { return e; }
};

template<typename ORange, typename OIt = decltype(std::begin(std::declval<ORange>())), typename It = std::reverse_iterator<OIt>>
Range<It> reverse(ORange && originalRange) {
    return Range<It>(It(std::end(originalRange)), It(std::begin(originalRange)));
}

class Solution {
public:
    vector<int> countSmaller(vector<int>& nums) {
        // case: empty

        multiset<int> Set;
        multiset<int>::iterator itBegin, itFound;
        vector<int> ans(nums.size());
        vector<int>::reverse_iterator it = ans.rbegin();
        for (auto num: reverse(nums)) { // const &
            itFound = Set.lower_bound(num); // *itFound >= num
            *(it++) =
        }
    }
};


int main() {
    Solution solution;
    return 0;
}
