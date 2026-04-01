#include <bits/stdc++.h>
using namespace std;

int n;
vector<int> arr;

bool Place(int k, int i) {
    for (int j = 1; j <= k - 1; j++) {

        // ❌ Same column
        if (arr[j] == i)
            return false;

        // ❌ LEFT diagonal (\)
        // Uncomment this to block only LEFT diagonal
        // if ((arr[j] - i) == (j - k))
        //     return false;

        // ❌ RIGHT diagonal (/)
        // Uncomment this to block only RIGHT diagonal
        // if ((arr[j] - i) == (k - j))
        //     return false;

        // ❌ BOTH diagonals (normal N-Queens)
        // Keep this for standard problem
        if (abs(arr[j] - i) == abs(j - k))
            return false;
    }
    return true;
}

void NQueens(int k) {
    for (int i = 1; i <= n; i++) {
        if (Place(k, i)) {
            arr[k] = i;

            if (k == n) {
                for (int j = 1; j <= n; j++)
                    cout << arr[j] << " ";
                cout << endl;
            } else {
                NQueens(k + 1);
            }
        }
    }
}

int main() {
    cin >> n;
    arr.resize(n + 1); // 1-based indexing
    NQueens(1);
    return 0;
}