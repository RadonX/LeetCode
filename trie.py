#!/bin/python3
__author__ = 'radon'

"""
Your Trie object will be instantiated and called as such:
trie = Trie()
trie.insert("lintcode")
trie.search("lint") will return false
trie.startsWith("lint") will return true
"""
class TrieNode:
  def __init__(self):
      self.count = 0
      self.children = {}

class Trie:
  def __init__(self):
    self.root = TrieNode()

  # @param {string} word
  # @return {void}
  # Inserts a word into the trie.
  def insert(self, word):
      p = self.root
      for char in word:
          if p.children.get(char) is None:
              p.children[char] = TrieNode()
          p = p.children[char]
      p.count = p.count + 1

  # @param {string} word
  # @return {boolean}
  # Returns if the word is in the trie.
  def search(self, word):
      p = self.root
      for char in word:
          if p.children.get(char) is None:
              return False
          p = p.children[char]
      if p.count == 0:
          return False
      else: return True # < 0? no delete

  # @param {string} prefix
  # @return {boolean}
  # Returns if there is any word in the trie
  # that starts with the given prefix.
  def startsWith(self, prefix):
      p = self.root
      for char in prefix:
          if p.children.get(char) is None:
              return False
          p = p.children[char]
      return True # < 0?
