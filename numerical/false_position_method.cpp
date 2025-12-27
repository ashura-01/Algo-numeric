// Basic implementation of the Bisection Method to find a root of f(x) = x^2 - 4x - 10 for the interval [-2, -1]
// Stopping criteria -> relative error |b - a| / |b| becomes less than or equal to 0.000001
#include <bits/stdc++.h>
using namespace std;

double f(double x)
{
    return x * x - 4 * x - 10;
}

int main()
{
    double a = -2, b = -1;
    double root;

    if (f(a) * f(b) > 0)
    {
        cout << "wrong interval" << endl;
        return -1;
    }
    do
    {
        root = a - ((b - a) * f(a)) / (f(b) - f(a));
        if (f(root) == 0)
            break;
        else if (f(root) * f(a) < 0)
            b = root;
        else
            a = root;

    } while (fabs((b - a) / b) > 0.000001);
    cout << "the final root is: " << root << endl;

    return 0;
}