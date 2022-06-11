#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define MAX 302

using namespace std;

int n; // 방의 개수
int m; // 복도의 수

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
                if (parent[there] == -1 && capacity[here][there] - flow[here][there] > 0) {
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

    memset(capacity, 0, sizeof(capacity));
    memset(flow, 0, sizeof(flow));

    cin >> n >> m;

    while (m--) {
        int room1, room2, candy;
        cin >> room1 >> room2 >> candy;   

        adj[room1].push_back(room2);
        adj[room2].push_back(room1);

        capacity[room1][room2] += candy;
        capacity[room2][room1] += candy;
    }

    cout << network_flow(1, n) << "\n";
    
    return 0;
}