#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int vertexU, vertexV, weight;
};

// Find with path compression
int findParent(int vertex, vector<int> &parent)
{
    if (parent[vertex] != vertex)
        parent[vertex] = findParent(parent[vertex], parent);
    return parent[vertex];
}

// Union by rank
void unionSets(int u, int v, vector<int> &parent, vector<int> &rank)
{
    int pu = findParent(u, parent);
    int pv = findParent(v, parent);

    if (pu != pv)
    {
        if (rank[pu] < rank[pv])
            swap(pu, pv);

        parent[pv] = pu;

        if (rank[pu] == rank[pv])
            rank[pu]++;
    }
}

// Kruskal Algorithm
pair<int, vector<Edge>> kruskalMST(int numVertices, vector<Edge> &edges)
{
    sort(edges.begin(), edges.end(), [](Edge &a, Edge &b)
    {
        return a.weight < b.weight;
    });

    vector<int> parent(numVertices);
    vector<int> rank(numVertices, 0);

    for (int i = 0; i < numVertices; i++)
        parent[i] = i;

    int totalWeight = 0;
    vector<Edge> mstEdges;

    for (auto &e : edges)
    {
        int pu = findParent(e.vertexU, parent);
        int pv = findParent(e.vertexV, parent);

        if (pu != pv)
        {
            unionSets(e.vertexU, e.vertexV, parent, rank);
            mstEdges.push_back(e);
            totalWeight += e.weight;
        }
    }

    return {totalWeight, mstEdges};
}

int main()
{
    int V, E;
    cin >> V >> E;

    vector<Edge> edges(E);

    for (int i = 0; i < E; i++)
    {
        cin >> edges[i].vertexU >> edges[i].vertexV >> edges[i].weight;
    }

    auto result = kruskalMST(V, edges);

    cout << "Total MST Weight: " << result.first << endl;
    cout << "Edges in MST:\n";

    for (auto &e : result.second)
    {
        cout << e.vertexU << " - " << e.vertexV << " : " << e.weight << endl;
    }

    return 0;
}