#include <bits/stdc++.h>
using namespace std;

int counts =1;

double f(double x)
{
    return x * x - 3 * x + 2;
}
double df(double x)
{
    return 2 * x - 3;
}
double newton_rapson()
{   
    cout<<fixed<<setprecision(17);
    double initialvalue, error;
    double nextvalue, functionAtNext;
    
    cout << "Enter the intial value";
    initialvalue = 0;
    cout << "enter torable error: ";
    error = 0.0000000000001;
    cout<<endl;

    do
    {
        if (df(initialvalue)==0.0)
        {
            cout<<"error....."<<endl;
            return -1.0;
        }

        nextvalue = initialvalue-f(initialvalue)/df(initialvalue);
        initialvalue= nextvalue;
        functionAtNext = f(initialvalue);

        cout<<counts<<". the approx root value is----------->"<<nextvalue<<endl;
        counts++;
        
    } while (functionAtNext > error);
    cout<<"the root value is: "<<nextvalue<<endl;

    return nextvalue;
}

int32_t main()
{
    newton_rapson();
    return 0;
}