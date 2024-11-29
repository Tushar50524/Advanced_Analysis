#include <iostream>
#include <map>
#include <string>
using namespace std;

// Suffix Tree Node
struct SuffixTreeNode {
    map<char, SuffixTreeNode*> children;  // Map for storing children nodes
    int start;  // Starting index of the substring represented by the node
    int* end;   // Pointer to the end index of the substring
    SuffixTreeNode* suffixLink;  // Link to the node representing the largest suffix

    SuffixTreeNode(int start, int* end) {
        this->start = start;
        this->end = end;
        suffixLink = nullptr;
    }

    int edgeLength() {
        return *end - start + 1;
    }
};

// Global variables for the tree construction
const int MAX_CHAR = 256;
string text;  // The input text for the suffix tree
SuffixTreeNode* root = nullptr;
SuffixTreeNode* lastNewNode = nullptr;
SuffixTreeNode* activeNode = nullptr;

int activeEdge = -1;
int activeLength = 0;
int remainingSuffixCount = 0;
int leafEnd = -1;
int* rootEnd = nullptr;
int* splitEnd = nullptr;
int size = -1; // Length of the input text

// Function to create a new node in the suffix tree
SuffixTreeNode* newNode(int start, int* end) {
    SuffixTreeNode* node = new SuffixTreeNode(start, end);
    return node;
}

// Function to extend the suffix tree by adding new characters
void extendSuffixTree(int pos) {
    leafEnd = pos;
    remainingSuffixCount++;
    lastNewNode = nullptr;

    while (remainingSuffixCount > 0) {
        if (activeLength == 0) {
            activeEdge = pos;
        }

        if (activeNode->children.find(text[activeEdge]) == activeNode->children.end()) {
            activeNode->children[text[activeEdge]] = newNode(pos, &leafEnd);

            if (lastNewNode != nullptr) {
                lastNewNode->suffixLink = activeNode;
                lastNewNode = nullptr;
            }
        } else {
            SuffixTreeNode* next = activeNode->children[text[activeEdge]];

            if (activeLength >= next->edgeLength()) {
                activeEdge += next->edgeLength();
                activeLength -= next->edgeLength();
                activeNode = next;
                continue;
            }

            if (text[next->start + activeLength] == text[pos]) {
                if (lastNewNode != nullptr && activeNode != root) {
                    lastNewNode->suffixLink = activeNode;
                    lastNewNode = nullptr;
                }

                activeLength++;
                break;
            }

            splitEnd = new int;
            *splitEnd = next->start + activeLength - 1;

            SuffixTreeNode* split = newNode(next->start, splitEnd);
            activeNode->children[text[activeEdge]] = split;

            split->children[text[pos]] = newNode(pos, &leafEnd);
            next->start += activeLength;
            split->children[text[next->start]] = next;

            if (lastNewNode != nullptr) {
                lastNewNode->suffixLink = split;
            }

            lastNewNode = split;
        }

        remainingSuffixCount--;

        if (activeNode == root && activeLength > 0) {
            activeLength--;
            activeEdge = pos - remainingSuffixCount + 1;
        } else if (activeNode != root) {
            activeNode = activeNode->suffixLink;
        }
    }
}
// Function to print the suffix tree
void print(int i, int j) {
    for (int k = i; k <= j; k++) {
        cout << text[k];
    }
}
void setSuffixIndexByDFS(SuffixTreeNode* node, int labelHeight) {
    if (node == nullptr) return;

    if (node->children.empty()) {
        cout << "Suffix : ";
        print(node->start, *(node->end));
        cout << " [Index = " << size - labelHeight << "]" << endl;
    } else {
        for (auto it : node->children) {
            setSuffixIndexByDFS(it.second, labelHeight + it.second->edgeLength());
        }
    }
}
// Function to build the suffix tree
void buildSuffixTree() {
    size = text.length();
    rootEnd = new int(-1);
    root = newNode(-1, rootEnd);
    activeNode = root;

    for (int i = 0; i < size; i++) {
        extendSuffixTree(i);
    }
    int labelHeight = 0;
    setSuffixIndexByDFS(root, labelHeight);
}
// Main function
int main() {
    cout << "Enter the text: ";
    cin >> text;
    buildSuffixTree();
    return 0;
}
