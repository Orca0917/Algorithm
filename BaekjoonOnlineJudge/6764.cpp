#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int a, b, c, d; cin >> a >> b >> c >> d;
    if (a > b && b > c && c > d) cout << "Fish Diving\n";
    else if (a < b && b < c && c < d) cout << "Fish Rising\n";
    else if (a == b && b == c && c == d) cout << "Fish At Constant Depth\n";
    else cout << "No Fish\n";
    
    return 0;
}