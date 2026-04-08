#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int n, minCost = INT_MAX;
vector<vector<int>> graph;
vector<bool> visited;
vector<int> path, bestPath;

void tsp(int city, int count, int cost)
{
    if (count == n && graph[city][0] != 0)
    {
        int total = cost + graph[city][0];
        if (total < minCost)
        {
            minCost = total;
            bestPath = path;
            bestPath.push_back(0);
        }
        return;
    }

    for (int i = 0; i < n; i++)
    {
        if (!visited[i] && graph[city][i] != 0)
        {
            int newCost = cost + graph[city][i];
            if (newCost < minCost)
            {
                visited[i] = true;
                path.push_back(i);

                tsp(i, count + 1, newCost);

                visited[i] = false;
                path.pop_back();
            }
        }
    }
}

int main()
{
    graph = {
        {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}
    };

    n = graph.size();
    visited.assign(n, false);

    visited[0] = true;
    path.push_back(0);

    tsp(0, 1, 0);

    cout << "Cost: " << minCost << "\nPath: ";
    for (int x : bestPath) cout << x << " ";

    return 0;
}