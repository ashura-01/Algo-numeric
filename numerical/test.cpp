#include <iostream>
#include <vector>
using namespace std;

vector<double> gaussElimination(vector<vector<double>> a)
{
    int n = a.size();
    vector<double> x(n);

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            double ratio = a[j][i] / a[i][i];
            for (int k = 0; k <= n; k++)
                a[j][k] -= ratio * a[i][k];
        }
    }

    x[n - 1] = a[n - 1][n] / a[n - 1][n - 1];

    for (int i = n - 2; i >= 0; i--)
    {
        double sum = 0;
        for (int j = i + 1; j < n; j++)
            sum += a[i][j] * x[j];

        x[i] = (a[i][n] - sum) / a[i][i];
    }

    return x;
}

vector<double> gaussJordan(vector<vector<double>> a)
{
    int n = a.size();

    for (int i = 0; i < n; i++)
    {
        double pivot = a[i][i];

        for (int j = 0; j <= n; j++)
            a[i][j] /= pivot;

        for (int k = 0; k < n; k++)
        {
            if (k != i)
            {
                double factor = a[k][i];
                for (int j = 0; j <= n; j++)
                    a[k][j] -= factor * a[i][j];
            }
        }
    }

    vector<double> x(n);
    for (int i = 0; i < n; i++)
        x[i] = a[i][n];

    return x;
}

vector<double> jacobi(vector<vector<double>> a, vector<double> b, int iter)
{
    int n = a.size();
    vector<double> x(n, 0), x_new(n);

    for (int k = 0; k < iter; k++)
    {
        for (int i = 0; i < n; i++)
        {
            double sum = 0;
            for (int j = 0; j < n; j++)
                if (j != i)
                    sum += a[i][j] * x[j];

            x_new[i] = (b[i] - sum) / a[i][i];
        }
        x = x_new;
    }

    return x;
}
vector<double> gaussSeidel(vector<vector<double>> a, vector<double> b, int iter)
{
    int n = a.size();
    vector<double> x(n, 0);

    for (int k = 0; k < iter; k++)
    {
        for (int i = 0; i < n; i++)
        {
            double sum = 0;
            for (int j = 0; j < n; j++)
                if (j != i)
                    sum += a[i][j] * x[j];

            x[i] = (b[i] - sum) / a[i][i];
        }
    }

    return x;
}
int main()
{
    vector<vector<double>> A = {
        {10, -1, 2},
        {-1, 11, -1},
        {2, -1, 10}};

    vector<double> B = {6, 25, -11};

    vector<double> ans = jacobi(A, B, 10);

    for (double v : ans)
        cout << v << " ";

    // vector<vector<double>> arr = {{2, 1, -1, 8},
    //                               {-3, -1, 2, -11},
    //                               {-2, 1, 2, -3}};
    // vector<double> answer = gaussJordan(arr);
    // for (auto elem : answer)
    //     cout << elem << " ";
    // return 0;
}