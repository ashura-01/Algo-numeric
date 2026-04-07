#include <bits/stdc++.h>
using namespace std;

#define INF 1e9

struct Edge {
    int to, weight;
};

void floydWarshall(int numOfVertices, vector<vector<pair<int, int>>> &graph)
{
    vector<vector<int>> distance(numOfVertices, vector<int>(numOfVertices, INF));
    vector<vector<int>> predecessor(numOfVertices, vector<int>(numOfVertices, -1));

    for (int vertex = 0; vertex < numOfVertices; vertex++)
    {
        distance[vertex][vertex] = 0;
        for (auto &p : graph[vertex])
        {
            int neighbor = p.first;
            int weight = p.second;
            distance[vertex][neighbor] = min(distance[vertex][neighbor], weight);
            predecessor[vertex][neighbor] = vertex;
        }
    }

    for (int k = 0; k < numOfVertices; k++)
        for (int i = 0; i < numOfVertices; i++)
            for (int j = 0; j < numOfVertices; j++)
                if (distance[i][k] < INF && distance[k][j] < INF &&
                    distance[i][j] > distance[i][k] + distance[k][j])
                {
                    distance[i][j] = distance[i][k] + distance[k][j];
                    predecessor[i][j] = predecessor[k][j];
                }

    for (int i = 0; i < numOfVertices; i++)
        if (distance[i][i] < 0)
        {
            cout << "Negative Cycle Detected" << endl;
            return;
        }

    // Print distance matrix
    cout << "Shortest Distances Matrix:\n";
    for (int i = 0; i < numOfVertices; i++)
    {
        for (int j = 0; j < numOfVertices; j++)
        {
            if (distance[i][j] == INF)
                cout << "INF ";
            else
                cout << distance[i][j] << " ";
        }
        cout << endl;
    }
}

int main()
{
    int V = 4; // number of vertices
    vector<vector<pair<int,int>>> graph(V);

    // Add edges: graph[u].push_back({v, weight});
    graph[0].push_back({1, 5});
    graph[0].push_back({3, 10});
    graph[1].push_back({2, 3});
    graph[2].push_back({3, 1});

    floydWarshall(V, graph);

    return 0;
}