#include <iostream>
#include <string>
using namespace std;

const int ALPHABET_SIZE = 26;

struct TrieNode {
    TrieNode* children[ALPHABET_SIZE];
    bool isEndOfWord;

    TrieNode() {
        isEndOfWord = false;
        for (int i = 0; i < ALPHABET_SIZE; i++)
            children[i] = nullptr;
    }
};

void insert(TrieNode* root, const string& key) {
    TrieNode* currentNode = root;
    for (char c : key) {
        int index = c - 'a';
        if (!currentNode->children[index]) {
            currentNode->children[index] = new TrieNode();
        }
        currentNode = currentNode->children[index];
    }
    currentNode->isEndOfWord = true;
}

bool hasChildren(TrieNode* node) {
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (node->children[i])
            return true;
    }
    return false;
}

bool deleteWord(TrieNode* root, const string& key, int depth = 0) {
    if (!root)
        return false;

    if (depth == key.size()) {
        if (root->isEndOfWord) {
            root->isEndOfWord = false;  // Unmark the end of word
            return !hasChildren(root);  // If no children, it can be deleted
        }
        return false; // Word does not exist
    }

    int index = key[depth] - 'a';
    if (deleteWord(root->children[index], key, depth + 1)) {
        delete root->children[index];
        root->children[index] = nullptr;

        return !root->isEndOfWord && !hasChildren(root);
    }

    return false;
}

bool search(TrieNode* root, const string& key) {
    TrieNode* currentNode = root;
    for (char c : key) {
        int index = c - 'a';
        if (!currentNode->children[index])
            return false;
        currentNode = currentNode->children[index];
    }
    return currentNode != nullptr && currentNode->isEndOfWord;
}

int main() {
    TrieNode* root = new TrieNode();
    int choice;
    string word;

    do {
        cout << "\nTrie Operations Menu:\n";
        cout << "1. Insert a word\n";
        cout << "2. Search for a word\n";
        cout << "3. Delete a word\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter word to insert: ";
                cin >> word;
                insert(root, word);
                cout << "'" << word << "' has been inserted into the Trie.\n";
                break;

            case 2:
                cout << "Enter word to search: ";
                cin >> word;
                if (search(root, word)) {
                    cout << "'" << word << "' is found in the Trie.\n";
                } else {
                    cout << "'" << word << "' is not found in the Trie.\n";
                }
                break;

            case 3:
                cout << "Enter word to delete: ";
                cin >> word;
                if (deleteWord(root, word)) {
                    cout << "'" << word << "' has been deleted from the Trie.\n";
                } else {
                    cout << "'" << word << "' was not found in the Trie or could not be deleted.\n";
                }
                break;

            case 4:
                cout << "Exiting program.\n";
                break;

            default:
                cout << "Invalid choice! Please try again.\n";
                break;
        }
    } while (choice != 4);

    return 0;
}
