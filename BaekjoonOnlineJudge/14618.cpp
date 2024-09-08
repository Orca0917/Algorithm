#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>
#define ll long long

int N, M, J, K;
vector<char> home_type;
vector<vector<pii>> adj;
vector<int> dist;

void dijkstra() {
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    pq.push({0, J});
    dist[J] = 0;

    while (!pq.empty()) {
        int cost = pq.top().first;
        int cur = pq.top().second;
        pq.pop();

        if (dist[cur] < cost) continue;

        for (pii there : adj[cur]) {
            int nxt = there.first, w = there.second;
            if (dist[nxt] > dist[cur] + w) {
                dist[nxt] = dist[cur] + w;
                pq.push({dist[nxt], nxt});
            }
        }
    }

    int A = 1e9, B = 1e9;
    
    // A, B 집 모두 처리하는 경우
    for (int i = 1; i <= N; ++i) {
        if (home_type[i] == 'A') {
            A = min(A, dist[i]);
        } else if (home_type[i] == 'B') {
            B = min(B, dist[i]);
        }
    }

    if (A == 1e9 && B == 1e9) cout << "-1\n";
    else if (A <= B) cout << "A\n" << A;
    else cout << "B\n" << B;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M >> J >> K;

    home_type.resize(N + 1, 'X');  // 'X'는 집이 없는 기본 상태
    adj.resize(N + 1);
    dist.assign(N + 1, 1e9);

    for (int i = 0; i < K; ++i) {
        int home; cin >> home;
        home_type[home] = 'A';
    }

    for (int i = 0; i < K; ++i) {
        int home; cin >> home;
        home_type[home] = 'B';
    }

    for (int i = 0; i < M; ++i) {
        int u, v, w; 
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    dijkstra();
    
    return 0;
}
