#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

const int MOD = 1e9 + 7;

typedef vector<vector<ll>> matrix;

matrix operator * (const matrix &a, const matrix &b) {
    matrix ret(2, vector<ll>(2));

    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 2; ++j)
            for (int k = 0; k < 2; ++k) {
                ret[i][j] += a[i][k] * b[k][j];
                ret[i][j] = (ret[i][j] + MOD) % MOD;
            }

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    ll n; cin >> n;

    if (n % 2) {
        cout << "0\n";
        return 0;
    }

    matrix answer = {{1, 0}, {0, 1}};
    matrix init = {{1, 0}, {1, 0}};
    matrix a = {{4, -1}, {1, 0}};
    
    n /= 2;
    while (n > 0) {
        if (n % 2) answer = answer * a;
        a = a * a;
        n /= 2;
    }

    answer = answer * init;

    cout << answer[0][0] << "\n";
    return 0;
}