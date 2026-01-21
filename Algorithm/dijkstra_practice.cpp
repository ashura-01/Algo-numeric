#include <bits/stdc++.h>
using namespace std;

struct edge
{
    int from;
    int to;
    int weight;
};

const int infinity = 1e9;

vector<vector<edge>> graph;
vector<int> distanceFromSource;
vector<int> parent;

void initialize(int numberOfNodes, int source)
{
    distanceFromSource.assign(numberOfNodes, infinity);
    parent.assign(numberOfNodes, -1);
    distanceFromSource[source] = 0;
}

void relax(
    int from,
    int to,
    int weight,
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> &minheap)
{
    if (distanceFromSource[to] > distanceFromSource[from] + weight)
    {
        distanceFromSource[to] = distanceFromSource[from] + weight;
        parent[to] = from;
        minheap.push({distanceFromSource[to], to});
    }
}

void dijkstra(int numberOfNodes, int source)
{
    initialize(numberOfNodes, source);

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> minheap;
    minheap.push({0, source});

    while (!minheap.empty())
    {
        int currentDistance = minheap.top().first;
        int currentNode = minheap.top().second;
        minheap.pop();

        if (currentDistance > distanceFromSource[currentNode])
        {
            continue;
        }
        for (auto &edge : graph[currentNode])
        {
            relax(currentNode, edge.to, edge.weight, minheap);
        }
    }
}

void printPath(int node)
{
    if (node == -1)
    {
        return;
    }
    printPath(parent[node]);
    cout << node << " ";
}

void inputGraph(int numberOfNodes, int numberOfEdges)
{
    graph.assign(numberOfNodes, {});

    cout << "Enter edges in format: from to weight\n";
    for (int i = 0; i < numberOfEdges; i++)
    {
        int from, to, weight;
        cin >> from >> to >> weight;
        graph[from].push_back({from, to, weight});
    }
}

int main()
{
    int numberOfNodes = 5;
    int numberOfEdges = 5;

    cout << "enter the number of nodes: ";
    cin >> numberOfNodes;
    cout << "enter the number of edges: ";
    cin >> numberOfEdges;

    inputGraph(numberOfNodes, numberOfEdges);
    
    int sourceNode = 0;

    dijkstra(numberOfNodes, sourceNode);

    for (int node = 0; node < numberOfNodes; node++)
    {
        cout << "node " << node << ": ";
        if (distanceFromSource[node] == infinity)
        {
            cout << "infinity" << endl;
        }
        else
        {
            cout << distanceFromSource[node] << "|path: ";
            printPath(node);
            cout << endl;
        }
    }

    return 0;
}