#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n; cin >> n;
    ll answer = (n == 1) ? n : n + 1, adder = 1;
    for (int i = 2; i < n; i = adder + 1) {
        ll cnt = (n - 1) / i;
        adder = (n - 1) / cnt;
        answer += (adder - i + 1) * (cnt + 1);
    }

    cout << answer << "\n";
    return 0;
}