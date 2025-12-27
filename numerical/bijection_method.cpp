#include <bits/stdc++.h>
using namespace std;

double f(double x)
{
    return x * x - 4 * x - 10;
}

void absoluteErrorBisection()
{
    double a, b;
label:
    cin >> a >> b;

    if (f(a) * f(b) > 0)
    {
        cout << "wrong interval!" << endl;
        goto label;
    }

    cout << fixed << setprecision(16);

    double root = 0.0, prev_root = 0.0;

    do
    {
        prev_root = root;
        root = (a + b) / 2.0;
        cout << "now is----->" << root << endl;

        if (f(root) == 0)
            break;
        else if (f(a) * f(root) < 0)
            b = root;
        else
            a = root;

    } while (fabs(root - prev_root) >= 1e-6);  // absolute error

    cout << "the final root is: " << root << endl;
}

void relativeErrorBisection()
{
    double a, b;
label:
    cin >> a >> b;

    if (f(a) * f(b) > 0)
    {
        cout << "wrong interval!" << endl;
        goto label;
    }

    cout << fixed << setprecision(16);

    double root = 0.0, prev_root = 0.0;

    do
    {
        prev_root = root;
        root = (a + b) / 2.0;
        cout << "now is----->" << root << endl;

        if (f(root) == 0)
            break;
        else if (f(a) * f(root) < 0)
            b = root;
        else
            a = root;

    } while (fabs(root - prev_root) / fabs(root) >= 1e-6);  // relative error

    cout << "the final root is: " << root << endl;
}

int main()
{
    relativeErrorBisection();   // or absoluteErrorBisection();
    return 0;
}
