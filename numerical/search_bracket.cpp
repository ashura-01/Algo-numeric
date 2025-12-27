#include <bits/stdc++.h>
using namespace std;

// Example: quadratic function f(x) = x^2 - 4x - 10
double f(double x)
{
    return x*x - 4*x - 10;
}

// Compute root bound using formula |x*| <= sqrt((a_{n-1}/a_n)^2 - 2*(a_{n-2}/a_n))
double rootBound(double a_n, double a_n1, double a_n2)
{
    return sqrt((a_n1/a_n)*(a_n1/a_n) - 2*(a_n2/a_n));
}

// Search for a bracket [a, b] where f(a)*f(b) < 0 inside [-R, R]
bool searchBracket(double start, double end, double step, double &a, double &b)
{
    a = start;
    b = a + step;

    while (b <= end)
    {
        if (f(a) * f(b) < 0)
            return true;  // valid bracket found
        a = b;
        b += step;
    }
    return false;  // no bracket found
}

int main()
{
    // Polynomial coefficients for x^2 - 4x - 10
    double a_n = 1;     // coefficient of x^2
    double a_n1 = -4;   // coefficient of x^1
    double a_n2 = -10;  // coefficient of x^0

    // Step 1: Compute root bound
    double R = rootBound(a_n, a_n1, a_n2);
    cout << "All roots lie in [-" << R << ", " << R << "]" << endl;

    // Step 2: Search for valid bracket
    double a, b;
    double step = 0.1;  // increment for scanning
    if (searchBracket(-R, R, step, a, b))
        cout << "Valid bracket found: [" << a << ", " << b << "]" << endl;
    else
        cout << "No valid bracket found in the range." << endl;

    return 0;
}
