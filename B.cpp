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

using namespace std;

/*
 * Complete the function below.
 */
int isArray_Balanced(vector < int > arr) {
    vector<int> sum(arr.size() + 1);
    int i = 1;
    sum[0] = 0;
    for (auto &a: arr) {
        sum[i] = sum[i-1] + a;
        ++i;
    }
    int all = sum[arr.size()];
    for (i = 0; i < arr.size(); ++i) {
        if (sum[i] == all - arr[i] - sum[i]) return i;
    }
    return -1;
}




int main() {

	return 0;
}
