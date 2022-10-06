#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define vvi vector<vector<int>>

using namespace std;

int n;
ll b;

vvi operator * (vvi &a, vvi &b) {
    vvi ret(n, vector<int>(n, 0));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                ret[i][j] += a[i][k] * b[k][j];
            }
            ret[i][j] %= 1000;
        }
    }

    return ret;
}


vvi matmul(vvi &mat, ll exp) {
    vvi ret(n, vector<int>(n, 0));
    
    if (exp == 1LL) return mat;

    if (exp % 2LL) {
        auto temp = matmul(mat, exp - 1);
        return temp * mat;
    } else {
        auto temp = matmul(mat, exp / 2LL);
        return temp * temp;
    }
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    // basic inputs
    cin >> n >> b;    
    vvi mat(n, vector<int>(n));

    // get matrix
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cin >> mat[i][j];

    // matrix multiplication
    vvi result = matmul(mat, b);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cout << result[i][j] % 1000 << " \n"[j == n - 1];

    
    return 0;
}