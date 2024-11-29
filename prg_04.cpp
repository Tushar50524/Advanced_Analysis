#include <iostream>
#include <vector>
#include <climits> // for INT_MAX

using namespace std;

// Edge structure to store information about a graph edge (u -> v with weight w)
struct Edge {
    int u, v, weight;
};

// Function to implement Bellman-Ford algorithm
bool bellmanFord(int vertices, int edges, int source, const vector<Edge>& graph, vector<int>& distances) {
    // Initialize distances from source to all vertices as infinite (INT_MAX)
    distances.assign(vertices, INT_MAX);
    distances[source] = 0;  // Distance from source to itself is always 0

    // Relax all edges (vertices-1) times
    for (int i = 0; i < vertices - 1; i++) {
        for (int j = 0; j < edges; j++) {
            int u = graph[j].u;
            int v = graph[j].v;
            int weight = graph[j].weight;
            
            if (distances[u] != INT_MAX && distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight;
            }
        }
    }

    // Check for negative weight cycles by relaxing edges one more time
    for (int j = 0; j < edges; j++) {
        int u = graph[j].u;
        int v = graph[j].v;
        int weight = graph[j].weight;

        if (distances[u] != INT_MAX && distances[u] + weight < distances[v]) {
            // Negative weight cycle detected
            return false;
        }
    }

    return true;
}

int main() {
    int vertices, edges;
    cout << "Enter number of vertices and edges: ";
    cin >> vertices >> edges;

    vector<Edge> graph(edges);
    
    cout << "Enter edges (u v weight):" << endl;
    for (int i = 0; i < edges; i++) {
        cin >> graph[i].u >> graph[i].v >> graph[i].weight;
    }

    int source;
    cout << "Enter source vertex: ";
    cin >> source;

    vector<int> distances(vertices);

    // Run Bellman-Ford algorithm
    if (bellmanFord(vertices, edges, source, graph, distances)) {
        cout << "Shortest distances from source " << source << " are:" << endl;
        for (int i = 0; i < vertices; i++) {
            if (distances[i] == INT_MAX) {
                cout << "Vertex " << i << ": No path" << endl;
            } else {
                cout << "Vertex " << i << ": " << distances[i] << endl;
            }
        }
    } else {
        cout << "Graph contains a negative weight cycle!" << endl;
    }

    return 0;
}

