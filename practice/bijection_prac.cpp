#include <bits/stdc++.h>
using namespace std;

double f(double x)
{
    return x * x - 4 * x - 10;
}

void absoluteErrorBisection(double a, double b)
{
    double root = (a + b) / 2.0, prevroot;
    // double root = a - ((b - a) * f(a)) / (f(b) - f(a));
    do
    {
        prevroot = root;
        root = (a + b) / 2.0;

        cout << "now is ---> " << root << endl;

        if (f(root) == 0)
            break;
        else if (f(a) * f(root) < 0)
            b = root;
        else
            a = root;

    } while (fabs(root - prevroot) >= 1e-6);

    cout << "the final root is " << root << endl;
}

double rootBound(double a_n, double a_n1, double a_n2)
{
    return sqrt((a_n1 / a_n) * (a_n1 / a_n) - 2 * (a_n2 / a_n));
}

bool intervals(double start, double end, double step, double &a, double &b)
{
    a = start;
    b = a + step;
    while (b <= end)
    {
        if (f(a) * f(b) < 0)
            return true;
        a = b;
        b += step;
    }
    return false;
}

int main()
{
    double a_n = 1, a_n1 = -4, a_n2 = -10;
    double range = rootBound(a_n, a_n1, a_n2);
    cout << "All roots lie in [-" << range << ", " << range << "]" << endl;

    double a, b;
    double step = 0.1;

    if (intervals(-range, range, step, a, b))
    {
        cout << "valid interval here!" << endl;
        absoluteErrorBisection(a, b);
    }
    else
    {
        cout << "there is no valid interval" << endl;
    }
}
