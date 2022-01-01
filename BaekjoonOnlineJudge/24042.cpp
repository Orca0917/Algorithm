#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define pll pair<long long, long long>
using namespace std;

int n, m;
vector<pll> adj[100001];
ll inf = 1e18;

ll dijkstra() {
    priority_queue<pll> pq;
    pq.push({0, 1}); // time, here

    vector<ll> dist(n + 1, inf);
    dist[1] = 0;

    while (!pq.empty()) {
        ll nowTime = -pq.top().first;
        ll here = pq.top().second;
        pq.pop();

        if (dist[here] < nowTime) continue;

        for (pll thereInfo : adj[here]) {
            ll there = thereInfo.first;
            ll thereTime = thereInfo.second;
            
            ll nextTime;
            if (nowTime % m <= thereTime % m) {
                nextTime = nowTime + (thereTime % m) - (nowTime % m) + 1;
            } else {    
                nextTime = nowTime + (m - nowTime % m) + (thereTime % m) + 1;
            }

            if (dist[there] > nextTime) {
                dist[there] = nextTime;
                pq.emplace(-nextTime, there);
            }
        }
    }

    return dist[n];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n >> m;
    for (ll i = 0; i < m; ++i) {
        ll from, to; cin >> from >> to;
        adj[from].emplace_back(to, i);
        adj[to].emplace_back(from, i);
    }

    cout << dijkstra() << "\n";

    return 0;
}