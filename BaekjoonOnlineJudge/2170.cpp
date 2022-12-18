#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int n;
vector<pii> lines;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n;

    lines.resize(n);
    for (pii &e : lines) cin >> e.first >> e.second;

    sort(lines.begin(), lines.end());

    ll answer = 0;
    
    pii cur = {-1e9, -1e9};
    for (pii line : lines) {
        if (cur.second < line.first) {
            answer += (cur.second - cur.first);
            cur = line;
        } else if (cur.second < line.second) {
            cur.second = line.second;
        }
    }
    answer += (cur.second - cur.first);

    cout << answer << "\n";
    
    return 0;
}