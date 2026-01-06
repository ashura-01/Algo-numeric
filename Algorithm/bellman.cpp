#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int from;
    int to;
    int weight;
};

const int INF = 1e9;

vector<Edge> edgeList;
vector<int> distanceFromSource;
vector<int> parentNode;

// INITIALIZE_SINGLE_SOURCE
void initializeSingleSource(int numberOfNodes, int source) {
    distanceFromSource.assign(numberOfNodes, INF);
    parentNode.assign(numberOfNodes, -1);
    distanceFromSource[source] = 0;
}

// RELAX
void relax(int from, int to, int weight) {
    if (distanceFromSource[from] != INF &&
        distanceFromSource[to] > distanceFromSource[from] + weight) {

        distanceFromSource[to] = distanceFromSource[from] + weight;
        parentNode[to] = from;
    }
}

// PRINT PATH
void printPath(int node) {
    if (node == -1) return;
    printPath(parentNode[node]);
    cout << node << " ";
}

// BELLMAN-FORD
bool bellmanFord(int numberOfNodes, int source) {
    initializeSingleSource(numberOfNodes, source);

    // Relax all edges (V - 1) times
    for (int i = 1; i <= numberOfNodes - 1; i++) {
        for (auto &edge : edgeList) {
            relax(edge.from, edge.to, edge.weight);
        }
    }

    // Check for negative weight cycle
    for (auto &edge : edgeList) {
        if (distanceFromSource[edge.from] != INF &&
            distanceFromSource[edge.to] >
            distanceFromSource[edge.from] + edge.weight) {

            return false;
        }
    }
    return true;
}

int main() {
    // -------- DUMMY INPUT (replace later) --------
    int numberOfNodes = 5;
    int sourceNode = 0;

    edgeList = {
        {0, 1, 6},
        {0, 2, 7},
        {1, 2, 8},
        {1, 3, 5},
        {1, 4, -4},
        {2, 3, -3},
        {2, 4, 9},
        {3, 1, -2},
        {4, 0, 2},
        {4, 3, 7}
    };

    /*
    // -------- INPUT SECTION (commented) --------
    int numberOfNodes, numberOfEdges;
    cin >> numberOfNodes >> numberOfEdges;

    for (int i = 0; i < numberOfEdges; i++) {
        int from, to, weight;
        cin >> from >> to >> weight;
        edgeList.push_back({from, to, weight});
    }

    int sourceNode;
    cin >> sourceNode;
    */
    // -------------------------------------------

    if (!bellmanFord(numberOfNodes, sourceNode)) {
        cout << "Negative weight cycle detected\n";
        return 0;
    }

    for (int node = 0; node < numberOfNodes; node++) {
        cout << "Node " << node << ": ";
        if (distanceFromSource[node] == INF) {
            cout << "INF\n";
        } else {
            cout << distanceFromSource[node] << " | Path: ";
            printPath(node);
            cout << "\n";
        }
    }

    return 0;
}
