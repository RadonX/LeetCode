#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
#include <queue>
#include <unordered_map>
#include <list>
#include <map>

using namespace std;

#include <iostream>
#include <map>

void changeInt(vector<int> &b) {
    a = 5;
}

int main ()
{
  std::map<char,int> mymap;
  std::map<char,int>::iterator itlow,itup;
  vector<vector<int> > a(10, vector<int>(10,1));
  vector<int> b {1,2,3,4};
  vector<int>::iterator it = b.end();
  cout << *prev(b.end()) << endl;

  mymap['a']=20;
  // mymap['b']=40;
  mymap['c']=60;
  mymap['d']=80;
  mymap['e']=100;

  itlow=mymap.lower_bound ('b');  // itlow points to b
  itup=mymap.upper_bound ('d');   // itup points to e (not d!)

  mymap.erase(itlow,itup);        // erases [itlow,itup)

  // print content:
  for (std::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';

  return 0;
}
