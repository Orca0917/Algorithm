#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

const int inf = 1234567890;
int n, m, x;
vector<pii> adj[1001];

vector<int> dijkstra(int start) {
    vector<int> dist1(n + 1, inf);

    priority_queue<pii> pq;
    pq.emplace(0, start);
    dist1[start] = 0;

    while (!pq.empty()) {
        int here = pq.top().second;
        int cost = -pq.top().first;
        pq.pop();

        if (dist1[here] < cost) continue;

        for(pii there : adj[here]) {
            int next = there.first;
            int nextCost = cost + there.second;

            if (dist1[next] > nextCost) {
                dist1[next] = nextCost;
                pq.emplace(-nextCost, next);
            }
        }
    }

    return dist1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n >> m >> x;
    for (int i = 0; i < m; ++i) {
        int from, to, cost; cin >> from >> to >> cost;
        adj[from].emplace_back(to, cost);
    }

    vector<int> back = dijkstra(x);

    int answer = 0;
    for (int start = 1; start <= n; ++start) {
        if (start == x) continue;
        vector<int> go = dijkstra(start);
        answer = max(answer, go[x] + back[start]);
    }

    cout << answer << "\n";

    return 0;
}