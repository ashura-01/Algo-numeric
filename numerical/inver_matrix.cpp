#include <iostream>
#include <vector>
using namespace std;

// Function to compute inverse using Gauss-Jordan
vector<vector<double>> inverseMatrix(vector<vector<double>> a){
    int n = a.size();
    vector<vector<double>> inv(n, vector<double>(n, 0));

    for(int i=0; i<n; i++)
        inv[i][i] = 1;

    for(int i=0; i<n; i++){
        double pivot = a[i][i];
        for(int j=0; j<n; j++){
            a[i][j] /= pivot;
            inv[i][j] /= pivot;
        }
        for(int k=0; k<n; k++){
            if(k != i){
                double factor = a[k][i];
                for(int j=0; j<n; j++){
                    a[k][j] -= factor * a[i][j];
                    inv[k][j] -= factor * inv[i][j];
                }
            }
        }
    }

    return inv;
}

// Multiply matrix by vector
vector<double> multiplyMatrixVector(vector<vector<double>> mat, vector<double> vec){
    int n = mat.size();
    vector<double> res(n,0);
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            res[i] += mat[i][j]*vec[j];
    return res;
}

int main(){
    // Coefficient matrix
    vector<vector<double>> A = {
        {2,1,-1},
        {-3,-1,2},
        {-2,1,2}
    };

    // Constant vector (right-hand side)
    vector<double> B = {8,-11,-3};

    // Compute inverse
    vector<vector<double>> invA = inverseMatrix(A);

    // Multiply inverse(A) * B to get solution
    vector<double> X = multiplyMatrixVector(invA, B);

    cout << "Solution: ";
    for(double v:X) cout << v << " ";
}