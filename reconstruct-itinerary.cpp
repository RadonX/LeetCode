#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
#include <map>

using namespace std;

class Solution {
    map<string, vector<string> > mat;
    vector<string> itinerary;
    int sum;

    void constructGraph(vector<pair<string, string>>& tickets) {
        for (const auto& ticket: tickets) {
            mat[ticket.first].push_back(ticket.second);
        }

        // sort in lexical order
        for (auto& ticketList: mat) {
            sort(ticketList.second.begin(), ticketList.second.end());
        }

        sum = tickets.size();
    }

    bool dfs(string src, int nticket) {
        if (nticket == sum) {
            return true;
        }

        if (mat.find(src) == mat.end()) {
            return false;
        }
        // http://www.cplusplus.com/reference/stdexcept/out_of_range/

        for (auto& dest: mat[src]) {
            if (dest != "") {
                string tmp = dest; // copy
                dest = "";
                // cout << src << "->" << tmp << endl;
                if (dfs(tmp, nticket + 1)) {
                    itinerary.push_back(tmp);
                    // dest = tmp;
                    return true;
                }
                dest = tmp;
            }
        }

        return false;
    }

public:
    vector<string> findItinerary(vector<pair<string, string>> tickets) {
        // construct graph as adjacent matrix
        constructGraph(tickets);

        // DFS
        dfs("JFK", 0);
        itinerary.push_back("JFK");
        reverse(itinerary.begin(), itinerary.end());

        // // print mat
        // for (const auto& ticketList: mat) {
        //     cout << endl << ticketList.first << ':';
        //     for (const auto& dest: ticketList.second)
        //         cout << dest << ' ';
        // }
        // cout << endl;

        return itinerary;
    }
};


int main() {
    Solution solution;
    vector<pair<string, string>> tickets {{"MUC", "LHR"}, {"JFK", "MUC"}, {"SFO", "SJC"}, {"LHR", "SFO"}}; // { {"JFK", "SFO"},{"JFK","ATL"},{"SFO","ATL"},{"ATL","JFK"},{"ATL","SFO"} };
    vector<string> ans = solution.findItinerary(tickets);

    for (const auto& a: ans) {
        cout << a << ' ';
    }
    return 0;
}
