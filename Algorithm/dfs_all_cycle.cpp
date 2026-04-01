#include <bits/stdc++.h>
using namespace std;

enum colors{white, gray, black};

vector<vector<int>> graph;
vector<colors> color;
vector<int> path;
vector<vector<int>> allcycles;

void dfs(int source)
{
    color[source]=gray;
    path.push_back(source);

    for(auto neighbor : graph[source])
    {
        if(color[neighbor]==white)
        {
            dfs(neighbor);
        }
        else if(color[neighbor]==gray)
        {
            auto it = find(path.begin(), path.end(), neighbor);
            if (it!= path.end())
            {
                vector<int> cycle(it, path.end());
                cycle.push_back(neighbor);
                allcycles.push_back(cycle);
            }
            
        }
    }
    color[source]= black;
    path.pop_back();
}
