#include <bits/stdc++.h>
using namespace std;

#define INF 1e9

int n;
vector<vector<int>> dist;
int ans = INF;

void tsp(vector<bool> &visited, int pos, int count, int cost)
{
    if (count == n) // all visited
    {
        ans = min(ans, cost + dist[pos][0]);
        return;
    }

    for (int i = 0; i < n; i++)
    {
        if (!visited[i])
        {
            visited[i] = true;
            tsp(visited, i, count + 1, cost + dist[pos][i]);
            visited[i] = false; // backtrack
        }
    }
}

int main()
{
    cin >> n;
    dist.assign(n, vector<int>(n));

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> dist[i][j];

    vector<bool> visited(n, false);
    visited[0] = true;

    tsp(visited, 0, 1, 0);

    cout << "Minimum TSP cost: " << ans << endl;
}