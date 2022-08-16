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
        int a, b; cin >> a >> b;
        if (a % 2 != b % 2) cout << "Burenka\n";
        else cout << "Tonya\n";
    }
    
    return 0;
}