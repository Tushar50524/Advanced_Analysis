#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Structure to represent an edge with weight
struct Edge {
    int u, v, weight;
};

// Compare edges based on their weights
bool compareEdge(Edge a, Edge b) {
    return a.weight < b.weight;
}

// Class to represent a graph
class Graph {
    int V; // Number of vertices
    vector<Edge> edges; // List of edges

public:
    Graph(int V) {
        this->V = V;
    }

    // Add an edge to the graph
    void addEdge(int u, int v, int weight) {
        edges.push_back({u, v, weight});
    }

    // Find function with path compression
    int find(vector<int>& parent, int i) {
        if (parent[i] != i) {
            parent[i] = find(parent, parent[i]);
        }
        return parent[i];
    }

    // Union function by rank
    void unionSets(vector<int>& parent, vector<int>& rank, int x, int y) {
        int rootX = find(parent, x);
        int rootY = find(parent, y);

        if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        } else if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        } else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
    }

    // Function to perform Kruskal's algorithm
    void kruskalMST() {
        // Sort all edges based on their weights
        sort(edges.begin(), edges.end(), compareEdge);

        vector<int> parent(V);
        vector<int> rank(V, 0);

        // Initialize disjoint sets
        for (int i = 0; i < V; i++) {
            parent[i] = i;
        }

        vector<Edge> mst; // Store the edges included in the MST

        for (const auto& edge : edges) {
            int u = edge.u;
            int v = edge.v;

            int setU = find(parent, u);
            int setV = find(parent, v);

            // If u and v are in different sets, include this edge in MST
            if (setU != setV) {
                mst.push_back(edge);
                unionSets(parent, rank, setU, setV);
            }
        }

        // Print the edges in the MST
        cout << "Edges in the Minimum Spanning Tree:\n";
        for (const auto& edge : mst) {
            cout << edge.u << " - " << edge.v << " : " << edge.weight << endl;
        }
    }
};

int main() {
    int V = 4; // Number of vertices
    Graph g(V);

    g.addEdge(0, 1, 10);
    g.addEdge(0, 2, 6);
    g.addEdge(0, 3, 5);
    g.addEdge(1, 3, 15);
    g.addEdge(2, 3, 4);

    g.kruskalMST();

    return 0;
}
