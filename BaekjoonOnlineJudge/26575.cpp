#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int testcase; cin >> testcase;
    while(testcase--) {
        double a, b, c; cin >> a >> b >> c;
        cout << setprecision(2);
        cout << fixed << "$" << a * b * c << "\n";
    }
    
    return 0;
}