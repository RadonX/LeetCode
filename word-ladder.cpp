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

// (V+V*wordlen)logV
// https://www.quora.com/What-is-the-most-simple-efficient-C++-code-for-Dijkstras-shortest-path-algorithm
class Solution {
    int maxdist;
    map<string, int> dist; // a must, b/c Set cannot be used to get dist by word
    unordered_set<string> words; // words set whose min dist not found yet.

    struct Node {
        int dist; // to src
        string word;
        Node(int dist, string word): dist(dist), word(word) {}
    };
    struct Compare {
        bool operator() (const struct Node &a , const struct Node &b) const {
            return (a.dist < b.dist) || (a.dist == b.dist && a.word < b.word);
        }
    };
    // http://www.cplusplus.com/reference/set/set/set/
    set<Node, Compare> Set; // Comment: better than priority_queue in that it's easier to delete eles.

    // All words have the same length.
    // All words contain only lowercase alphabetic characters.
    vector<string> getNeighbors(string w) { // O(V) -> O(wordlen)
        vector<string> neighbors;
        for (int i = 0; i < w.size(); ++i) {
            char oldch = w[i];
            for (char ch = 'a'; ch <= 'z'; ++ch) {
                w[i] = ch;
                if (words.find(w) != words.end())
                    neighbors.push_back(w);
            }
            w[i] = oldch;
        }
        return neighbors;
    }

    void init(const string &src) {
        for (auto & word: words) {
            dist[word] = maxdist;
        }
        dist[src] = 0;
        Set = set<Node, Compare> {Node(0, src)};
    }

    int findMinDist(string dst) {
        while (!Set.empty()) {
            struct Node node = *(Set.begin());
            Set.erase(Set.begin());

            // no node in Set has maxdist
            // cout << node.word << ':' << node.dist << endl;
            if (node.word == dst) { return node.dist; }

            words.erase(node.word); // node.word's min dist found
            // update neighbor words with node.word
            for (const auto & word: getNeighbors(node.word)) {
                int tmpdist = node.dist + 1;
                if (tmpdist < dist[word]) { // < maxdist
                    // cout << ' ' << word << ':' << tmpdist;
                    Set.erase(Node(dist[word], word)); // so that there's no duplicate word
                    dist[word] = tmpdist;
                    Set.insert(Node(tmpdist, word));
                    // cout << '(' << Set.size() << ')' << endl;
                }
            }

        }

        return -1;
    }


public:

    Solution() { maxdist = INT_MAX >> 1; };

    int ladderLength(const string & beginWord, const string & endWord, unordered_set<string>& wordList) {
        words = wordList;
        words.insert(beginWord);
        words.insert(endWord);

        init(beginWord);
        return findMinDist(endWord) + 1;
    }
};


// very slow,
// 1669ms -> 1515ms (Node*) -> 1322ms (getNeighbors when needed) -> 1223ms (neighbors Node*)
// -> 1125ms (remove wordId nearest) -> 1082ms (give up vector<Node>)
// -> 1149ms
class Solution2 {
    int maxdist;

    class Node {
    public:
        int dist; // to src
        string word;
        Node(int dist, string word): dist(dist), word(word) {}
    };

    struct SetNode {
        int dist; // to src
        Node *p;
        SetNode(int dist, Node *p): dist(dist), p(p) {}
    };

    struct Compare {
        bool operator() (const struct SetNode &a , const struct SetNode &b) const {
            return (a.dist < b.dist) || (a.dist == b.dist && a.p < b.p);
        } // Comment: page miss
    };
    set<SetNode, Compare> Set;


    map<string, Node*> wordId; // Comment: set<string> ??

    // get it when need it
    vector<Node*> getNeighbors(Node *p) { // O(V) -> O(wordlen)
        vector<Node*> neighbors;
        string &w = p->word;
        map<string, Node*>::iterator it;

        for (int i = 0; i < w.size(); ++i) {
            char oldch = w[i];
            for (char ch = 'a'; ch <= 'z'; ++ch) {
                w[i] = ch;
                it = wordId.find(w);
                if (it != wordId.end())
                    neighbors.push_back(it->second);
            }
            w[i] = oldch;
        }
        return neighbors;
    }

    int findMinDist(Node *dst) {
        int dist;
        Node *p;
        while (!Set.empty()) {
            p = Set.begin()->p;
            dist = Set.begin()->dist;
            Set.erase(Set.begin());
            wordId.erase(p->word); // garbage

            if (p == dst) { return dist; }
            for (const auto & neighbor: getNeighbors(p)) {
                int tmpdist = dist + 1;
                if (tmpdist < neighbor->dist) { // < maxdist
                    Set.erase(SetNode(neighbor->dist, neighbor)); // so that there's no duplicate word
                    neighbor->dist = tmpdist;
                    Set.insert(SetNode(neighbor->dist, neighbor));
                }
            }
        }

        return -1;
    }

    // wordList -> word nodes
    void parseWords(const string & beginWord, const string & endWord, unordered_set<string>& wordList) {
        wordList.erase(beginWord);
        wordList.erase(endWord);

        wordId[beginWord] = new Node(0, beginWord);
        for (auto &word: wordList) {
            wordId[word] = new Node(maxdist, word); //Comment: new Node
        }
        wordId[endWord] = new Node(maxdist, endWord);
    }

public:

    Solution2 () { maxdist = INT_MAX >> 1; };

    int ladderLength(const string & beginWord, const string & endWord, unordered_set<string>& wordList) {
        parseWords(beginWord, endWord, wordList);
        Set.insert(SetNode(0, wordId[beginWord]));
        return findMinDist(wordId[endWord]) + 1;
    }
};


int main() {
    Solution2 solution;
    unordered_set<string> wordList {"hot","dot","dog","lot","log"};
    // unordered_set<string> wordList {"hot","cog","dot","dog","hit","lot","log"};
    cout << solution.ladderLength("hit", "cog", wordList) << endl;

    return 0;
}
