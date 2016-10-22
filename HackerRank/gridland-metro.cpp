//https://www.hackerrank.com/challenges/gridland-metro

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

long n, m, k;
struct Track {
    int r, c1, c2;
    Track(int r, int c1, int c2): r(r), c1(c1), c2(c2) {}
};
vector<Track> tracks;
struct Compare {
    bool operator() (const Track &a, const Track &b) {
        return (a.r < b.r) ||
            (a.r == b.r &&
                (a.c1 < b.c1 || (a.c1 == b.c1 && a.c2 < b.c2)));
    }
} cmp;

long countGrids() {
    if (tracks.size() == 0) return 0;
    sort(tracks.begin(), tracks.end(), cmp);
    long count = 0;
    vector<Track>::iterator it, itPrev;
    it = tracks.begin();
    count += it->c2 - it->c1 + 1;
    itPrev = it;
    for (++it; it != tracks.end(); ++it){
        if (itPrev->r == it->r) {
            if (itPrev->c2 >= it->c1) { // error-prone, use test cases 
                it->c1 = itPrev->c2 + 1;
                it->c2 = max(it->c2, itPrev->c2); // it->c1 - 1
            }
            // it->c2 is current max right side in this row
        }
        count += it->c2 - it->c1 + 1; // >= 0
        itPrev = it;
    }
    return count;
}

int main() {
    /* Read input from STDIN */
    cin >> n >> m >> k;
    tracks.reserve(k);
    int r, c1, c2;
    for (int i = 0; i < k; ++i) {
        cin >> r >> c1 >> c2;
        tracks.emplace_back(Track(r, c1, c2));
    }

    long ans = n * m - countGrids();
    cout << ans;

    return 0;
}
