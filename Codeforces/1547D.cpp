#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int testcase; cin >> testcase;
    while (testcase--) {
        int n; cin >> n;
        vector<int> X(n);
        for (int &x : X) cin >> x;
        vector<int> Y(n, 0);
        Y[0] = 0;
        X[0] ^= Y[0];

        for (int i = 1; i < n; ++i) {
            for (int bit = 1; bit <= max(X[i - 1], X[i]); bit = bit << 1) {
                if (((X[i - 1] & bit) >= 1) && ((X[i] & bit) == 0)) {
                    Y[i] |= bit;
                }
            }
            X[i] ^= Y[i];
        }

        for (int i = 0; i < n; ++i)
            cout << Y[i] << " ";
        
        cout << "\n";
    }
    
    return 0;
}