#include <bits/stdc++.h>
using namespace std;

vector<double> gaussElimination(vector<vector<double>> arr)
{
    int n = arr.size();
    vector<double> x(n);

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            double ratio = arr[j][i] / arr[i][i];

            for (int k = 0; k <= n; k++)
                arr[j][k] -= ratio * arr[i][k];
        }
    }

    x[n - 1] = arr[n - 1][n] / arr[n - 1][n - 1];

    for (int i = n - 2; i >= 0; i--)
    {
        double sum = 0;
        for (int j = i + 1; j < n; j++)
            sum += arr[i][j] * x[j];
        x[i] = (arr[i][n] - sum) / arr[i][i];
    }

    return x;
}

vector<double> gaussJordan(vector<vector<double>> arr)
{
    int n = arr.size();

    for (int i = 0; i < n; i++)
    {
        double pivot = arr[i][i];

        for (int j = 0; j <= n; j++)
            arr[i][j] /= pivot;

        for (int k = 0; k < n; k++)
        {
            if (k != i)
            {
                double factor = arr[k][i];
                for (int j = 0; j <= n; j++)
                    arr[k][j] -= factor * arr[i][j];
            }
        }
    }

    vector<double> x(n);
    for (int i = 0; i < n; i++)
        x[i] = arr[i][n];

    return x;
}

int main()
{
    vector<vector<double>> arr = {{2, 1, -1, 8},
                                  {-3, -1, 2, -11},
                                  {-2, 1, 2, -3}};
    vector<double> answer = gaussJordan(arr);
    for (auto elem : answer)
        cout << elem << " ";
    return 0;
}