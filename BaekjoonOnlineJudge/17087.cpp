#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n, s; cin >> n >> s;
    vector<int> a(n);
    for (int &e : a) cin >> e;
    int answer = abs(s - a[0]);
    for (int i = 1; i < n; ++i) {
        int dist = abs(s - a[i]);
        answer = __gcd(answer, dist);
    }
    cout << answer << "\n";
    
    return 0;
}