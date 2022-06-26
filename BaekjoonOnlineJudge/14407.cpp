#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define MAX 55
using namespace std;

int n, m, t, k;
vector<int> adj[MAX];
int capacity[MAX][MAX], flow[MAX][MAX], cost[MAX][MAX];

set<vector<int> > s;

int MCMF(int source, int sink, int thickness) {
    int max_flow = 0;
    memset(flow, 0, sizeof(flow));

    while (true) {
        vector<int> parent(MAX, -1);
        parent[source] = source;

        vector<int> dist(MAX, 1e9);
        dist[source] = 0;

        vector<bool> isin_queue(MAX, false);
        isin_queue[source] = true;

        queue<int> q;
        q.push(source);

        while (!q.empty()) {
            int here = q.front(); q.pop();
            isin_queue[here] = false;

            for (int there : adj[here]) {
                if (capacity[here][there] - flow[here][there] > 0 && cost[here][there] <= thickness && parent[there] == -1 && dist[there] > dist[here] + 1) {
                    dist[there] = dist[here] + 1;
                    parent[there] = here;
                    if (isin_queue[there]) continue;
                    isin_queue[there] = true;
                    q.push(there);
                }
            }
        }

        if (parent[sink] == -1) break;

        int amount = 1, cnt = 0;
        for (int node = sink; node != source; node = parent[node]) {
            flow[parent[node]][node] += amount;
            flow[node][parent[node]] += amount;
            ++cnt;
        }

        max_flow += (t - cnt + 1);
    }

    return max_flow;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    memset(capacity, 0, sizeof(capacity));
    memset(cost, 0, sizeof(cost));

    cin >> n >> m >> t >> k;
    for (int i = 0; i < m; ++i) {
        int n1, n2, wave; cin >> n1 >> n2 >> wave;
        adj[n1].push_back(n2);
        adj[n2].push_back(n1);

        capacity[n1][n2] = k - 1;
        capacity[n2][n1] = k - 1;

        cost[n1][n2] = wave;
        cost[n2][n1] = wave;
    }

    int lo = 1, hi = 1e5, answer = -1;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        int result = MCMF(1, n, mid);

        if (result >= k) {
            answer = mid;
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }

    cout << answer << "\n";
    return 0;
}