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

        int start_idx = 1;
        if (n % 2) {
            cout << "1 ";
            start_idx = 2;
        }

        for (int i = start_idx; i + 1 <= n; i += 2) {
            cout << i + 1 << " " << i << " ";
        }
        cout << "\n";
    }
    
    return 0;
}