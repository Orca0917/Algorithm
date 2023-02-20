#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int num_city;
int num_road;

vector<pii> adj[2501];
vector<int> oil(2501, 0);

struct dt {
    ll cost;
    int city;
    int cheapest_oil;
};

struct cmp {
    bool operator() (dt &a, dt &b) {
        return a.cost > b.cost;
    }
};

ll dijkstra(int source, int sink) {
    vector<vector<ll>> dist(2501, vector<ll>(2501, LLONG_MAX));
    dist[source][oil[source]] = 0;

    priority_queue<dt, vector<dt>, cmp> pq;
    pq.push({0, source, oil[source]});

    while (!pq.empty()) {
        ll cost = pq.top().cost;
        int here = pq.top().city;
        int cheapest = pq.top().cheapest_oil;
        pq.pop();

        if (dist[here][cheapest] < cost) continue;
        if (here == sink) return cost;

        for (pii e : adj[here]) {
            int there = e.first;
            int here2there = e.second;
            ll next_cost = cost + (1LL * here2there * cheapest);

            // 여기서 주유를 얼마나 할 것인가?
            if (dist[there][cheapest] > next_cost) {
                dist[there][cheapest] = next_cost;
                pq.push({next_cost, there, min(cheapest, oil[there])});
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> num_city >> num_road;

    for (int i = 1; i <= num_city; ++i) cin >> oil[i];
    for (int i = 1; i <= num_road; ++i) {
        int from, to, dist; cin >> from >> to >> dist;
        adj[from].push_back({to, dist});
        adj[to].push_back({from, dist});
    }

    cout << dijkstra(1, num_city) << "\n";
    
    return 0;
}