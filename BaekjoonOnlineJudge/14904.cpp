#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define MAX 5002
using namespace std;

int n, k;
vector<int> adj[MAX];
int capacity[MAX][MAX], flow[MAX][MAX], cost[MAX][MAX];
int board[MAX][MAX];
bool vis[MAX];

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
            int here = q.front();
            q.pop();

            isin_queue[here] = false;

            for (int there : adj[here]) {
                if (capacity[here][there] > 0 && dist[there] > dist[here] + cost[here][there]) {
                    dist[there] = dist[here] + cost[here][there];
                    parent[there] = here;
                    if (isin_queue[there]) continue;
                    isin_queue[there] = true;
                    q.push(there);
                }
            }
        }

        if (parent[sink] == -1) break;

        int amount = 1;
        
        for (int node = sink; node != source; node = parent[node]) {
            capacity[parent[node]][node] -= amount;
            capacity[node][parent[node]] += amount;
            max_cost += cost[parent[node]][node];
        }
    }

    return -max_cost;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    memset(capacity, 0, sizeof(capacity));
    memset(flow, 0, sizeof(flow));
    memset(cost, 0, sizeof(cost));

    cin >> n >> k;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            cin >> board[i][j];

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            int here = (i - 1) * n + j;
            int here_in = here * 2;
            int here_out = here * 2 + 1;

            // 정점 분리 적용 : 사탕의 개수를 해당간선의 cost로 설정
            adj[here_in].push_back(here_out);
            adj[here_out].push_back(here_in);
            capacity[here_in][here_out] = k;

            // MCMF의 계산에서 cost를 -로 해줌으로서 최대의 cost를 계산하도록 설정
            cost[here_in][here_out] = -board[i][j];
            cost[here_out][here_in] = board[i][j];

            for (int d = 0; d < 2; ++d) {
                int nx = i + ("12"[d] - '0') - 1;
                int ny = j + ("21"[d] - '0') - 1;
                int there = (nx - 1) * n + ny;
                int there_in = there * 2;
                int there_out = there * 2 + 1;

                if (nx < 1 || nx > n || ny < 1 || ny > n) continue;
                adj[here_out].push_back(there_in);
                adj[there_in].push_back(here_out);
                capacity[here_out][there_in] = 1e9;
            }
        }
    }

    int source = 0, sink = 1;
    adj[source].push_back(2);
    adj[2].push_back(source);
    capacity[source][2] = k;

    adj[sink].push_back(n * n * 2 + 1);
    adj[n * n * 2 + 1].push_back(sink);
    capacity[n * n * 2 + 1][sink] = k;
    int answer = MCMF(source, sink);

    cout << answer << "\n";
    
    return 0;
}