#include <bits/stdc++.h>
using namespace std;

// Function to print optimal parenthesis
void printParens(vector<vector<int>> &split, int i, int j)
{
    if (i == j)
    {
        cout << "A" << i;
        return;
    }
    cout << "(";
    printParens(split, i, split[i][j]);
    printParens(split, split[i][j] + 1, j);
    cout << ")";
}

// Matrix Chain Multiplication DP
vector<vector<int>> matrixChain(vector<int> &dim, int &optimal)
{
    int n = dim.size() - 1;
    vector<vector<int>> cost(n + 1, vector<int>(n + 1, 0));
    vector<vector<int>> split(n + 1, vector<int>(n + 1, 0));

    for (int len = 2; len <= n; len++)
    { // chain length
        for (int i = 1; i <= n - len + 1; i++)
        {
            int j = i + len - 1;
            cost[i][j] = INT_MAX;
            for (int k = i; k < j; k++)
            {
                int cur = cost[i][k] + cost[k + 1][j] + dim[i - 1] * dim[k] * dim[j];
                if (cur < cost[i][j])
                {
                    cost[i][j] = cur;
                    split[i][j] = k;
                }
            }
        }
    }

    optimal = cost[1][n];
    cout << "Minimum multiplications: " << cost[1][n] << "\n";
    return split;
}

int main()
{
    vector<int> dim = {30, 35, 15, 5, 10, 20, 25}; // Example: 6 matrices
    int optimal;
    vector<vector<int>> split = matrixChain(dim, optimal);

    cout << "Optimal parenthesization: ";
    printParens(split, 1, dim.size() - 1);
    cout << endl;

    return 0;
}