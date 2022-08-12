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
        vector<int> arr(n);
        for (int i = 0; i < n; ++i) cin >> arr[i];

        bool is_possible = true;
        for (int i = 1; i < n && is_possible; ++i) {
            if (arr[i] % arr[0] != 0) is_possible = false;
        }

        if (is_possible) cout << "YES\n";
        else cout << "NO\n";
    }
    return 0;
}