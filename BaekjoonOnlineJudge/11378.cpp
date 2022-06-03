#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define MAX 2003
using namespace std;

int N; // 직원의 수
int M; // 작업의 수
int K; // 벌점의 총합

vector<int> adj[MAX];
int capacity[MAX][MAX], flow[MAX][MAX];

int network_flow(int source, int sink) {
    int max_flow = 0;

    while (true) {

        vector<int> parent(MAX, -1);
        parent[source] = source;

        queue<int> q;
        q.push(source);

        while (!q.empty() && parent[sink] == -1) {
            int here = q.front(); q.pop();

            for (int there : adj[here]) {
                if (parent[there] != -1) continue;
                if (capacity[here][there] - flow[here][there] > 0) {
                    parent[there] = here;
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
        }

        max_flow += amount;
    }

    return max_flow;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int source = 0, sink = 2001, bridge = 2002;

    memset(capacity, 0, sizeof(capacity));
    memset(flow, 0, sizeof(flow));

    cin >> N >> M >> K;
    
    // 1. link source to person
    for (int person = 1; person <= N; ++person) {
        adj[source].push_back(person);
        adj[person].push_back(source);

        capacity[source][person] = 1;
    }

    // 2 . link person to task
    for (int person = 1; person <= N; ++person) {
        int task_cnt; cin >> task_cnt;
        while (task_cnt--) {
            int task_num; cin >> task_num;
            task_num += 1000;

            adj[person].push_back(task_num);
            adj[task_num].push_back(person);

            capacity[person][task_num] = 1;
        }
    }

    // 3. link task to sink
    for (int task = 1001; task <= M + 1000; ++task) {
        adj[task].push_back(sink);
        adj[sink].push_back(task);

        capacity[task][sink] = 1;
    }

    // 4. link source to bridge
    adj[source].push_back(bridge);
    adj[bridge].push_back(source);
    capacity[source][bridge] = K;

    // 5. link bridge to person
    for (int person = 1; person <= N; ++person) {
        adj[bridge].push_back(person);
        adj[person].push_back(bridge);
        capacity[bridge][person] = K;
    }

    cout << network_flow(source, sink) << "\n";
    return 0;
}