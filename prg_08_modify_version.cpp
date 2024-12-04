
#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

// SuffixTrieNode class represents a single node in the suffix trie
class SuffixTrieNode {
public:
    map<char, SuffixTrieNode*> children;  // Children nodes
    bool isEndOfWord;  // Flag to mark the end of a word

    SuffixTrieNode() {
        isEndOfWord = false;  // Initially, it's not the end of a word
    }
};

// SuffixTrie class represents the suffix trie
class SuffixTrie {
private:
    SuffixTrieNode* root;  // Root of the suffix trie
    string text;           // The input string for the suffix trie

public:
    // Constructor to initialize the suffix trie
    SuffixTrie(string txt) {
        root = new SuffixTrieNode();
        text = txt;
    }

    // Function to insert a suffix into the trie
    void insertSuffix(string suffix) {
        SuffixTrieNode* node = root;
        for (char c : suffix) {
            if (node->children.find(c) == node->children.end()) {
                node->children[c] = new SuffixTrieNode();
            }
            node = node->children[c];
        }
        node->isEndOfWord = true;  // Mark the end of this suffix
    }

    // Function to build the suffix trie by inserting all suffixes
    void build() {
        for (int i = 0; i < text.length(); ++i) {
            insertSuffix(text.substr(i));
        }
    }

    // Utility function to print all suffixes stored in the trie
    void printSuffixes(SuffixTrieNode* node, string suffix) {
        if (node->isEndOfWord) {
            cout << suffix << endl;
        }

        // Recursively print all suffixes from the children
        for (auto& child : node->children) {
            printSuffixes(child.second, suffix + child.first);
        }
    }

    // Function to print the entire suffix trie
    void print() {
        printSuffixes(root, "");
    }
};

int main() {
    // Accept user input for the string
    string txt;
    cout << "Enter a word: ";
    cin >> txt;

    // Create the suffix trie for the input string
    SuffixTrie trie(txt);

    // Build the suffix trie
    trie.build();

    // Print the constructed suffix trie
    cout << "\nSuffix Trie for the word \"" << txt << "\":\n";
    trie.print();

    return 0;
}

