#include <bits/stdc++.h>
using namespace std;


int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ofstream outFile("data.txt"); 
    if (!outFile)
    {
        cerr << "Cannot open file for writing!\n";
        return 1;
    } 

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(1, 1000000); 
    for (int i = 0; i < 100000; i++)
    {
        outFile << dis(gen) << " ";
    }
    outFile.close();
    
    return 0;
}