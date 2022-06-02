#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int N; // 사람의 수
int M; // 서점의 수

int source = 0;
int sink = 201;

vector<int> adj[202];
int capacity[202][202], flow[202][202], cost[202][202];
int dist[202];
bool isin_queue[202];

int MCMF() {
    int max_flow_cost = 0;

    while (true) {

        //// initialize ////
        memset(dist, -1, sizeof(dist));
        memset(isin_queue, false, sizeof(isin_queue));


        vector<int> parent(202, -1);
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
    }

    return max_flow_cost;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    //// initialize ////
    memset(capacity, 0, sizeof(capacity));
    memset(flow, 0, sizeof(flow));
    memset(cost, 0, sizeof(cost));

    //// get input ////
    cin >> N >> M;
    for (int person = 1; person <= N; ++person) {
        cin >> capacity[person][sink];
        adj[sink].push_back(person);
        adj[person].push_back(sink);
    }

    for (int bookstore = 101; bookstore <= 100 + M; ++bookstore) {
        cin >> capacity[source][bookstore];
        adj[bookstore].push_back(source);
        adj[source].push_back(bookstore);
    }

    for (int bookstore = 101; bookstore <= 100 + M; ++bookstore)
        for (int person = 1; person <= N; ++person) {
            int c; cin >> c;
            cost[bookstore][person] = c;
            cost[person][bookstore] = -c;

            adj[bookstore].push_back(person);
            adj[person].push_back(bookstore);

            capacity[bookstore][person] = 1e9;
        }

    //// make graph ////
    
    cout << MCMF() << "\n";

    return 0;
}