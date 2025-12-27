#include <bits/stdc++.h>
using namespace std;

double f(double x)
{
    return x * x - 4 * x - 10;
}

int main()
{
    double a = -2, b = -1;
label:
    double root;
    cin >> a >> b;

    if (f(a) * f(b) > 0)
    {
        cout << "wrong interval!";
        goto label;
    }
    cout << fixed << setprecision(16);
    do
    {
        root = (a + b) / 2;
        cout << "now is----->" << root << endl;
        if (f(root) == 0)
            break;
        else if (f(a) * f(root) < 0)
            b = root;
        else
            a = root;
    } while (fabs((b - a) / b) >= 0.000001);
    cout << "the final root is: " << root << endl;
    return 0;
}
