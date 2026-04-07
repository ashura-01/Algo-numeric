#include <bits/stdc++.h>
using namespace std;

struct Edge
{
    int u, v, weight;
};

// Prim's MST function
pair<int, vector<Edge>> primMST(int numVertices, vector<vector<pair<int, int>>> &adj)
{
    vector<int> key(numVertices, INT_MAX);
    vector<int> parent(numVertices, -1);
    vector<bool> inMST(numVertices, false);

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    key[0] = 0;
    pq.push({0, 0});

    int totalWeight = 0;
    vector<Edge> mstEdges;

    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();

        if (inMST[u])
            continue;

        inMST[u] = true;

        if (parent[u] != -1)
            mstEdges.push_back({parent[u], u, key[u]});

        totalWeight += key[u];

        for (auto &p : adj[u])
        {
            int v = p.first;
            int w = p.second;

            if (!inMST[v] && w < key[v])
            {
                key[v] = w;
                parent[v] = u;
                pq.push({key[v], v});
            }
        }
    }

    return make_pair(totalWeight, mstEdges);
}

int main()
{
    int numVertices = 5;

    // predefined adjacency list
    vector<vector<pair<int, int>>> adj = {
        {{1, 2}, {3, 6}},                 // edges from vertex 0
        {{0, 2}, {2, 3}, {3, 8}, {4, 5}}, // edges from vertex 1
        {{1, 3}, {4, 7}},                 // edges from vertex 2
        {{0, 6}, {1, 8}, {4, 9}},         // edges from vertex 3
        {{1, 5}, {2, 7}, {3, 9}}          // edges from vertex 4
    };

    // Pre-C++17 style
    pair<int, vector<Edge>> result = primMST(numVertices, adj);
    int totalWeight = result.first;
    vector<Edge> mstEdges = result.second;

    cout << "Total weight of MST: " << totalWeight << "\n";
    cout << "Edges in MST:\n";
    for (auto &e : mstEdges)
        cout << e.u << " - " << e.v << " (weight " << e.weight << ")\n";

    return 0;
}