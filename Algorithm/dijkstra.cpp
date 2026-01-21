#include <bits/stdc++.h>
using namespace std;

struct Edge
{
    int from;
    int to;
    int weight;
};

const int INF = 1e9;

vector<vector<Edge>> adjacencyList;
vector<int> distanceFromSource;
vector<int> parentNode;

// INITIALIZE_SINGLE_SOURCE
void initializeSingleSource(int numberOfNodes, int source)
{
    distanceFromSource.assign(numberOfNodes, INF);
    parentNode.assign(numberOfNodes, -1);
    distanceFromSource[source] = 0;
}

// RELAX
void relax(int from, int to, int weight,
           priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> &minHeap)
{
    if (distanceFromSource[to] > distanceFromSource[from] + weight)
    {
        distanceFromSource[to] = distanceFromSource[from] + weight;
        parentNode[to] = from;
        minHeap.push({distanceFromSource[to], to});
    }
}

// PRINT PATH
void printPath(int node)
{
    if (node == -1)
        return;
    printPath(parentNode[node]);
    cout << node << " ";
}

// DIJKSTRA
void dijkstra(int numberOfNodes, int source)
{
    initializeSingleSource(numberOfNodes, source);

    priority_queue<pair<int, int>, 
    vector<pair<int, int>>, greater<>> minHeap;

    minHeap.push({0, source});

    while (!minHeap.empty())
    {
        int currentDistance = minHeap.top().first;
        int currentNode = minHeap.top().second;
        minHeap.pop();

        if (currentDistance > distanceFromSource[currentNode])
            continue;

        for (auto &edge : adjacencyList[currentNode])
        {
            relax(currentNode, edge.to, edge.weight, minHeap);
        }
    }
}

int main()
{
    // -------- DUMMY INPUT (replace later) --------
    int numberOfNodes = 5;
    int sourceNode = 0;

    adjacencyList.assign(numberOfNodes, {});
    adjacencyList[0].push_back({0, 1, 4}); 
    adjacencyList[0].push_back({0, 2, 1}); 
    adjacencyList[2].push_back({2, 1, 2}); 
    adjacencyList[1].push_back({1, 3, 1}); 
    adjacencyList[2].push_back({2, 3, 5}); 
    adjacencyList[3].push_back({3, 4, 3}); 

   

    dijkstra(numberOfNodes, sourceNode);

    for (int node = 0; node < numberOfNodes; node++)
    {
        cout << "Node " << node << ": ";
        if (distanceFromSource[node] == INF)
        {
            cout << "INF\n";
        }
        else
        {
            cout << distanceFromSource[node] << " | Path: ";
            printPath(node);
            cout << "\n";
        }
    }

    return 0;
}
