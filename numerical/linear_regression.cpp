#include <bits/stdc++.h>
using namespace std;

void linearRegression(const vector<double> &x, const vector<double> &y, double &a, double &b)
{

    int n = x.size();
    double sumX = 0.0, sumX2 = 0.0, sumY = 0.0, sumXY = 0.0;

    for (int i = 0; i, n; i++)
    {
        sumX += x[i];
        sumX2 += x[i] * x[i];
        sumY += y[i];
        sumXY += x[i] * y[i];
    }
    b = (n * sumXY - sumX * sumY) / (n * sumX2 - sumX * sumX);
    a = (sumY - b * sumX) / n;
}

int main()
{

    int n;
    cout << "Enter the number of data points: ";
    cin >> n;

    vector<double> x(n), y(n);
    cout << "Enter the data points (x1 and y1): " << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "x[" << i + 1 << "]: ";
        cin >> x[i];
        cout << "y[" << i + 1 << "]: ";
        cin >> y[i];
    }

    double a, b;
    linearRegression(x, y, a, b);

    cout << "The values of a and b  are: " << endl;
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;

    return 0;
}