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

class Point2D{
public:
    int x, y;
    Point2D(int x, int y): x(x), y(y) {}
    double dist2D(Point2D p) {
        return sqrt( (x-p.x)*(x-p.x) + (y-p.y)*(y-p.y));
    }
    void printDistance(double d) {
        cout << "2D distance = " << ceil(d) << endl;
    }
};

class Point3D: public Point2D{
public:
    int z;
    Point3D(int x, int y, int z): Point2D(x,y), z(z){}
    double dist3D(Point3D p) {
        return sqrt( (x-p.x)*(x-p.x) + (y-p.y)*(y-p.y) + (z-p.z)*(z-p.z));
    }
    void printDistance(double d) {
        cout << "3D distance = " << ceil(d) << endl;
    }
};

int main() {

	return 0;
}
