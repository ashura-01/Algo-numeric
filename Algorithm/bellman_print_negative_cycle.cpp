#include <bits/stdc++.h>
using namespace std;

struct Edge
{
    int from, to, weight;
};

const int INF = 1e9;

vector<Edge> edgeList;
vector<int> distanceFromSource, parentNode;

// INITIALIZE
void initializeSingleSource(int numberOfNodes, int source)
{
    distanceFromSource.assign(numberOfNodes, INF);
    parentNode.assign(numberOfNodes, -1);
    distanceFromSource[source] = 0;
}

// RELAX
void relax(int from, int to, int weight)
{
    if (distanceFromSource[from] != INF &&
        distanceFromSource[to] > distanceFromSource[from] + weight)
    {
        distanceFromSource[to] = distanceFromSource[from] + weight;
        parentNode[to] = from;
    }
}

// BELLMAN-FORD + NEGATIVE CYCLE PRINT
bool bellmanFordWithNegativeCycle(int numberOfNodes, int source)
{
    initializeSingleSource(numberOfNodes, source);

    // V-1 relaxations
    for (int i = 1; i <= numberOfNodes - 1; i++)
    {
        for (auto &edge : edgeList)
        {
            relax(edge.from, edge.to, edge.weight);
        }
    }

    int cycleNode = -1;

    // Extra relaxation to detect cycle
    for (auto &edge : edgeList)
    {
        if (distanceFromSource[edge.from] != INF &&
            distanceFromSource[edge.to] >
                distanceFromSource[edge.from] + edge.weight)
        {

            parentNode[edge.to] = edge.from;
            cycleNode = edge.to;
            break;
        }
    }

    if (cycleNode == -1)
        return true;

    // Move inside the cycle
    for (int i = 0; i < numberOfNodes; i++)
    {
        cycleNode = parentNode[cycleNode];
    }

    // Extract cycle
    vector<int> cycle;
    int current = cycleNode;
    do
    {
        cycle.push_back(current);
        current = parentNode[current];
    } while (current != cycleNode);

    cycle.push_back(cycleNode);
    reverse(cycle.begin(), cycle.end());

    cout << "Negative weight cycle nodes: ";
    for (int node : cycle)
        cout << node << " ";
    cout << "\n";

    return false;
}

int main()
{
    int numberOfNodes = 5;
    int sourceNode = 0;

    edgeList = {
        {0, 1, 6},
        {0, 2, 7},
        {1, 2, 8},
        {1, 3, 5},
        {1, 4, -4},
        {2, 3, -3},
        {2, 4, 9},
        {3, 1, -2},
        {4, 0, 2},
        {4, 3, 7}};

    bellmanFordWithNegativeCycle(numberOfNodes, sourceNode);
    return 0;
}
