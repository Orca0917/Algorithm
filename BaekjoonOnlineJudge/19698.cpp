#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n, w, h, l; cin >> n >> w >> h >> l;
    cout << min(n, (w / l) * (h / l)) << "\n";
    
    return 0;
}