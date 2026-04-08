
#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9;

vector<vector<int>>mat;


void floydWarshall(int n){

    for(int k=0;k<n;k++){
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(mat[i][k]!=INF&&mat[k][j]!=INF){
                    if(mat[i][k]+mat[k][j]<mat[i][j]){
                        mat[i][j]=mat[i][k]+mat[k][j];
                    }
                }
            }
        }
    }
}
void printMatrix(int n){

    cout<<"all-pairs shortest path matrix:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (mat[i][j] == INF) cout << setw(5) << "INF";
            else cout << setw(5) << mat[i][j];
        }
        cout << "\n";
    }
}

int main(){
    int N = 4;


    mat.assign(N, vector<int>(N, INF));
    for(int i = 0; i < N; i++) mat[i][i] = 0;


    mat[0][1] = 5;
    mat[0][3] = 10;
    mat[1][2] = 3;
    mat[2][3] = 1;
    mat[3][0] = -2;

    cout << "--- Floyd-Warshall Algorithm ---\n";
    floydWarshall(N);

    printMatrix(N);


}
