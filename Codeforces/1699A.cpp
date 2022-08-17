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
        unsigned int n; cin >> n;
        if (n % 2) cout << -1 << "\n";
        else {
            n /= 2;
            cout << n << " 0 " << n << "\n";
        }
    }
    
    return 0;
}