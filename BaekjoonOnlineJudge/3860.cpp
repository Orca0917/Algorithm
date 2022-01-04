#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define inf 1234567890
using namespace std;

int W, H, G, E, X, Y, X1, Y1, X2, Y2, T;
int myoji[31][31];
vector<pii> adj[1000];
vector<int> dist(1000, inf);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    while (true) {
        cin >> W >> H;
        if (W == 0 && H == 0) break;

        // initialize
        memset(myoji, 0, sizeof(myoji));
        for (int i = 0; i < 1000; ++i) adj[i].clear();
        fill(dist.begin(), dist.end(), inf);

        cin >> G;
        for (int i = 0; i < G; ++i) {
            cin >> X >> Y;
            myoji[X][Y] = 1;
        }

        cin >> E;
        for (int i = 0; i < E; ++i) {
            cin >> X1 >> Y1 >> X2 >> Y2 >> T;
            int from = X1 + Y1 * W;
            int to = X2 + Y2 * W;
            myoji[X1][Y1] = 2;
            adj[from].push_back({to, T});
        }

        for (int i = 0; i < W; ++i) {
            for (int j = 0; j < H; ++j) {
                if (i == W - 1 && j == H - 1) continue;
                if (myoji[i][j] == 0) {
                    for (int k = 0; k < 4; ++k) {
                        int x = i + "2110"[k] - '1';
                        int y = j + "1201"[k] - '1';
                        if (x < 0 || x >= W || y < 0 || y >= H) continue;
                        if (myoji[x][y] != 1) {
                            int from = i + j * W;
                            int to = x + y * W;
                            adj[from].push_back({to, 1});
                        }
                    }
                }
            }
        }

        bool negCycle = false;
        dist[0] = 0;
        for (int i = 0; i < W * H; ++i) {
            for (int j = 0; j < W * H; ++j) {
                for (pii there : adj[j]) {
                    int v = there.first;
                    int cost = there.second;
                    // cout << j << " adj with " << v << ", cost = " << cost << "\n";
                    if (dist[j] != inf && dist[j] + cost < dist[v]) {
                        dist[v] = dist[j] + cost;
                        // cout << "update distance = " << j << " - " << v << " => " << dist[v] << "\n";

                        if (i == W * H - 1) negCycle = true;
                    }
                }
            }
        }

        if (negCycle) cout << "Never\n";
        else if (dist[H * W - 1] == inf) cout << "Impossible\n";
        else cout << dist[H * W - 1] << "\n";
    }
    
    return 0;
}