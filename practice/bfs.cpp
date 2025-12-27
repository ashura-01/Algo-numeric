#include <bits/stdc++.h>
using namespace std;

vector<int> bfs(vector<vector<int>> &graph, int source_vertex, int number_of_vertices)
{
    vector<bool> visited(number_of_vertices, false);
    vector<int> result;

    queue<int> que;
    que.push(source_vertex);

    visited[source_vertex] = true;
    result.push_back(source_vertex);

    while (!que.empty())
    {
        int current = que.front();
        que.pop();

        for (int neighbor : graph[current])
        {
            if (!visited[neighbor])
            {
                que.push(neighbor);
                visited[neighbor] = true;
                result.push_back(neighbor);
            }
        }
    }
    return result;
}
void input(vector<vector<int>> &graph, int edges)
{
    cout << "enter edges(u,v):" << endl;
    for (int i = 0; i < edges; i++)
    {
        int vertex, neighbor;
        cout << "vertex---->neighbor: ";
        cin >> vertex >> neighbor;

        graph[vertex].push_back(neighbor);
    }
}
void output(vector<vector<int>> &graph)
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
    int vertices, edges;
    cout<<"input vertices and edge numbers: ";
    cin>>vertices>>edges;

    vector<vector<int>> graph(vertices);
    input(graph,edges);
    output(graph);
    return 0;
}