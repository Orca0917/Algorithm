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
        ll n; cin >> n;
        if ((n + 1) % 3 == 0 || n % 9 == 0)
            cout << "TAK\n";
        else {
            cout << "NIE\n";
        }
    }
    
    return 0;
}