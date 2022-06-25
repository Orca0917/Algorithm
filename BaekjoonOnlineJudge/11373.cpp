#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define MAX 1001

using namespace std;
int n, m;  // 무기의 종류, 병사의 수
char c; // 무기 종류
int t;  // 보유 수량

map<char, int> weapon2index;
vector<int> adj[MAX];
int capacity[MAX][MAX], flow[MAX][MAX], cost[MAX][MAX];

int MCMF(int source, int sink) {
    int max_cost = 0;

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
                if (capacity[here][there] - flow[here][there] > 0 && dist[there] > dist[here] + cost[here][there]) {
                    dist[there] = dist[here] + cost[here][there];
                    parent[there] = here;
                    if (isin_queue[there]) continue;
                    isin_queue[there] = true;
                    q.push(there);
                }
            }
        }

        // 더이상의 증가경로가 발견되지 않음.
        if (parent[sink] == -1) break;

        int amount = 1;
        for (int node = sink; node != source; node = parent[node]) {
            flow[parent[node]][node] += amount;
            flow[node][parent[node]] -= amount;
            max_cost += cost[parent[node]][node];
        }
    }

    return max_cost;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int testcase; cin >> testcase;
    while (testcase--) {

        // init
        weapon2index.clear();
        for (int i = 0; i < MAX; ++i) adj[i].clear();
        memset(capacity, 0, sizeof(capacity));
        memset(flow, 0, sizeof(flow));
        memset(cost, 0, sizeof(cost));

        int weapon_index = 901;
        int source = 0, sink = 1000;

        cin >> n >> m;

        // weapon -> sink
        for (int weapon = 1; weapon <= n; ++weapon) {
            cin >> c >> t;
            if (weapon2index.find(c) == weapon2index.end())
                weapon2index[c] = weapon_index++;
            
            adj[weapon2index[c]].push_back(sink);
            adj[sink].push_back(weapon2index[c]);
            capacity[weapon2index[c]][sink] = t;
        }

        // soldier -> weapon
        for (int soldier = 1; soldier <= m; ++soldier) {
            string weapons; cin >> weapons;
            int inexp = 0;
            for (char weapon : weapons) {
                adj[weapon2index[weapon]].push_back(soldier);
                adj[soldier].push_back(weapon2index[weapon]);
                capacity[soldier][weapon2index[weapon]] = 1;
                
                cost[soldier][weapon2index[weapon]] = inexp;
                cost[weapon2index[weapon]][soldier] = -inexp;
                ++inexp;
            }
        }

        // source -> soldier
        for (int soldier = 1; soldier <= m; ++soldier) {
            adj[source].push_back(soldier);
            adj[soldier].push_back(source);
            capacity[source][soldier] = 1;
        }

        cout << MCMF(source, sink) << "\n";
    }
    
    return 0;
}