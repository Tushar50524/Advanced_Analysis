#include <iostream>
using namespace std;

class Node {
    int *keys; // Array of keys
    int t; // Minimum degree
    Node **C; // Array of child pointers
    int n; // Current number of keys
    bool leaf; // Is true when the node is a leaf

public:
    Node(int _t, bool _leaf); // Constructor

    void insertNonFull(int k);
    void splitChild(int i, Node *y);
    void traverse(); // Function to traverse the nodes

    friend class BTree;
};

class BTree {
    Node *root; // Pointer to root node
    int t; // Minimum degree

public:
    BTree(int _t) {
        root = NULL;
        t = _t;
    }

    void traverse() {
        if (root != NULL)
            root->traverse();
    }

    void insert(int k);
};

Node::Node(int t1, bool leaf1) {
    t = t1;
    leaf = leaf1;
    keys = new int[2 * t - 1];
    C = new Node *[2 * t];
    n = 0;
}

// Traverse the nodes in the B-Tree
void Node::traverse() {
    int i;
    for (i = 0; i < n; i++) {
        if (!leaf)
            C[i]->traverse();
        cout << " " << keys[i];
    }
    if (!leaf)
        C[i]->traverse();
}

// Insert a key into the B-Tree
void BTree::insert(int k) {
    if (root == NULL) {
        root = new Node(t, true);
        root->keys[0] = k;
        root->n = 1;
    } else {
        if (root->n == 2 * t - 1) {
            Node *s = new Node(t, false);
            s->C[0] = root;
            s->splitChild(0, root);
            int i = 0;
            if (s->keys[0] < k)
                i++;
            s->C[i]->insertNonFull(k);
            root = s;
        } else
            root->insertNonFull(k);
    }
}

// Insert key in a non-full node
void Node::insertNonFull(int k) {
    int i = n - 1;

    if (leaf) {
        while (i >= 0 && keys[i] > k) {
            keys[i + 1] = keys[i];
            i--;
        }
        keys[i + 1] = k;
        n = n + 1;
    } else {
        while (i >= 0 && keys[i] > k)
            i--;

        if (C[i + 1]->n == 2 * t - 1) {
            splitChild(i + 1, C[i + 1]);
            if (keys[i + 1] < k)
                i++;
        }
        C[i + 1]->insertNonFull(k);
    }
}

// Split a full child
void Node::splitChild(int i, Node *y) {
    Node *z = new Node(y->t, y->leaf);
    z->n = t - 1;

    for (int j = 0; j < t - 1; j++)
        z->keys[j] = y->keys[j + t];

    if (!y->leaf) {
        for (int j = 0; j < t; j++)
            z->C[j] = y->C[j + t];
    }

    y->n = t - 1;
    for (int j = n; j >= i + 1; j--)
        C[j + 1] = C[j];

    C[i + 1] = z;

    for (int j = n - 1; j >= i; j--)
        keys[j + 1] = keys[j];

    keys[i] = y->keys[t - 1];
    n = n + 1;
}
int main() {
    int t;
    cout << "Enter the minimum degree of the B-Tree: ";
    cin >> t;
    BTree btree(t);

    int choice, key;
    do {
        cout << "\n1. Insert key\n2. Traverse B-Tree\n3. Exit\nEnter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "Enter the key to insert: ";
                cin >> key;
                btree.insert(key);
                break;
            case 2:
                cout << "B-Tree traversal: ";
                btree.traverse();
                cout << endl;
                break;
            case 3:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice, please try again." << endl;
        }
    } while (choice != 3);
    return 0;
}
