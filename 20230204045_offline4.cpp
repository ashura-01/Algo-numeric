#include <windows.h>
#include <psapi.h>
#include <bits/stdc++.h>
using namespace std;
#pragma comment(lib, "Psapi.lib")
#define CPU_POWER_WATTS 65.0
#define BD_EMISSION_FACTOR 0.62

struct Edge {
    int vertexU, vertexV, weight;
};

// Sparse Graph Generator 
void generateSparseGraph(string filename, int numVertices = 50) {
    int minEdges = 100;
    int maxEdges = 150;
    int numEdges = minEdges + rand() % (maxEdges - minEdges + 1);

    ofstream file(filename);
    file << numVertices << " " << numEdges << "\n";

    set<pair<int,int>> existingEdges;
    while ((int)existingEdges.size() < numEdges) {
        int u = rand() % numVertices;
        int v = rand() % numVertices;
        if (u == v) continue;
        if (u > v) swap(u, v);
        if (existingEdges.count({u,v})) continue;
        existingEdges.insert({u,v});
        int w = rand() % 100 + 1;
        file << u << " " << v << " " << w << "\n";
    }

    file.close();
}
// Dense Graph Generator 
void generateDenseGraph(string filename, int numVertices = 50) {
    ofstream file(filename);
    int numEdges = numVertices * (numVertices - 1) / 2;
    file << numVertices << " " << numEdges << "\n";

    for (int u = 0; u < numVertices; u++) {
        for (int v = u + 1; v < numVertices; v++) {
            int w = rand() % 100 + 1;
            file << u << " " << v << " " << w << "\n";
        }
    }

    file.close();
}
// Load graph 
void loadGraph(string filename, int &numVertices, vector<Edge> &edges) {
    ifstream file(filename);
    int numEdges;
    file >> numVertices >> numEdges;
    edges.clear();
    for (int i = 0; i < numEdges; i++) {
        Edge e;
        file >> e.vertexU >> e.vertexV >> e.weight;
        edges.push_back(e);
    }
    file.close();
}
// Prims Algo
pair<int, vector<Edge>> primMST(int numVertices, vector<Edge> &edges) {
    vector<vector<pair<int,int>>> adj(numVertices);
    for (auto &e : edges) {
        adj[e.vertexU].push_back({e.vertexV, e.weight});
        adj[e.vertexV].push_back({e.vertexU, e.weight});
    }

    vector<int> key(numVertices, INT_MAX);
    vector<int> parent(numVertices, -1);
    vector<bool> inMST(numVertices, false);

    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;
    key[0] = 0;
    pq.push({0, 0});

    int totalWeight = 0;
    vector<Edge> mstEdges;

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        if (inMST[u]) continue;
        inMST[u] = true;
        if (parent[u] != -1)
            mstEdges.push_back({parent[u], u, key[u]});
        totalWeight += key[u];

        for (auto &p : adj[u]) {
            int v = p.first;
            int w = p.second;
            if (!inMST[v] && w < key[v]) {
                key[v] = w;
                parent[v] = u;
                pq.push({key[v], v});
            }
        }
    }

    return {totalWeight, mstEdges};
}
// Kruskals Algo
int findParent(int vertex, vector<int> &parent) {
    if (parent[vertex] != vertex)
        parent[vertex] = findParent(parent[vertex], parent);
    return parent[vertex];
}

void unionSets(int u, int v, vector<int> &parent, vector<int> &rank) {
    int pu = findParent(u, parent);
    int pv = findParent(v, parent);
    if (pu != pv) {
        if (rank[pu] < rank[pv]) swap(pu, pv);
        parent[pv] = pu;
        if (rank[pu] == rank[pv]) rank[pu]++;
    }
}
pair<int, vector<Edge>> kruskalMST(int numVertices, vector<Edge> &edges) {
    sort(edges.begin(), edges.end(), [](Edge &a, Edge &b) { return a.weight < b.weight; });

    vector<int> parent(numVertices);
    vector<int> rank(numVertices, 0);
    for (int i = 0; i < numVertices; i++) parent[i] = i;

    int totalWeight = 0;
    vector<Edge> mstEdges;

    for (auto &e : edges) {
        int pu = findParent(e.vertexU, parent);
        int pv = findParent(e.vertexV, parent);
        if (pu != pv) {
            unionSets(e.vertexU, e.vertexV, parent, rank);
            mstEdges.push_back(e);
            totalWeight += e.weight;
        }
    }

    return {totalWeight, mstEdges};
}
int main()
{
    srand(time(0));
//---------------- txt graph generation here-----------------

    // generateSparseGraph("sparse_graph.txt");
    // generateDenseGraph("dense_graph.txt");

//---------------- putting graph in vector--------------------
    int numVerticesSparse, numVerticesDense;
    vector<Edge> sparseEdges, denseEdges;

    loadGraph("sparse_graph.txt", numVerticesSparse, sparseEdges);
    loadGraph("dense_graph.txt", numVerticesDense, denseEdges);
//-------------------------------------------------------------------

    LARGE_INTEGER freq, start, end;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&start);

    // -------- Your algorithm here --------

    // auto primSparse = primMST(numVerticesSparse, sparseEdges);
    // auto kruskalSparse = kruskalMST(numVerticesSparse, sparseEdges);

    // auto primDense = primMST(numVerticesDense, denseEdges);
    auto kruskalDense = kruskalMST(numVerticesDense, denseEdges);

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
        printf("Estimated energy consumption: %.4f Joules\n", energy);
        printf("Peak Memory Usage: %zu KB\n", peakMemUsed / 1024);
        printf("Estimated CO2 emissions (Bangladesh): %.12f kg\n", co2);
    }
    else
    {
        printf("Failed to get memory info.\n");
    }
    return 0;
}