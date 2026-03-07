#include <bits/stdc++.h>
using namespace std;

vector<double> jacobi(vector<vector<double>> arr, vector<double> brr, int iter)
{
    int n = arr.size();
    vector<double> x(n, 0), x_new(n);

    while (iter--)
    {
        for (int i = 0; i < n; i++)
        {
            double sum = 0;
            for (int j = 0; j < n; j++)
            {
                if (j != i)
                    sum += arr[i][j] * x[j];
                x_new[i] = (brr[i] - sum) / arr[i][i];
            }
        }
        x = x_new;
    }
    return x;
}

vector<double> gaussSeidal(vector<vector<double>> arr, vector<double> brr, int iter)
{
    int n = arr.size();
    vector<double> x(n, 0);

    while (iter--)
    {
        for (int i = 0; i < n; i++)
        {
            double sum = 0;

            for (int j = 0; j < n; j++)
            {
                if (j != i)
                    sum += arr[i][j] * x[j];

                x[i] = (brr[i] - sum) / arr[i][i];
            }
        }
    }

    return x;
}

int main()
{
    vector<vector<double>> arr = {
        {10, -1, 2},
        {-1, 11, -1},
        {2, -1, 10}};

    vector<double> brr = {6, 25, -11};
    vector<double> ans = gaussSeidal(arr, brr, 10);
    for (auto elem : ans)
        cout << elem << " ";
    return 0;
}