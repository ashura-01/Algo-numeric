#include <bits/stdc++.h>
using namespace std;
enum colors
{
    WHITE,
    GRAY,
    BLACk
};

void input(int nodes, int edges, vector<vector<int>> &graph)
{
    for (int i = 0; i < edges; i++)
    {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
    }
}

bool dfs(int node, vector<vector<int>> &graph, vector<colors> &color, vector<int> &path, vector<int> &cycle)
{
    color[node] = GRAY;
    path.push_back(node);

    for (auto neighbor : graph[node])
    {
        if (color[neighbor] == WHITE)
        {
            if (dfs(neighbor, graph, color, path, cycle))
                return true;
        }
        else if (color[neighbor] == GRAY)
        {
            auto it = find(path.begin(), path.end(), neighbor);
            cycle.assign(it, path.end());
            cycle.push_back(neighbor);
            return true;
        }
    }
    color[node] = BLACk;
    path.pop_back();
    return false;
}
int main()
{
    int nodes, edges;
    cout << "input nodes: ";
    cin >> nodes;
    cout << "input edges: ";
    cin >> edges;

    vector<vector<int>> graph(nodes);
    input(nodes, edges, graph);

    vector<colors> color(nodes, WHITE);
    vector<int> path;
    vector<int> cycle;

    int source;
    cout << "input source: ";
    cin >> source;

    bool hasCycle = false;
    for (int i = 0; i < nodes; i++)
    {
        if (color[i] == WHITE)
        {
            if (dfs(i, graph, color, path, cycle))
            {
                hasCycle = true;
                break;
            }
        }
    }

    for (auto elem : cycle)
    {
        cout << elem << "---->>";
    }
    cout << endl;

    return 0;
}