#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

int n, m;
int dist[101][101];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n >> m;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            dist[i][j] = 1e9;
        }
    }

    while (m--) {
        int u, v; cin >> u >> v;
        dist[u][v] = 1;
    }

    for (int k = 1; k <= n; ++k) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }

    for (int i = 1; i <= n; ++i) {
        int answer = 0;
        for (int j = 1; j <= n; ++j) {
            if (i == j) continue;
            if (dist[i][j] == 1e9 && dist[j][i] == 1e9) ++answer;
        }
        cout << answer << "\n";
    }
    
    return 0;
}