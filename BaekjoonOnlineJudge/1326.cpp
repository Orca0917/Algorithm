#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

int n;
vector<int> bridge;
int src, dest;
bool vis[10001];

int bfs() {
    priority_queue<pii> pq;
    pq.push({0, src});
    vis[src] = true;

    while (!pq.empty()) {
        int c = -pq.top().first;
        int x = pq.top().second;
        pq.pop();

        if (x == dest) return c;

        // 순방향
        for (int jump = 1; x + jump * bridge[x] <= n; ++jump) {
            int there = x + jump * bridge[x];
            if (vis[there]) continue;
            vis[there] = true;
            pq.push({-(c + 1), there});
        }
        
        // 역방향
        for (int jump = -1; x + jump * bridge[x] > 0; --jump) {
            int there = x + jump * bridge[x];
            if (vis[there]) continue;
            vis[there] = true;
            pq.push({-(c + 1), there});
        }
    }

    return -1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    // 돌다리의 수
    cin >> n;
    
    // 돌다리 정보 (배수)
    bridge.resize(n + 1);
    for (int i = 1; i <= n; ++i) cin >> bridge[i];

    // 출발지와 도착지
    cin >> src >> dest;
    
    memset(vis, false, sizeof(vis));
    cout << bfs();
    
    return 0;
}