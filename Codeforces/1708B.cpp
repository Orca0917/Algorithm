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
        int n, l, r; cin >> n >> l >> r;
        vector<int> answer(n + 1);

        bool is_possible = true;
        for (int i = 1; i <= n && is_possible; ++i) {
            int value = (l / i) * i;
            if (value < l) value += i;

            if (value <= r) answer[i] = value;
            else is_possible = false;
        }

        if (is_possible) {
            cout << "YES\n";
            for (int i = 1; i <= n; ++i) cout << answer[i] << " \n"[i == n];
        } else cout << "NO\n";
    }
    return 0;
}