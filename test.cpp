#include <bits/stdc++.h>
using namespace std;

struct edge
{
    int u_tex, v_tex, weight;
};
int findparent(int vertex, vector<int> &parent)
{
    if (vertex != parent[vertex])
    {
        parent[vertex] = findparent(parent[vertex], parent);
    }

    return parent[vertex];
}

void unionsets(int u, int v, vector<int> &parent, vector<int> &rank)
{
    int pu = findparent(u, parent);
    int pv = findparent(v, parent);

    if (pu != pv)
    {
        if (rank[pu] > rank[pv])
        {
            swap(pu, pv);
        }
        parent[pv]=pu;
        if (rank[pu] == rank[pv])
            rank[pu]++;
    }
}

pair<int, vector<edge>> kruskal(int numVertices, vector<edge> &edges)
{
    vector<int> parent(numVertices);
    vector<int> rank(numVertices, 0);
    vector<edge> mstedges;
    int totalWeight;

    sort(edges.begin(), edges.end(), [](edge &a, edge &b)
         { return a.weight < b.weight; });
    
    for (int i = 0; i < numVertices; i++)
    {
        parent[i]=i;
    }

    for(auto &connection: edges)
    {
        int pu = findparent(connection.u_tex, parent);
        int pv= findparent(connection.v_tex, parent);

        if (pu!=pv)
        {
            unionsets(connection.u_tex, connection.v_tex, parent, rank);
            mstedges.push_back(connection);
            totalWeight+= connection.weight;
        }
        
    }
    
    return {totalWeight, mstedges};
}

int main()
{
    int V = 4;  // number of vertices
    int E = 5;  // number of edges

    vector<edge> edges = {
        {0, 1, 10},
        {0, 2, 6},
        {0, 3, 5},
        {1, 3, 15},
        {2, 3, 4}
    };

    auto result = kruskal(V, edges);

    cout << "Total MST Weight: " << result.first << endl;
    cout << "Edges in MST:\n";

    for (auto &e : result.second)
    {
        cout << e.u_tex << " - " << e.v_tex << " : " << e.weight << endl;
    }

    return 0;
}