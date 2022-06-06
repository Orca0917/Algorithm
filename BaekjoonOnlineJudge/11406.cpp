#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define MAX 202

using namespace std;

int n; // 사람의 수
int m; // 온라인 서점의 수

int source = 0;
int sink = 201;

vector<int> adj[MAX];
int capacity[MAX][MAX], flow[MAX][MAX];

int network_flow() {
    int max_flow = 0;

    while (true) {
        vector<int> parent(MAX, -1);
        parent[source] = source;

        queue<int> q;
        q.push(source);

        while (!q.empty() && parent[sink] == -1) {
            int here = q.front(); q.pop();
            for (int there : adj[here]) {
                if (capacity[here][there] - flow[here][there] > 0 && parent[there] == -1) {
                    parent[there] = here;
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
        }

        max_flow += amount;
    }

    return max_flow;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    memset(capacity, 0, sizeof(capacity));
    memset(flow, 0, sizeof(flow));

    cin >> n >> m;
    
    // person -> sink
    for (int person = 1; person <= n; ++person) {
        adj[sink].push_back(person);
        adj[person].push_back(sink);

        cin >> capacity[person][sink];
    }

    // source -> store
    for (int store = 1 + n; store <= n + m; ++store) {
        adj[source].push_back(store);
        adj[store].push_back(source);

        cin >> capacity[source][store];
    }

    // person -> store
    for (int store = 1 + n; store <= n + m; ++store) {
        for (int person = 1; person <= n; ++person) {
            adj[person].push_back(store);
            adj[store].push_back(person);

            cin >> capacity[store][person];
        }
    }

    cout << network_flow() << "\n";
    
    return 0;
}