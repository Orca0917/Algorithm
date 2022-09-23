#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define MOD 1'000'003

using namespace std;

int n, s, e, t;

struct Matrix {
    vector<vector<ll>> v;
    int sz = 0;

    Matrix(int n) {
        sz = n;
        v.resize(n, vector<ll>(n, 0));
    }

    Matrix operator * (const Matrix &A) {
        Matrix B(sz);
        for (int i = 0; i < sz; ++i) {
            for (int j = 0; j < sz; ++j) {
                for (int k = 0; k < sz; ++k) {
                    B.v[i][j] += v[i][k] * A.v[k][j];
                    B.v[i][j] %= MOD;
                }
            }
        }
        return B;   
    }

};


Matrix matmul(Matrix A, int k) {
    if (k == 1) return A;

    Matrix ret = matmul(A, k / 2);
    ret = ret * ret;

    if (k & 1) ret = ret * A;
    return ret;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n >> s >> e >> t;
    --s; --e;

    Matrix matrix(n * 5);

    for (int i = 0; i < n; ++i) {
        for (int j = 1; j < 5; ++j) {
            matrix.v[i * 5 + j][i * 5 + j - 1] = 1;
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            char c; cin >> c;
            int value = c - '0';

            if (value == 1) matrix.v[i * 5][j * 5] = 1;
            else if (value > 1) matrix.v[i * 5][j * 5 + value - 1] = 1;
        }
    }

    cout << matmul(matrix, t).v[s * 5][e * 5] % MOD << "\n";

    return 0;
}