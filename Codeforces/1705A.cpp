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
        int n, x; cin >> n >> x;
        vector<int> arr(2 * n);
        for (int i = 0; i < 2 * n; ++i) cin >> arr[i];

        sort(arr.begin(), arr.end());

        bool is_possible = true;
        for (int i = 0; i < n && is_possible; ++i) {
            if (arr[i] + x > arr[i + n]) 
                is_possible = false;
        }

        if (is_possible) cout << "YES\n";
        else cout << "NO\n";
    }

    return 0;
}