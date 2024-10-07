#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

int n; // 행사장의 수
int m; // 요청의 수

int dist[500][500];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n >> m;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> dist[i][j];
        }
    }

    // floyd-warshall
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dist[i][j] > dist[i][k] + dist[k][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }

    // queries
    while (m--) {
        int u, v, c; cin >> u >> v >> c;
        cout << (dist[u - 1][v - 1] <= c ? "Enjoy other party" : "Stay here") << "\n";
    }
    
    return 0;
}