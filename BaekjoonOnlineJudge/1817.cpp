#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n, m; cin >> n >> m;
    vector<int> v(n);
    for (int &e : v) cin >> e;

    int answer = (n == 0 ? 0 : 1), cur = 0;
    for (int e : v) {
        if (cur + e <= m) cur += e;
        else {
            cur = e;
            answer += 1;
        }
    }
    
    cout << answer << "\n";

    return 0;
}