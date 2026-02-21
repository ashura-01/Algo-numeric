#include <bits/stdc++.h>
using namespace std;

// -------- Function Definition --------
double f(double x)
{
    // Example equation: x^3 - x - 2 = 0
    return x * x * x - x - 2;
}

// -------- Bisection Method --------
double bisection(double x1, double x2, double eps)
{
    double prev_root = x1;
    double error = 1e9;
    double x0;

    while (error >= eps)
    {
        x0 = (x1 + x2) / 2.0;
        error = fabs(x0 - prev_root);

        if (f(x0) == 0.0)
            break;

        else if (f(x0) * f(x1) < 0)
            x2 = x0;
        else
            x1 = x0;

        prev_root = x0;
    }

    return x0;
}

// -------- Interval Scanning --------
void findRoots(double a, double b, double ds, double eps)
{
    double x1 = a;
    double x2 = x1 + ds;

    while (x2 <= b)
    {

        if (f(x1) * f(x2) < 0)
        {
            double root = bisection(x1, x2, eps);
            cout << "Root found: " << root << endl;
        }

        x1 = x2;
        x2 = x1 + ds;
    }
}

// -------- Main Function --------
int main()
{
    double a, b, ds, eps;

    cout << "Enter a, b: ";
    cin >> a >> b;

    cout << "Enter step size ds: ";
    cin >> ds;

    cout << "Enter tolerable error epsilon: ";
    cin >> eps;

    findRoots(a, b, ds, eps);

    return 0;
}