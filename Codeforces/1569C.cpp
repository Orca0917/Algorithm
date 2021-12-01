#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long
#define MOD 998244353
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int testcase; cin >> testcase;
    while (testcase--) {
        int n; cin >> n;
        vector<int> arr(n);
        for (int i = 0; i < n; ++i) cin >> arr[i];
        int M = *max_element(arr.begin(), arr.end());
        int Mcnt = count(arr.begin(), arr.end(), M);
        int mcnt = count(arr.begin(), arr.end(), M - 1);

        ll answer = 1, notGood = 1;
        for (int i = 1; i <= n; ++i) {
            answer = answer * i % MOD;
            if (i != mcnt + 1) notGood = notGood * i % MOD;
        }
        if (Mcnt == 1) answer = (answer - notGood + MOD) % MOD;
        cout << answer << "\n";
    }
    return 0;
}