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



string mergeStrings(string a, string b) {
    int lena = a.size();
    int lenb = b.size();
    string str;
    str.resize(lena + lenb);
    int i, j;
    for (i = 0, j = 0; i < min(lena, lenb); ++i) {
        str[j++] = a[i];
        str[j++] = b[i];
    }
    if (lena < lenb) {
        for (; i < lenb; ++i){ // c_str, memcpy
            str[j++] = b[i];
        }
    } else {
        for (; i < lena; ++i) {
            str[j++] = a[i];
        }
    }
    return str;
}



int main() {

	return 0;
}
