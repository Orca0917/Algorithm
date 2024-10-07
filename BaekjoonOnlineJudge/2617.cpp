#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

int n, m;
const int INF = 1e9;

vector<vector<int>> heavier, lighter;

void floyd(vector<vector<int>>& dist) {
    for (int k = 1; k <= n; ++k) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n >> m;

    heavier.assign(n + 1, vector<int>(n + 1, INF));
    lighter.assign(n + 1, vector<int>(n + 1, INF));
    
    for (int i = 1; i <= n; ++i) {
        heavier[i][i] = 0;
        lighter[i][i] = 0;
    }

    while (m--) {
        int u, v;
        cin >> u >> v;
        heavier[u][v] = 1; // u가 더 무겁다
        lighter[v][u] = 1; // v가 더 가볍다
    }

    floyd(heavier);
    floyd(lighter);

    int answer = 0;
    for (int i = 1; i <= n; ++i) {
        int heavier_count = -1, lighter_count = -1;
        for (int j = 1; j <= n; ++j) {
            if (heavier[i][j] != INF) ++heavier_count;
            if (lighter[i][j] != INF) ++lighter_count;
        }
        if (heavier_count > n / 2 || lighter_count > n / 2) ++answer;
    }

    cout << answer << '\n';
    
    return 0;
}
