#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
#include <map>
#include <unordered_map>

using namespace std;

class WordDictionary {
  class TrieNode {
    public:
    char val;
    unordered_map<char, TrieNode*> children;
    TrieNode(char val = '\0'): val(val){};
  };

  TrieNode* root;
public:
  WordDictionary() {
    root = new TrieNode();
  }
    // Adds a word into the data structure.
    void addWord(string word) {
      TrieNode* p = root;
     unordered_map<char, TrieNode*>::iterator it;

      for (auto & ch: word) {
        it = p->children.find(ch);
        if (it == p->children.end()) {
            TrieNode* tmp = new TrieNode(ch);
            p->children[ch] = tmp;
            p = tmp;
        } else {
          p = p->children[ch];
        }
      }
      p->children['\0'] = new TrieNode();
    }

    bool dfs(TrieNode *p, string& word, int ind) {
        // cout << p->val << ',' << ind << endl;
        if (ind == word.size()) {
            // parse the end ('\0'). it's different cuz it cannot match '.'
            if (p->children.find('\0') != p->children.end())
              return true;
            else return false;
        }

      char &ch = word[ind];
      if (ch != '.') {
        unordered_map<char, TrieNode*>::iterator it = p->children.find(ch);
        if (it == p->children.end()) {
          return false;
        } else {
          return dfs(it->second, word, ind+1);
        }
      } else {
        bool ans = false;
        for (auto & child: p->children) {
          ans = dfs(child.second, word, ind+1);
            if (ans) break;
        }
        return ans;
      }


    }

    // Returns if the word is in the data structure. A word could
    // contain the dot character '.' to represent any one letter.
    bool search(string word) {
        return dfs(root, word, 0);

    //   TrieNode* p = root;
    //   unordered_map<char, TrieNode*>::iterator it;
      //
    //   for (auto & ch: word) {
    //     it = p->children.find(ch);
    //     if (it == p->children.end()) {
    //       return false;
    //     } else {
    //       p = p->children[ch];
    //     }
    //   }
    //   if (p->children.find('\0') != p->children.end())
    //     return true;
    //   else return false;

      // todo: match '.'

    }
};



// To execute C++, please define "int main()"
int main() {
    WordDictionary wordDictionary;
    wordDictionary.addWord("word");
    wordDictionary.addWord("bad");
wordDictionary.addWord("dad");
wordDictionary.addWord("mad");
cout << wordDictionary.search("pad"); // false
cout << wordDictionary.search("bad"); // true
cout << wordDictionary.search(".ad"); // true
cout << wordDictionary.search("b.."); // true;
    // cout << wordDictionary.search("pattern");
    // cout << wordDictionary.search("word");
  return 0;
}
