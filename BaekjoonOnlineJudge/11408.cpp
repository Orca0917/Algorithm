#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int N; // 직원의 수
int M; // 일의 개수

vector<int> adj[802];
int capacity[802][802], flow[802][802], dist[802];
int cost[802][802];
bool isin_queue[802];

pii MCMF(int source, int sink) {
    int max_flow_cost = 0;
    int max_flow_cnt = 0;

    while (true) {

        //// initialize ////
        memset(dist, -1, sizeof(dist));
        vector<int> parent(802, -1);

        parent[source] = source;

        queue<int> q;
        q.push(source);
        isin_queue[source] = true;
        dist[source] = 0;

        while (!q.empty()) {
            int here = q.front(); q.pop();
            isin_queue[here] = false;

            for (int there : adj[here]) {
                if (capacity[here][there] - flow[here][there] > 0 && (dist[there] == -1 || dist[there] > dist[here] + cost[here][there])) {
                    parent[there] = here;
                    dist[there] = dist[here] + cost[here][there];
                    
                    if (isin_queue[there]) continue;
                    isin_queue[there] = true;
                    q.push(there);
                }
            }
        }

        if (parent[sink] == -1) break;

        int amount = 1e9;

        for (int node = sink; node != source; node = parent[node]) {
            amount = min(amount, capacity[parent[node]][node] - flow[parent[node]][node]);
        }

        for (int node = sink; node != source; node = parent[node]) {
            flow[parent[node]][node] += amount;
            flow[node][parent[node]] -= amount;
            max_flow_cost += amount * cost[parent[node]][node];
        }

        max_flow_cnt += 1;
    }

    return {max_flow_cnt, max_flow_cost};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    //// initialize ////
    memset(capacity, 0, sizeof(capacity));
    memset(flow, 0, sizeof(flow));
    memset(isin_queue, false, sizeof(isin_queue));

    //// get input ////
    cin >> N >> M;
    for (int person = 1; person <= N; ++person) {
        int can_do; cin >> can_do;
        for (int task = 1; task <= can_do; ++task) {
            int task_node; cin >> task_node;
            int task_cost; cin >> task_cost;

            task_node = task_node + 400;
            cost[person][task_node] = task_cost;
            cost[task_node][person] = -task_cost;

            adj[person].push_back(task_node);
            adj[task_node].push_back(person);

            capacity[person][task_node] = 1;
        }
    }

    //// make flow graph ////
    int source = 0;
    int sink = 801;

    for (int person = 1; person <= N; ++person) {
        adj[source].push_back(person);
        adj[person].push_back(source);

        capacity[source][person] = 1;
    }

    for (int task = 1; task <= M; ++task) {
        adj[400 + task].push_back(sink);
        adj[sink].push_back(400 + task);

        capacity[400 + task][sink] = 1;
    }

    //// Minimum Cost Maximum Flow ////
    pii answer = MCMF(source, sink);
    cout << answer.first << "\n" << answer.second << "\n";

    return 0;
}