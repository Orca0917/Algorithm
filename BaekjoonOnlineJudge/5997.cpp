#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define MAX 1102
using namespace std;

int n; // # of cows
int m; // # of study groups

vector<int> adj[MAX];
int capacity[MAX][MAX], flow[MAX][MAX];
int answer[MAX];

void network_flow(int source, int sink) {
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
            answer[node] = parent[node];
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    memset(capacity, 0, sizeof(capacity));
    memset(flow, 0, sizeof(flow));
    memset(answer, -1, sizeof(answer));

    int source = 0, sink = 1101;

    cin >> n >> m;

    // connection group - sink
    // connection cow - group
    for (int group = 1001; group <= 1000 + m; ++group) {
        adj[group].push_back(sink);
        adj[sink].push_back(group);
        capacity[group][sink] = 1;

        int cows; cin >> cows;
        while (cows--) {
            int cow; cin >> cow;
            adj[cow].push_back(group);
            adj[group].push_back(cow);
            capacity[cow][group] = 1;
        }
    }

    // connection source - cow
    for (int cow = 1; cow <= n; ++cow) {
        double cookie = 0;
        for (int there : adj[cow]) {
            int group_size = adj[there].size() - 1; // exclude sink
            cookie += 1 / (double)group_size;
        }

        adj[source].push_back(cow);
        adj[cow].push_back(source);
        capacity[source][cow] = ceil(cookie);
    }

    network_flow(source, sink);

    for (int group = 1001; group <= 1000 + m; ++group) {
        cout << answer[group] << "\n";
    }

    return 0;
}