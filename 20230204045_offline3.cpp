#include <windows.h>
#include <psapi.h>
#include <stdio.h>

#include <bits/stdc++.h>
using namespace std;

#pragma comment(lib, "Psapi.lib") // Needed for MSVC linking

// Replace with your CPU's approximate average power (Watts)
#define CPU_POWER_WATTS 65.0
// Bangladesh grid emission factor (kg CO₂ / kWh)
#define BD_EMISSION_FACTOR 0.62

const int INF = INT_MAX;

bool bellmanFord(vector<vector<pair<int, int>>> &graph, vector<int> &distance, int source)
{
    int numOfVertices = graph.size();
    distance.assign(numOfVertices, INF);
    distance[source] = 0;

    for (int i = 0; i < numOfVertices - 1; i++)
    {
        for (int u = 0; u < numOfVertices; u++)
        {
            if (distance[u] == INF)
                continue;

            for (auto &edge : graph[u])
            {
                int v = edge.first;
                int weight = edge.second;
                if (distance[v] > distance[u] + weight)
                    distance[v] = distance[u] + weight;
            }
        }
    }

    for (int u = 0; u < numOfVertices; u++)
    {
        if (distance[u] == INF)
            continue;

        for (auto &edge : graph[u])
        {
            int v = edge.first;
            int weight = edge.second;
            if (distance[v] > distance[u] + weight)
                return false;
        }
    }

    return true;
}

void dijkstra(vector<vector<pair<int, int>>> &graph, int source, vector<int> &distance, vector<int> &predecessor)
{
    int numOfVertices = graph.size();
    distance.assign(numOfVertices, INF);
    predecessor.assign(numOfVertices, -1);
    distance[source] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, source});

    while (!pq.empty())
    {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();

        if (d > distance[u])
            continue;

        for (auto &edge : graph[u])
        {
            int v = edge.first;
            int weight = edge.second;
            if (distance[v] > distance[u] + weight)
            {
                distance[v] = distance[u] + weight;
                predecessor[v] = u;
                pq.push({distance[v], v});
            }
        }
    }
}

vector<vector<int>> johnsonsAlgorithm(vector<vector<pair<int, int>>> &graph, vector<vector<int>> &predecessorMatrix)
{
    int numOfVertices = graph.size();

    vector<vector<pair<int, int>>> modifiedGraph = graph;
    modifiedGraph.push_back(vector<pair<int, int>>());

    for (int v = 0; v < numOfVertices; v++)
        modifiedGraph[numOfVertices].push_back({v, 0});

    vector<int> h(numOfVertices + 1);
    if (!bellmanFord(modifiedGraph, h, numOfVertices))
    {
        cout << "Graph contains a negative weight cycle" << endl;
        return {};
    }

    vector<vector<pair<int, int>>> reweightedGraph(numOfVertices);
    for (int u = 0; u < numOfVertices; u++)
    {
        for (auto &edge : graph[u])
        {
            int v = edge.first;
            int weight = edge.second;
            int newWeight = weight + h[u] - h[v];
            reweightedGraph[u].push_back({v, newWeight});
        }
    }

    vector<vector<int>> allPairsDistance(numOfVertices, vector<int>(numOfVertices, INF));
    predecessorMatrix.assign(numOfVertices, vector<int>(numOfVertices, -1));

    for (int u = 0; u < numOfVertices; u++)
    {
        vector<int> distance, predecessor;
        dijkstra(reweightedGraph, u, distance, predecessor);
        for (int v = 0; v < numOfVertices; v++)
        {
            if (distance[v] != INF)
            {
                allPairsDistance[u][v] = distance[v] + h[v] - h[u];
                predecessorMatrix[u][v] = predecessor[v];
            }
        }
    }

    return allPairsDistance;
}

void floydWarshall(int numOfVertices, vector<vector<pair<int, int>>> &graph)
{
    vector<vector<int>> distance(numOfVertices, vector<int>(numOfVertices, INF));
    vector<vector<int>> predecessor(numOfVertices, vector<int>(numOfVertices, -1));

    for (int vertex = 0; vertex < numOfVertices; vertex++)
    {
        distance[vertex][vertex] = 0;
        for (int i = 0; i < graph[vertex].size(); i++)
        {
            int neighbor = graph[vertex][i].first;
            int weight = graph[vertex][i].second;
            distance[vertex][neighbor] = min(distance[vertex][neighbor], weight);
            predecessor[vertex][neighbor] = vertex;
        }
    }

    for (int k = 0; k < numOfVertices; k++)
    {
        for (int i = 0; i < numOfVertices; i++)
        {
            for (int j = 0; j < numOfVertices; j++)
            {
                if (distance[i][k] < INF && distance[k][j] < INF &&
                    distance[i][j] > distance[i][k] + distance[k][j])
                {
                    distance[i][j] = distance[i][k] + distance[k][j];
                    predecessor[i][j] = predecessor[k][j];
                }
            }
        }
    }

    for (int i = 0; i < numOfVertices; i++)
    {
        if (distance[i][i] < 0)
        {
            cout << "Negative Cycle" << endl;
            return;
        }
    }
}

int generateDenseGraph(int numOfVertices)
{
    ofstream file("dense.txt");
    int edges = (numOfVertices * (numOfVertices - 1)) / 2;
    file << numOfVertices << " " << edges << endl;

    for (int i = 0; i < numOfVertices; i++)
    {
        for (int j = i + 1; j < numOfVertices; j++)
        {
            int weight = rand() % 100 + 1;
            file << i << " " << j << " " << weight << endl;
        }
    }

    file.close();
    return edges;
}

int generateSparseGraph(int numOfVertices)
{
    ofstream file("sparse.txt");
    int edges = rand() % 51 + 150;
    file << numOfVertices << " " << edges << endl;

    set<pair<int, int>> usedEdges;

    while ((int)usedEdges.size() < edges)
    {
        int u = rand() % numOfVertices;
        int v = rand() % numOfVertices;

        if (u == v)
            continue;

        if (u > v)
            swap(u, v);

        if (usedEdges.count({u, v}) == 0)
        {
            usedEdges.insert({u, v});
            int weight = rand() % 100 + 1;
            file << u << " " << v << " " << weight << endl;
        }
    }

    file.close();
    return edges;
}

vector<vector<pair<int, int>>> readGraphFromFile(string filename, int &V)
{
    ifstream file(filename);

    int E;
    file >> V >> E;

    vector<vector<pair<int, int>>> adj(V);

    for (int i = 0; i < E; i++)
    {
        int u, v, w;
        file >> u >> v >> w;

        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    file.close();
    return adj;
}

int main()
{
    int numOfVertices = 50;
    
    
    //data generatrion
    int numberOfEdgesSparse = generateSparseGraph(50);
    int numberOfEdgesDense = generateDenseGraph(50);

    vector<vector<pair<int, int>>> denseGraph = readGraphFromFile("dense.txt", numberOfEdgesDense);
    vector<vector<pair<int, int>>> sparseGraph = readGraphFromFile("sparse.txt", numberOfEdgesDense);
    vector<vector<int>> predecessorMatrix;

    LARGE_INTEGER freq, start, end;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&start);

    // -------- Your algorithm here --------

    // floydWarshall(numOfVertices, denseGraph);
    // floydWarshall(numOfVertices, sparseGraph);

    // vector<vector<int>> allPairsDistance = johnsonsAlgorithm(denseGraph, predecessorMatrix);
    vector<vector<int>> allPairsDistance = johnsonsAlgorithm(sparseGraph, predecessorMatrix);

    // -------------------------------------

    QueryPerformanceCounter(&end);

    double elapsed = (double)(end.QuadPart - start.QuadPart) / freq.QuadPart;
    double energy = CPU_POWER_WATTS * elapsed;    // Joules
    double energy_kWh = energy / 3.6e6;           // kWh
    double co2 = energy_kWh * BD_EMISSION_FACTOR; // kg CO₂

    // ----- Memory usage -----
    PROCESS_MEMORY_COUNTERS_EX pmc;
    if (GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS *)&pmc, sizeof(pmc)))
    {
        SIZE_T peakMemUsed = pmc.PeakWorkingSetSize; // Peak RAM usage

        printf("Execution time: %.6f seconds\n", elapsed);
        printf("Estimated energy consumption: %.2f Joules\n", energy);
        printf("Peak Memory Usage: %zu KB\n", peakMemUsed / 1024);
        printf("Estimated CO2 emissions (Bangladesh): %.8f kg\n", co2);
    }
    else
    {
        printf("Failed to get memory info.\n");
    }

    return 0;
}