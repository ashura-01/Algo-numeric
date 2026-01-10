#include <bits/stdc++.h>
using namespace std;

int counts = 1;
double f(double x)
{
    return x * x - 4 * x - 10;
}

double secant_method()
{
    cout << fixed << setprecision(17);

    double x0, x1, x2;
    double error, relativeError;
    // dummy input
    x0 = 4;
    x1 = 2;
    error = 0.0000001;
    double root = 0.0;

    do
    {
        if (f(x1) - f(x0) == 0.0)
        {
            cout << "error in input..." << endl;
            return -1.0;
        }
        x2 = x1 -
             (f(x1) * (x1 - x0)) /
                 (f(x1) - f(x0));
                 
        root = x2;
        cout << "the approx root is---------> " << root << endl;

        relativeError = fabs((x1 - x2) / x2);
        x0 = x1;
        x1 = x2;

    } while (relativeError > error);
    cout << "the root is: " << root << endl;

    return root;
}

int32_t main()
{
    secant_method();
    return 0;
}