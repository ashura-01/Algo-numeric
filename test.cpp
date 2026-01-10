#include <bits/stdc++.h>
using namespace std;

double f(double x)
{
    return x * x - x - 2;
}
double g(double x)
{
    return 2 - x * x;
}

double fixedPoint()
{
    double x0 = 0, x1;
    double error = 0.00001;
    int maxIteration = 100;

    do
    {
        x1 = g(x0);
        if (maxIteration-- <= 0)
        {
            cout << "not convergent!..." << endl;
            return -1;
        }

        cout << "Approx Root is--------> " << x1 << endl;
        x0 = x1;
    } while (fabs(f(x1)) > error);
    cout << "Root is: " << x1 << endl;
    return x1;
}

int32_t main()
{
    fixedPoint();
    return 0;
}