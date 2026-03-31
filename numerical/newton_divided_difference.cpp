#include <bits/stdc++.h>
using namespace std;

void newtonDividedDifference(vector<double> x, vector<double> y, double xp)
{
    int n = x.size();
    vector<vector<double>> table(n, vector<double>(n));

    for (size_t i = 0; i < n; i++)
    {
        table[i][0]=y[i];
    }
    
    for (int i = 0; i < n; i++)
    {
        for (int  j = 0; j < n-i; j++)
        {
            table[i][j]=(table[j+1][i-1]- table[j][i-1])/ (x[j+i]-x[j]);
        }
        
    }
    
}

int main()
{
    vector<double> x;
    vector<double> y;
    double xp;
    newtonDividedDifference(x,y,xp);
    return 0;
}