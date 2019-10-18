// https://www.lintcode.com/problem/word-squares/description
// 15.20% , -
// Time for memory, that's it 

import java.util.function.*;
import java.util.stream.*;

public class Solution {

    int size; // square
    List<List<String>> answer;
    Trie trie;
    public static class TrieNode {
        Map<Character, TrieNode> children;
        boolean isLeaf;
        String word;
        int count;

        TrieNode getChild(char ch) {
            if (isLeaf) {
                return null;
            }
            return children.get(ch);
        }

        TrieNode getOrAddChild(char ch) {
            if (children == null) {
                children = new HashMap();
            }
            TrieNode node = children.get(ch);
            if (node == null) {
                node = new TrieNode();
                children.put(ch, node);
            }
            return node;
        }

        void addLeaf(String word) {
            TrieNode leafNode = getOrAddChild('0');
            // if (!leafNode.isLeaf) {
                leafNode.isLeaf = true;
                leafNode.count = 1;
                leafNode.word = word;
            // } else {
            //     leafNode.count += 1;
            // }
        }
    }


    public static class WordSquareBuilder {
        LinkedList<String> words;
        int size;
        WordSquareBuilder() {
            this.words = new LinkedList();
        }

        char[] getPrefix() {
            int row = words.size();
            char[] tmp = new char[row];
            for (int i = 0; i < row; i++) {
                tmp[i] = words.get(i).charAt(row);
            }
            return tmp;
        }

        void pushRow(String word) {
            words.add(word);
            // System.out.println(words);
        }

        void popRow() {
            words.removeLast();
        }

        int getRow() {
            return words.size();
        }

        void addToAnswer(List<List<String>> answer) {
            List<String> tmp = new ArrayList<>(size);
            tmp.addAll(words);
            answer.add(tmp);
        }
    }


    public static class Trie {
        TrieNode root;
        Trie() {
            root = new TrieNode();
            root.children = new HashMap();
        }

        void addWord(String word) {
            TrieNode node = root;
            for (int i = 0; i < word.length(); i++) {
                char ch = word.charAt(i);
                node = node.getOrAddChild(ch);
            }
            node.addLeaf(word);
        }

        TrieNode findSubtrie(WordSquareBuilder builder) {
            TrieNode node = root;
            char[] prefix = builder.getPrefix();
            for (int i = 0; i < builder.getRow(); i++) {
                node = node.getChild(prefix[i]);
                if (node == null) {
                    return null;
                }
            }
            return node;
        }

        void postOrder(TrieNode node, WordSquareBuilder builder, Consumer<WordSquareBuilder> callback) {
            if (node == null) {
                return;
            }
            if (node.isLeaf) {
                if (node.count > 0) {
                    // node.count -= 1;
                    builder.pushRow(node.word);
                    callback.accept(builder);
                    builder.popRow();
                    // node.count += 1;
                }
                return;
            }
            for (TrieNode child: node.children.values()) {
                postOrder(child, builder, callback);
            }
        }


    }

    public void buildTrie(String[] words) {
        trie = new Trie();
        for (String word: words) {
            trie.addWord(word);
        }
    }

    public void backtrace(WordSquareBuilder builder) {
        if (builder.getRow() == size) {
            builder.addToAnswer(answer);
            return;
        }
        TrieNode node = trie.findSubtrie(builder);
        trie.postOrder(node, builder, (b) -> {
            backtrace(b);
        });

    }

    /*
     * @param words: a set of words without duplicates
     * @return: all word squares
     */
    public List<List<String>> wordSquares(String[] words) {
        /*
        build trie
        backtrace on trie
        */
        answer = new ArrayList<>();
        if (words.length == 0) {
            return answer;
        }
        size = words[0].length();
        buildTrie(words);
        WordSquareBuilder builder = new WordSquareBuilder();
        builder.size = size;
        backtrace(builder);
        return answer;
    }
}
