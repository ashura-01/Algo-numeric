#include <bits/stdc++.h>
using namespace std;

double lagRangeInterPolation(vector<double> x, vector<double> y, double xp)
{
    int n = x.size();
    double yp = 0;

    for (int i = 0; i < n; i++)
    {
        double p = 1;
        for (int j = 0; j < n; j++)
        {
            if (i != j)
            {
                p = p * (xp - x[j]) / (x[i] - x[j]);
            }
        }

        yp = yp + p * y[i];
    }
    return yp;
}

int main()
{
    vector<double> x={1,2,3};
    vector<double> y={1,4,9};
    double xp=2.5;
    double yp=lagRangeInterPolation(x, y, xp);

    cout<<"the value is: "<<yp<<endl;
    return 0;
}