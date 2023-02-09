#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int n, m;

struct Edge {
    int dest, capacity, flow = 0;
    Edge* rev;

    Edge(int dest, int cap): dest(dest), capacity(cap) {}

    int remain() {
        return capacity - flow;
    }

    void add_flow(int amount) {
        flow += amount;
        rev -> flow -= amount;
    }
};


vector<Edge*> adj[102];


void add_edge(int u, int v, int cap) {
    Edge* e1 = new Edge(v, cap);
    Edge* e2 = new Edge(u, 0);

    e1 -> rev = e2;
    e2 -> rev = e1;

    adj[u].push_back(e1);
    adj[v].push_back(e2);
}


int net_flow(int source, int sink, bool change_flow = false) {
    int ret = 0;

    while (true) {
        vector<int> parent(n + m + 2, -1);
        parent[source] = source;

        vector<bool> isin_queue(n + m + 2, false);
        isin_queue[source] = true;

        vector<Edge*> path(n + m + 2, nullptr);
        
        queue<int> q;
        q.push(source);

        while (!q.empty() && parent[sink] == -1) {
            int here = q.front(); q.pop();
            isin_queue[here] = false;

            for (Edge* edge : adj[here]) {
                int there = edge -> dest;
                if (change_flow && (here < source || here == source && there < sink)) continue; // 사전순 정의
                if (edge -> remain() > 0 && parent[there] == -1) {
                    parent[there] = here;
                    path[there] = edge;
                    if (isin_queue[there]) continue;
                    isin_queue[there] = true;
                    q.push(there);
                }
            }
        }

        if (parent[sink] == -1) break;

        if (change_flow) { // source -> sink 유량 초기화
            for (int i = 1; i < adj[source].size(); ++i) {
                if (adj[source][i] -> dest == sink) {
                    adj[source][i] -> flow = 0;
                    adj[source][i] -> rev -> flow = 0;
                    break;
                }
            }
        }

        for (int c = sink; c != source; c = parent[c]) path[c] -> add_flow(1);

        ++ret;

        if (change_flow) break;
    }

    return ret;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n >> m;

    int source = 0;
    int sink = n + m + 1;

    int team1_flow = 0, team2_flow = 0;
    for (int i = 1; i <= n; ++i) { // source -> team1
        int cap; cin >> cap;
        team1_flow += cap;
        add_edge(source, i, cap);
    }

    for (int i = n + 1; i <= n + m; ++i) { // team2 -> sink
        int cap; cin >> cap;
        team2_flow += cap;
        add_edge(i, sink, cap);
    }

    for (int i = 1; i <= n; ++i) { // team1 -> team2
        for (int j = n + 1; j <= n + m; ++j) {
            add_edge(i, j, 1);
        }
    }

    int flows = net_flow(source, sink); // first flow
    if (flows != team1_flow || flows != team2_flow) {
        cout << "-1\n";
        return 0;
    }

    for (int src = 1; src <= n; ++src) { // change flow
        for (Edge *e : adj[src]) {
            if (e->capacity > 0 && e -> remain() == 0) {
                net_flow(src, e -> dest, true);
            }
        }
    }

    int answer[102][102];
    for (int i = 1; i <= n; ++i) {
        for (Edge* e : adj[i]) {
            if (e -> capacity > 0)
                answer[i][e->dest] = e->flow;
        }
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cout << answer[i][n + j];
        }
        cout << "\n";
    }
    
    return 0;
}