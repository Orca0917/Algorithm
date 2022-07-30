#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int testcase; cin >> testcase;
    while (testcase--) {
        int n; // number of students;
        int m; // number of pairs

        cin >> n >> m;

        vector<int> unhappiness(n + 1);
        for (int i = 1; i <= n; ++i) cin >> unhappiness[i];

        vector<pii> friends;
        vector<int> degree(n + 1, 0);
        for (int i = 1; i <= m; ++i) {
            int u, v; cin >> u >> v;
            friends.push_back({u, v});
            ++degree[u];
            ++degree[v];
        }

        int answer = 1e9;
        if (m % 2 == 0) answer = 0;

        for (int i = 1; i <= n; ++i) if (degree[i] % 2 == 1) answer = min(answer, unhappiness[i]);
        for (int i = 0; i < m; ++i) if (degree[friends[i].first] % 2 == 0 && degree[friends[i].second] % 2 == 0)
            answer = min(answer, unhappiness[friends[i].first] + unhappiness[friends[i].second]);

        cout << answer << "\n";
    }
    
    return 0;
}