#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int from;
    int to;
    int weight;
};

const int INF = 1e9;

vector<vector<Edge>> graph;   // <-- renamed
vector<int> distanceFromSource;
vector<int> parentNode;
vector<bool> visited;
stack<int> topoStack;

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

// TOPOLOGICAL SORT (DFS)
void topologicalSort(int node) {
    visited[node] = true;

    for (auto &edge : graph[node]) {
        if (!visited[edge.to]) {
            topologicalSort(edge.to);
        }
    }
    topoStack.push(node);
}

// DAG SHORTEST PATH
void dagShortestPath(int numberOfNodes, int source) {
    initializeSingleSource(numberOfNodes, source);

    visited.assign(numberOfNodes, false);

    for (int node = 0; node < numberOfNodes; node++) {
        if (!visited[node]) {
            topologicalSort(node);
        }
    }

    while (!topoStack.empty()) {
        int currentNode = topoStack.top();
        topoStack.pop();

        for (auto &edge : graph[currentNode]) {
            relax(edge.from, edge.to, edge.weight);
        }
    }
}

int main() {
    // -------- DUMMY INPUT --------
    int numberOfNodes = 6;
    int sourceNode = 1;

    graph.resize(numberOfNodes);

    graph[0].push_back({0, 1, 5});
    graph[0].push_back({0, 2, 3});
    graph[1].push_back({1, 3, 6});
    graph[1].push_back({1, 2, 2});
    graph[2].push_back({2, 4, 4});
    graph[2].push_back({2, 5, 2});
    graph[2].push_back({2, 3, 7});
    graph[3].push_back({3, 4, -1});
    graph[4].push_back({4, 5, -2});

    dagShortestPath(numberOfNodes, sourceNode);

    for (int node = 0; node < numberOfNodes; node++) {
        cout << "Node " << node << ": ";
        if (distanceFromSource[node] == INF) {
            cout << "INF\n";
        } else {
            cout << distanceFromSource[node] << "\n";
        }
    }

    return 0;
}
