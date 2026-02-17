#include <windows.h>
#include <psapi.h>
#include <stdio.h>

#include <bits/stdc++.h>
using namespace std;

#pragma comment(lib, "Psapi.lib")  // Needed for MSVC linking

// Replace with your CPU's approximate average power (Watts)
#define CPU_POWER_WATTS 65.0
// Bangladesh grid emission factor (kg CO₂ / kWh)
#define BD_EMISSION_FACTOR 0.62

const int INF = INT_MAX;

bool bellmanFord(vector<vector<pair<int, int>>> &adj, vector<int> &dist, int src)
{
    int V = adj.size();
    dist.assign(V, INF);
    dist[src] = 0;
    for(int i=0; i<V-1; i++)
    {
        for(int u=0; u<V; u++)
        {
            if(dist[u]==INF)
                continue;

            for(auto &edge : adj[u])
            {
                int v = edge.first;
                int w = edge.second;
                if(dist[v] > dist[u]+w)
                {
                    dist[v] = dist[u] + w;
                }
            }
        }
    }
    for(int u=0; u<V; u++)
    {
        if(dist[u]==INF)
            continue;

        for(auto &edge : adj[u])
        {
            int v = edge.first;
            int w = edge.second;
            if(dist[v] > dist[u] + w)
            {
                return false;
            }
        }
    }
    return true;
}

void dijkstra(vector<vector<pair<int, int>>> &adj, int src, vector<int> &dist, vector<int> &pi)
{
    int V = adj.size();
    dist.assign(V, INF);
    pi.assign(V, -1);
    dist[src] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, src});

    while(!pq.empty())
    {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();

        if(d>dist[u])
            continue;

        for(auto &edge : adj[u])
        {
            int v = edge.first;
            int w = edge.second;
            if(dist[v] > dist[u] + w)
            {
                dist[v] = dist[u] + w;
                pi[v] = u;
                pq.push({dist[v], v});
            }
        }
    }
}

vector<vector<int>> johnsonsAlgorithm(vector<vector<pair<int, int>>> &adj, vector<vector<int>> &piMatrix)
{
    int V = adj.size();

    vector<vector<pair<int, int>>> modifiedAdj = adj;
    modifiedAdj.push_back(vector<pair<int, int>>());
    for(int v=0; v<V; v++)
    {
        modifiedAdj[V].push_back({v, 0});
    }

    vector<int> h(V + 1);
    if(!bellmanFord(modifiedAdj, h, V))
    {
        cout << "Graph contains a negative weight cycle" << endl;
        return {};
    }

    vector<vector<pair<int, int>>> reweightedAdj(V);
    for(int u=0; u<V; u++)
    {
        for(auto &edge : adj[u])
        {
            int v = edge.first;
            int w = edge.second;
            int newWeight = w + h[u] - h[v];
            reweightedAdj[u].push_back({v, newWeight});
        }
    }

    vector<vector<int>> allPairsDist(V, vector<int>(V, INF));
    piMatrix.assign(V, vector<int>(V, -1));

    for(int u=0; u<V; u++)
    {
        vector<int> dist, pi;
        dijkstra(reweightedAdj, u, dist, pi);
        for(int v=0; v<V; v++)
        {
            if(dist[v]!=INF)
            {
                allPairsDist[u][v] = dist[v] + h[v] - h[u];
                piMatrix[u][v] = pi[v];
            }
        }
    }

    return allPairsDist;
}

int main() {
    freopen("sparse_graph.txt", "r", stdin);

    LARGE_INTEGER freq, start, end;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&start);

    // -------- Your algorithm here --------
    int V,E;
    cin >> V >> E;

    vector<vector<pair<int,int>>> adj(V);
    while(E--)
    {
        int u,v,w;
        cin >> u >> v >> w;
        adj[u].push_back({v,w});
    }

    vector<vector<int>> piMatrix;
    vector<vector<int>> distMatrix = johnsonsAlgorithm(adj, piMatrix);
    /*
    if(!distMatrix.empty())
    {
        cout << "Shortest Distance Matrix:" << endl;
        for(int i=0; i<V; i++)
        {
            for(int j=0; j<V; j++)
            {
                if(distMatrix[i][j] == INF)
                    cout << "INF ";
                else
                    cout << distMatrix[i][j] << " ";
            }
            cout << endl;
        }

        cout << endl;
        cout << "Predecessor Matrix:" << endl;
        for(int i=0; i<V; i++)
        {
            for(int j=0; j<V; j++)
            {
                if(piMatrix[i][j] == -1)
                    cout << "NIL ";
                else
                    cout << piMatrix[i][j] << " ";
            }
            cout << endl;
        }
    }
    */
    // -------------------------------------

    QueryPerformanceCounter(&end);

    double elapsed = (double)(end.QuadPart - start.QuadPart) / freq.QuadPart;
    double energy = CPU_POWER_WATTS * elapsed;         // Joules
    double energy_kWh = energy / 3.6e6;                // kWh
    double co2 = energy_kWh * BD_EMISSION_FACTOR;      // kg CO₂

    // ----- Memory usage -----
    PROCESS_MEMORY_COUNTERS_EX pmc;
    if (GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc))) {
        SIZE_T peakMemUsed = pmc.PeakWorkingSetSize; // Peak RAM usage

        printf("Execution time: %.6f seconds\n", elapsed);
        printf("Estimated energy consumption: %.2f Joules\n", energy);
        printf("Peak Memory Usage: %zu KB\n", peakMemUsed / 1024);
        printf("Estimated CO2 emissions (Bangladesh): %.8f kg\n", co2);
    } else {
        printf("Failed to get memory info.\n");
    }

    return 0;
}
