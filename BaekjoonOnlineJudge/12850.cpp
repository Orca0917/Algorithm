#include <bits/stdc++.h>
#define pii pair<int, int>
#define vvll vector<vector<ll>>
#define ll long long
#define MOD 1'000'000'007

using namespace std;

vvll operator * (const vvll &A, const vvll &B) {
    vvll ret(8, vector<ll>(8, 0));

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            for (int k = 0; k < 8; ++k)
                ret[i][j] += A[i][k] * B[k][j];
            ret[i][j] %= MOD;
        }
    }

    return ret;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int t; cin >> t;

    vvll adj = {

    //   0  1  2  3  4  5  6  7
        {0, 1, 0, 0, 1, 0, 0, 0},
        {1, 0, 1, 0, 0, 1, 0, 0},
        {0, 1, 0, 1, 0, 1, 1, 0},
        {0, 0, 1, 0, 0, 0, 1, 1},
        {1, 0, 0, 0, 0, 1, 0, 0},
        {0, 1, 1, 0, 1, 0, 1, 0},
        {0, 0, 1, 1, 0, 1, 0, 1},
        {0, 0, 0, 1, 0, 0, 1, 0}
    };

    // answer (possible number to (i, i))
    vvll answer(8, vector<ll>(8, 0));
    for (int i = 0; i < 8; ++i) answer[i][i] = 1;

    while (t) {
        if (t % 2) answer = answer * adj;
        adj = adj * adj;
        t /= 2;
    }
    
    cout << answer[7][7] << "\n";

    return 0;
}