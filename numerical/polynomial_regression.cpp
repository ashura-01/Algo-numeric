#include <bits/stdc++.h>
using namespace std;

vector<double> polyRegression(vector<double> &x, vector<double> &y, int n, int degree)
{
    int m = degree + 1;
    vector<vector<double>> arr(m, vector<double>(m + 1, 0));

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < m; j++)
        {
            for (int k = 0; k < n; k++)
                arr[i][j] += pow(x[k], i + j);
        }
        for (int k = 0; k < n; k++)
            arr[i][m] += pow(x[k], i) * y[k];
    }

    for (int i = 0; i < m; i++)
    {
        // pivot
        int maxRow = i;
        for (int k = i + 1; k < m; k++)
        {
            if (abs(arr[k][i]) > abs(arr[maxRow][i]))
                maxRow = k;
        }
        swap(arr[i], arr[maxRow]);

        if (abs(arr[i][i]) < 1e-9)
        {
            cout << "Matrix is singular!\n";
            return {};
        }

        for (int j = i + 1; j < m; j++)
        {
            double ratio = arr[j][i] / arr[i][i];
            for (int k = i; k <= m; k++)   
                arr[j][k] -= ratio * arr[i][k];
        }
    }

    vector<double> coeff(m);
    for (int i = m - 1; i >= 0; i--)
    {
        coeff[i] = arr[i][m];
        for (int j = i + 1; j < m; j++)
            coeff[i] -= arr[i][j] * coeff[j];

        coeff[i] /= arr[i][i];
    }

    return coeff;
}

void printingPoly(vector<double> &coeff)
{
    cout << "\nPolynomial:\ny = ";
    for (int i = 0; i < coeff.size(); i++)
    {
        cout << coeff[i];
        if (i > 0) cout << "x^" << i;
        if (i != coeff.size() - 1) cout << " + ";
    }
}

int main()
{
    int n, degree;
    cin >> n;

    vector<double> x(n), y(n);
    for (int i = 0; i < n; i++)
        cin >> x[i] >> y[i];

    cin >> degree;

    vector<double> coeff = polyRegression(x, y, n, degree);
    if (!coeff.empty())
        printingPoly(coeff);
}