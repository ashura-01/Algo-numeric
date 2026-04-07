#include<bits/stdc++.h>
using namespace std;

struct item{
    int id;
    double value, weight;
};

bool cmp(item a, item b)
{
    return (a.value/a.weight) > (b.value/b.weight);
}

double fracknap(vector<item> &arr, double capacity)
{
    sort(arr.begin(), arr.end(), cmp);

    double totalValue = 0.0;

    cout<<"items takenL "<<endl;

    for(auto &item : arr)
    {
        if (capacity>= item.weight)
        {
            cout<<"item--> "<<item.id<<" -< 100%"<<endl;
            totalValue+= item.value;
            capacity-= item.weight;
        }else{

            double fraction =  capacity/item.weight;
            cout<<"item--> "<<item.id<<"-< "<<fraction*100<<"%"<<endl;
            totalValue+= item.value*fraction;
            break;
        }
        
    }

    return totalValue;
}

int main()
{
    vector<item> items = {
        {1, 60, 10},
        {2, 100, 20},
        {3, 120, 30},
        {4, 100, 5}
    };

    double capacity=50;
    double result = fracknap(items, capacity);
    cout<< "max val= "<<result<<endl;
    return 0;
}