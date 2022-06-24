#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define MAX 402
using namespace std;

int n; // # of schools

vector<int> adj[MAX];
int capacity[MAX][MAX], flow[MAX][MAX], cost[MAX][MAX];
int cur_number[MAX];
bool isin_queue[MAX];

pii MCMF(int source, int sink) {
    int max_cost = 0;
    int max_flow = 0;
    
    while (true) {
        vector<int> parent(MAX, -1);
        parent[source] = source;

        vector<int> dist(MAX, 1e9);
        dist[source] = 0;

        queue<int> q;
        q.push(source);

        memset(isin_queue, false, sizeof(isin_queue));
        isin_queue[source] = true;

        while (!q.empty()) {
            int here = q.front(); q.pop();
            isin_queue[here] = false;

            for (int there : adj[here]) {
                if (capacity[here][there] - flow[here][there] > 0 && dist[there] > dist[here] + cost[here][there]) {
                    dist[there] = dist[here] + cost[here][there];
                    parent[there] = here;
                    if (isin_queue[there]) continue;
                    isin_queue[there] = true;
                    q.push(there);
                }
            }
        }

        if (parent[sink] == -1) break;

        int amount = 1e9;
        for (int node = sink; node != source; node = parent[node])
            amount = min(amount, capacity[parent[node]][node] - flow[parent[node]][node]);

        for (int node = sink; node != source; node = parent[node]) {
            flow[parent[node]][node] += amount;
            flow[node][parent[node]] -= amount;
            max_cost += amount * cost[parent[node]][node];
        }

        max_flow += amount;
    }


    return {max_flow, max_cost};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    // initialize variables
    memset(capacity, 0, sizeof(capacity));
    memset(flow, 0, sizeof(flow));
    memset(cost, 0, sizeof(cost));
    memset(cur_number, 0, sizeof(cur_number));

    int source = 0, sink = 401;

    cin >> n;

    for (int index = 1; index <= n; ++index) {
        int m, a, b, k; cin >> m >> a >> b >> k;
        cur_number[index] = m;

        adj[source].push_back(index);
        adj[index].push_back(source);
        capacity[source][index] = 1;

        for (int new_num = 200 + a; new_num <= 200 + b; ++new_num) {
            adj[index].push_back(new_num);
            adj[new_num].push_back(index);
            capacity[index][new_num] = 1;

            int c = k * abs(m - (new_num - 200));
            cost[index][new_num] = c;
            cost[new_num][index] = -c;
        }
    }

    for (int ch = 201; ch <= 200 + n; ++ch) {
        adj[ch].push_back(sink);
        adj[sink].push_back(ch);
        capacity[ch][sink] = 1;
    }

    pii result = MCMF(source, sink);
    if (result.first == n)
        cout << result.second << "\n";
    else
        cout << "NIE\n";

    return 0;
}