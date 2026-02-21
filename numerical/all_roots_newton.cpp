#include <bits/stdc++.h>
using namespace std;

double df(vector<double> &arr, int n, double x)
{
    double result = 0;
    for (int i = n; i > 0; i--)
        result = result * x + i * arr[i];
    return result;
}

double f(vector<double> &arr, int n, double x)
{
    double result = 0;
    for (int i = n; i >= 0; i--)
        result = result * x + arr[i];
    return result;
}

double newtonRaphson(vector<double> &arr, int n, double initialvalue, double tol = 1e-12)
{
    double nextvalue, functionAtNext;
    int iter = 1;

    do
    {
        double deriv = df(arr, n, initialvalue);
        if (deriv == 0.0)
        {
            cout << "Derivative zero, stopping..." << endl;
            return -1.0;
        }

        nextvalue = initialvalue - f(arr, n, initialvalue) / deriv;
        initialvalue = nextvalue;
        functionAtNext = f(arr, n, initialvalue);

        // cout << iter << ". Approx root: " << nextvalue << " | f(x) = " << functionAtNext << endl;
        iter++;

    } while (fabs(functionAtNext) > tol);

    return nextvalue;
}

void syntheticdivision(vector<double> &arr, int &n, double root)
{
    vector<double> brr(n+1);
    brr[n] = arr[n];

    for (int i = n-1; i >= 0; i--)
        brr[i] = arr[i] + brr[i+1] * root;

    for (int i = 0; i < n; i++)
        arr[i] = brr[i+1];

    n--;
}

int main()
{
    vector<double> arr = {-6, 11, -6, 1}; // x^3 - 6x^2 + 11x - 6
    int n = 3;
    double initialguess = 1.5;

    while (n > 1)
    {
        double root = newtonRaphson(arr, n, initialguess);
        cout << "Found root: " << root << endl;
        syntheticdivision(arr, n, root);
        initialguess = root; // reuse
    }

    double finalroot = -arr[0] / arr[1];
    cout << "Final root: " << finalroot << endl;

    return 0;
}