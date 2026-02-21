#include<bits/stdc++.h>
using namespace std;

double f(double x)
{
    return x*x*x-x-2;
}

double bisection(double x1, double x2, double eps)
{
    double previousRoot = x1;
    double error =1e9;
    double root;

    while(error >= eps)
    {
        root=(x1+x2)/2.0;
        error = fabs(root-previousRoot);

        if(f(root)==0.0)
            break;
        else if(f(root)*f(x1)<0)
            x2=root;
        else    
            x1=root;
        
        previousRoot=root;
    }

    return root;
} 


void findroots(double a, double b, double ds, double eps)
{
    double x1=a;
    double x2=x1+ds;

    while(x2<=b)
    {
        if(f(x1)*f(x2)<0)
        {
            double root = bisection(x1, x2, eps);
            cout<<"root found: "<<root<<endl;
        }
        x1=x2;
        x2=x1+ds;
    }
}
int main()
{
    double a, b, ds, eps;

    cin >> a >> b;
    cin >> ds;
    cin >> eps;

    findroots(a, b, ds, eps);

    return 0;
}