//http://stackoverflow.com/questions/25142557
#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <climits>
#include <deque>
#include <queue>
#include <stack>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <typeinfo>
using namespace std;


//priority_queue<pair<int, int>, vector<pair<int, int> >, ?? > q;
//make_heap(numPrereq.begin(),numPrereq.end());


#define USE_STD_VECT_BOOL 0

#if USE_STD_VECT_BOOL
typedef vector<bool> BITS;
#else
typedef class bvect {
    unsigned data; // we could use vector<unsigned> but this is just an examle
    unsigned size;
public:
    bvect(): data(0), size(0) {}
    void push_back(bool value) {
        if(value) data |= (1u<<size);
        size++; }
    class reference {
        friend class bvect;
    protected:
        unsigned& data;
        unsigned  flag;
        reference(unsigned& data, unsigned flag)
        : data(data), flag(flag) {}
    public:
        operator bool() const {
            return data & flag; }
        reference& operator = (bool value) {
            if(value) data |= flag;
            else data &= ~flag;
            return *this; }
    };
    class iterator: protected reference  {
        friend class bvect;
        iterator(unsigned& data, unsigned flag)
        : reference(data, flag) {}
    public:
        typedef bool value_type;
        typedef bvect::reference reference;
        typedef input_iterator_tag iterator_category;
    //  HERE IS THE TRICK:
        reference& operator * () {
            return *this; }
        iterator& operator ++ () {
            flag <<= 1;
            return *this; }
        iterator operator ++ (int) {
            iterator tmp(*this);
            operator ++ ();
            return tmp; }
        bool operator == (const iterator& rhs) {
            return flag == rhs.flag; }
        bool operator != (const iterator& rhs) {
            return flag != rhs.flag; }
    };
    iterator begin() {
        return iterator(data, 1); }
    iterator end() {
        return iterator(data, 1<<size); }
} BITS;
#endif


template <typename T>
inline T const& Max (T const& a, T const& b) {
    return a < b ? b:a;
}

int main() {
    BITS bits;
    bits.push_back(0);
    bits.push_back(1);
#if !USE_STD_VECT_BOOL
//  won't compile for vector<bool>
    for(auto& a : bits)
        cout << typeid(a).name()
          << " = " << (int)(bool)a
          << endl;
#endif
//  std::_Bit_Reference
    for(BITS::reference a : bits)
        cout << typeid(a).name()
          << " = " << (int)(bool)a
          << endl;
//  few more tests
    for(auto a : bits)
        cout << typeid(a).name()
            << " = " << (int)(bool)a
            << endl;
    for(bool a : bits)
        cout << (int)(bool)a;
    cout << endl;
}
