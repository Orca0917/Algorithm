#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int v, e;
vector<pii> adj[10001];
vector<int> dist_starbucks(10001, -1);
vector<int> dist_mcdonalds(10001, -1);
priority_queue<pii> pq;

int is_mcdonalds[10001];
int is_starbucks[10001];

int min_mcdonalds = 0;
int min_starbucks = 0;

void dijkstra(vector<int> &dist) {

    while (!pq.empty()) {
        int cost = -pq.top().first;
        int here = pq.top().second;
        pq.pop();

        if (dist[here] > cost) continue;

        for (pii there_info : adj[here]) {
            int there = there_info.first;
            int c = there_info.second;

            if (dist[there] == -1 || dist[there] > cost + c) {
                dist[there] = cost + c;
                pq.push({-(cost + c), there});
            }
        }
    }
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> v >> e;

    while (e--) {
        int u1, u2, c; cin >> u1 >> u2 >> c;
        adj[u1].push_back({u2, c});
        adj[u2].push_back({u1, c});
    }

    memset(is_mcdonalds, false, sizeof(is_mcdonalds));
    memset(is_starbucks, false, sizeof(is_starbucks));

    int mcdonald_count = 0;
    int startbucks_count = 0;

    cin >> mcdonald_count >> min_mcdonalds;
    while (mcdonald_count--) {
        int mcdonald; cin >> mcdonald;
        is_mcdonalds[mcdonald] = true;

        pq.push({0, mcdonald});
        dist_mcdonalds[mcdonald] = 0;
    }

    dijkstra(dist_mcdonalds);

    cin >> startbucks_count >> min_starbucks;
    while (startbucks_count--) {
        int starbucks; cin >> starbucks;
        is_starbucks[starbucks] = true;

        pq.push({0, starbucks});
        dist_starbucks[starbucks] = 0;
    }

    dijkstra(dist_starbucks);

    int answer = -1;
    for (int node = 1; node <= v; ++node) {
        if (is_mcdonalds[node] || is_starbucks[node]) continue;
        if (dist_mcdonalds[node] > min_mcdonalds || dist_starbucks[node] > min_starbucks) continue;

        int ret = dist_mcdonalds[node] + dist_starbucks[node];
        if (answer == -1) answer = ret;
        else answer = min(answer, ret);
    }

    cout << answer << "\n";

    return 0;
}