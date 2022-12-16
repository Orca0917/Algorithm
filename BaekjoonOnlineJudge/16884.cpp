#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int n;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int testcase; cin >> testcase;
    while (testcase--) {
        cin >> n;
        cout << (n % 2 ? "koosaga" : "cubelover") << "\n";
    }
    
    
    return 0;
}