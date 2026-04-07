#include <bits/stdc++.h>
using namespace std;

int n;
vector<int> arr;

bool place(int k, int i)
{
    for (int j = 1; j <= k; j++)
    {
        if (arr[j] == i)
            return false;

        if (abs(arr[j] - i) == abs(j - k))
            return false;
    }

    return true;
}

void nqueen(int k)
{
    for (int i = 1; i < n; i++)
    {
        if (place(k, i))
        {
            arr[k] = i;

            if (k == n)
            {
                for (int j = 1; j <= n; j++)
                {
                    cout << arr[j] << " ";
                }

                cout << endl;
            }
            else
            {
                nqueen(k + 1);
            }
        }
    }
}

int main()
{

    return 0;
}