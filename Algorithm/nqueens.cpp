#include <bits/stdc++.h>
using namespace std;

int n;
vector<int> arr;

// Uncomment to restrict certain rows or columns
// set<int> blockedRows;  // rows where queens cannot be placed
// set<int> blockedCols;  // columns where queens cannot be placed

bool Place(int k, int i) {
    // Uncomment to block specific rows
    // if (blockedRows.count(k)) return false;

    // Uncomment to block specific columns
    // if (blockedCols.count(i)) return false;

    for (int j = 1; j <= k - 1; j++) {

        // ❌ Same column
        if (arr[j] == i)
            return false;

        // ❌ LEFT diagonal (\)
        // if ((arr[j] - i) == (j - k))
        //     return false;

        // ❌ RIGHT diagonal (/)
        // if ((arr[j] - i) == (k - j))
        //     return false;

        // ❌ BOTH diagonals (normal N-Queens)
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

    // Example of using restrictions (commented out)
    // blockedRows = {2, 4};   // forbid queens in rows 2 and 4
    // blockedCols = {1, 3};   // forbid queens in columns 1 and 3

    NQueens(1);
    return 0;
}