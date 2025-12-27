#include <bits/stdc++.h>
using namespace std;

enum colors
{
    WHITE,
    GRAY,
    BLACK
};

void dfs(vector<vector<int>> &graph, int source_vertex, vector<colors> &color, vector<int> &result, vector<int> &parents)
{
    color[source_vertex] = GRAY;
    result.push_back(source_vertex);

    for (auto neighbors : graph[source_vertex])
    {
        if (color[neighbors] == WHITE)
        {
            parents[neighbors] = source_vertex;
            dfs(graph, neighbors, color, result, parents);
        }
    }
    color[source_vertex] = BLACK;
}

void input_graph(vector<vector<int>> &graph, int edges)
{
    cout << "Enter edges (u v):" << endl;
    for (int i = 0; i < edges; i++)
    {
        int u, v;
        cout << "input u--->v: ";
        cin >> u >> v;

        graph[u].push_back(v);
    }
}
void output_graph(vector<vector<int>> &graph)
{
    for (int i = 0; i < graph.size(); i++)
    {
        cout << i << "---->";
        for (auto neighbors : graph[i])
        {
            cout << neighbors << " ";
        }
        cout << endl;
    }
}
int main()
{
    int verticies, edges;
    cout << "input verticies and edge numbers: ";
    cin >> verticies >> edges;

    vector<vector<int>> graph(verticies);
    input_graph(graph, edges);

    vector<colors> color(verticies, WHITE);
    vector<int> parent(verticies, -1);
    vector<int> result;

    dfs(graph, 0, color, result, parent);
    
    cout << "DFS Order:\n";
    for (int v : result)
        cout << v << " ";

    return 0;
}
