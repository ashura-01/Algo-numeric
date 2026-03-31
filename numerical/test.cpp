#include <iostream>
#include <vector>
using namespace std;

double newtonDividedDifference(vector<double> x, vector<double> y, double xp) {
    int n = x.size();
    vector<vector<double>> table(n, vector<double>(n));

    // first column = y values
    for(int i=0;i<n;i++)
        table[i][0] = y[i];

    // build divided difference table
    for(int i=1;i<n;i++){
        for(int j=0;j<n-i;j++){
            table[j][i] = (table[j+1][i-1] - table[j][i-1]) / (x[j+i] - x[j]);
        }
    }

    // apply Newton formula
    double yp = table[0][0];

    for(int i=1;i<n;i++){
        double product = 1;
        for(int j=0;j<i;j++)
            product *= (xp - x[j]);

        yp += product * table[0][i];
    }

    return yp;
}

int main() {
    vector<double> x = {1,2,3,4};
    vector<double> y = {1,4,9,16};

    double xp = 2.5;

    double yp = newtonDividedDifference(x, y, xp);

    cout << "Interpolated value: " << yp << endl;
}