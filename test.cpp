#include <bits/stdc++.h>
using namespace std;

int counts = 1;

// Polynomial evaluation (Horner's method)
double f(vector<double> &arr, int n, double x)
{
    double result = 0;
    for (int i = n; i >= 0; i--)
        result = result * x + arr[i];
    return result;
}

// Polynomial derivative evaluation
double df(vector<double> &arr, int n, double x)
{
    double result = 0;
    for (int i = n; i > 0; i--)
        result = result * x + i * arr[i];
    return result;
}

// Newton-Raphson using your exact style
double newton_raphson(vector<double> &arr, int n, double initialvalue, double tol = 1e-12)
{
    cout << fixed << setprecision(17);
    double nextvalue, functionAtNext;

    do
    {
        if (df(arr, n, initialvalue) == 0.0) // fixed line
        {
            cout << "error....." << endl;
            return -1.0;
        }

        nextvalue = initialvalue - f(arr, n, initialvalue) / df(arr, n, initialvalue);
        initialvalue = nextvalue;
        functionAtNext = f(arr, n, initialvalue);

        cout << counts << ". the approx root value is----------->" << nextvalue << endl;
        counts++;

    } while (fabs(functionAtNext) > tol);

    cout << "the root value is: " << nextvalue << endl;
    return nextvalue;
}

// Synthetic Division
void syntheticDivision(vector<double> &a, int &n, double root) {
    vector<double> b(n + 1);

    b[n] = a[n];
    for (int i = n - 1; i >= 0; i--) {
        b[i] = a[i] + b[i + 1] * root;
    }

    for (int i = 0; i < n; i++) {
        a[i] = b[i + 1];
    }

    n--;
}

int32_t main()
{
    // Example polynomial: x^3 - 6x^2 + 11x - 6
    vector<double> a = {-6, 11, -6, 1}; // coefficients a0, a1, a2, a3
    int n = 3;                           // degree
    double initial_guess = 1.5;

    while (n > 1)
    {
        double root = newton_raphson(a, n, initial_guess);
        syntheticDivision(a, n, root);
        initial_guess = root; // reuse for next root
    }

    // Last root (linear term)
    double lastRoot = -a[0] / a[1];
    cout << "Final root: " << lastRoot << endl;

    return 0;
}