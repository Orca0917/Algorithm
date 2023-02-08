#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

struct Edge {
    int dest, capacity, flow = 0;
    Edge* rev;

    Edge(int dest, int cap): dest(dest), capacity(cap) {}

    int remain() {
        return capacity - flow;
    }

    void add_flow(int amount) {
        flow += amount;
        rev->flow -= amount;
    }
};

vector<Edge*> adj[301];
int n, m;

void add_edge(int u, int v, int cap) {
    Edge* e1 = new Edge(v, cap);
    Edge* e2 = new Edge(u, 0);

    e1->rev = e2;
    e2->rev = e1;

    adj[u].push_back(e1);
    adj[v].push_back(e2);
}

void net_flow(int source, int sink) {
    while (true) {
        vector<bool> isin_queue(n + 1, false);
        isin_queue[source] = true;

        queue<int> q;
        q.push(source);

        vector<int> parent(n + 1, -1);
        parent[source] = source;

        vector<Edge*> path(n + 1, nullptr);

        while (!q.empty() && parent[sink] == -1) {
            int here = q.front(); q.pop();
            isin_queue[here] = false;

            for (Edge* e : adj[here]) {
                if (e->remain() && parent[e->dest] == -1) {
                    parent[e->dest] = here;
                    path[e->dest] = e;
                    if (isin_queue[e->dest]) continue;
                    isin_queue[e->dest] = true;
                    q.push(e->dest);
                }
            }
        }

        if (parent[sink] == -1) break;

        int amount = 1e9;
        for (int c = sink; c != source; c = parent[c]) {
            amount = min(amount, path[c]->remain());
        }

        for (int c = sink; c != source; c = parent[c]) {
            path[c] -> add_flow(amount);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int testcase; cin >> testcase;
    while (testcase--) {
        for (int i = 1; i <= 300; ++i) adj[i].clear();

        cin >> n >> m;
        while (m--) {
            int u, v, c; cin >> u >> v >> c;
            add_edge(u, v, c);
        }

        net_flow(1, n);

        int answer = 0;
        vector<bool> available(n + 1, true);
        for (int i = 1; i <= n; ++i)
            for (Edge* e : adj[i]) {
                if (e->capacity != 0 && e->remain() == 0) {
                    vector<int> parent(n + 1, -1);
                    parent[i] = i;

                    queue<int> q;
                    q.push(i);

                    vector<bool> isin_queue(n + 1, false);
                    isin_queue[i] = true;

                    while (!q.empty() && parent[e->dest] == -1) {
                        int here = q.front(); q.pop();
                        isin_queue[here] = false;
                        for (Edge* edge : adj[here]) {
                            if (edge->remain() && parent[edge->dest] == -1) {
                                parent[edge->dest] = here;
                                if (isin_queue[edge->dest]) continue;
                                q.push(edge->dest);
                                isin_queue[edge->dest] = true;
                            }
                        }
                    }

                    if (parent[e->dest] == -1) ++answer;
                }
            }


        cout << answer << "\n";
    }
    
    
    return 0;
}