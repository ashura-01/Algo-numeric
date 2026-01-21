#include <bits/stdc++.h>
using namespace std;
void dfs(int node, vector<vector<int>> &graph, vector<bool> &visited, stack<int> &topostack)
{
    visited[node] = true;
    for (auto neighbors : graph[node])
    {
        if (!visited[neighbors])
        {
            dfs(neighbors, graph, visited, topostack);
        }
    }

    topostack.push(node);
}

void toposort(int nodesNumber, vector<vector<int>> &graph, vector<bool> &visited, stack<int> &topostack)
{
    for (int i = 0; i < nodesNumber; i++)
    {
        if (!visited[i])
        {
            dfs(i, graph, visited, topostack);
        }
    }
}

void input(int nodes, int edges, vector<vector<int>> &graph)
{
    for (int i = 0; i < edges; i++)
    {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
    }
}
int main()
{
    int nodes, edges;
    cout << "input number of nodes: ";
    cin >> nodes;
    cout << "input number of edges: ";
    cin >> edges;

    vector<vector<int>> graph(nodes);
    input(nodes, edges, graph);

    vector<bool> visited(nodes, false);
    stack<int> topoStack;

    toposort(nodes, graph, visited, topoStack);

    while (!topoStack.empty())
    {
        cout << topoStack.top() << "---->";
        topoStack.pop();
    }
    cout << endl;

    return 0;
}