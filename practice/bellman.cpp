#include <bits/stdc++.h>
using namespace std;

struct Edge
{
    int from;
    int to;
    int weight;
};

const int INF = 1e9;

vector<Edge> edgeList;
vector<int> distanceFromSource;
vector<int> parentNode;

void initializeSingleSource(int numberOfNodes, int source)
{
    distanceFromSource.assign(numberOfNodes, INF);
    parentNode.assign(numberOfNodes, -1);
    distanceFromSource[source] = 0;
}

void relax(int from, int to, int weight)
{
    if (distanceFromSource[from] != INF &&
        distanceFromSource[to] > distanceFromSource[from] + weight)
    {
        distanceFromSource[to]=distanceFromSource[from]+weight;
        parentNode[to]=from;
    }
}

void printingPath(int node)