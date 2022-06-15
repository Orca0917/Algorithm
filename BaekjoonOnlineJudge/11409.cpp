#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define MAX 802
#define INF 1e9

using namespace std;

int n, m;
vector<int> adj[MAX];
int capacity[MAX][MAX], flow[MAX][MAX], cost[MAX][MAX];

pii MCMF(int source, int sink) {

    int max_flow = 0;
    int max_cost = 0;

    while (true) {
        
        vector<int> dist(MAX, INF);
        dist[source] = 0;

        vector<int> parent(MAX, -1);
        parent[source] = source;

        queue<int> q;
        q.push(source);
        
        vector<bool> isin_queue(MAX, false);
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

    memset(capacity, 0, sizeof(capacity));
    memset(cost, 0, sizeof(cost));

    cin >> n >> m;

    int source = 0, sink = 801;

    for (int person = 1; person <= n; ++person) {
        
        adj[source].push_back(person);
        adj[person].push_back(source);
        capacity[source][person] = 1;
        
        int num_tasks; cin >> num_tasks;
        while (num_tasks--) {
            int job, payment; cin >> job >> payment;
            job = job + 400;
            adj[person].push_back(job);
            adj[job].push_back(person);
            capacity[person][job] = 1;
            cost[person][job] = -payment;
            cost[job][person] = payment;
        }
    }

    for (int task = 401; task <= 400 + m; ++task) {
        adj[task].push_back(sink);
        adj[sink].push_back(task);
        capacity[task][sink] = 1;
    }

    // calculate Minimum Cost Maxmimum Flow
    pii result = MCMF(source, sink);
    cout << result.first << "\n" << -result.second << "\n";
   
    return 0;
}