#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    queue<int> q[21];
    int n, m; cin >> n >> m;
    ll answer = 0;

    for (int i = 0; i < n; ++i) {
        string name; cin >> name;
        int len = name.length();

        int x = i;
        while (!q[len].empty() && q[len].front() + m < x) {
            answer += q[len].size() - 1;
            q[len].pop();
        }
        q[len].push(x);
    }

    for (int i = 1; i <= 20; ++i)
        if (!q[i].empty())
            answer += (1LL * q[i].size() * (q[i].size() - 1)) / 2;
    
    cout << answer << "\n";
    return 0;
}