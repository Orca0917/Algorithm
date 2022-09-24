#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

bool adj[51][51];
vector<int> answer;
int n, m;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n >> m;

    int connect_cnt = m * 2;
    int max_connect = n * (n - 1);
    int answer_day = 0;
    memset(adj, false, sizeof(adj));

    while (m--) {
        int u, v; cin >> u >> v;
        adj[u - 1][v - 1] = adj[v - 1][u - 1] = true;
    }


    while (true) {
        vector<pii> new_connection;
        new_connection.clear();

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                for (int k = 0; k < n; ++k) {
                    if (!adj[i][k] && adj[i][j] && adj[j][k] && i != k) {
                        new_connection.push_back({i, k});
                    }
                }
            }
        }
        
        if (new_connection.empty()) break;

        ++answer_day;
        
        int cnt = 0;
        for (pii &e : new_connection) {
            if (!adj[e.first][e.second]) ++cnt;
            adj[e.first][e.second] = true;
        }

        connect_cnt += cnt;
        answer.push_back(cnt / 2);
    }

    cout << answer_day << "\n";
    for (int e : answer) cout << e << "\n";
    
    return 0;
}