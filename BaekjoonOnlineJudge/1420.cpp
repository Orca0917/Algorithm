#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

struct Edge {
    int from;
    int to;
    int capacity;
    int flow;

    Edge* rev;
    Edge(int u, int v, int c) : from(u), to(v), capacity(c), flow(0) {}

    int left() { return capacity - flow; }
    void new_flow(int amount) {
        flow += amount;
        rev->flow -= amount;
    }
};

int n, m;
vector<Edge*> adj[20002];
char board[101][101];


void addEdge(int u, int v, int c) {
    Edge* e1 = new Edge(u, v, c);
    Edge* e2 = new Edge(v, u, 0);

    e1 -> rev = e2;
    e2 -> rev = e1;

    adj[u].push_back(e1);
    adj[v].push_back(e2);
}

bool available(int x, int y, int dir) {
    if (dir) return x + 1 < n;
    else return y + 1 < m;
}

int max_flow(int source, int sink) {
    int ret = 0;
    while (true) {
        vector<Edge*> parent(20002, nullptr);
        queue<int> q;
        q.push(source);

        while (!q.empty() && parent[sink] == nullptr) {
            int here = q.front(); q.pop();
            for (Edge* there_info : adj[here]) {
                int there = there_info->to;
                if (there_info->left() && parent[there] == nullptr) {
                    q.push(there);
                    parent[there] = there_info;
                }
            }
        }

        if (parent[sink] == nullptr) break;

        for (int p = sink; p != source; p = parent[p]->from) {
            if (p != sink && p != source + 1) parent[p] -> new_flow(1);
        }

        ++ret;
    }

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n >> m;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> board[i][j];
            int idx = (i * m + j) * 2;
            addEdge(idx, idx + 1, 1);
        }
    }

    pii start, end;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {

            if (board[i][j] == 'H') start = {i, j};
            if (board[i][j] == 'K') end = {i, j};
            if (board[i][j] == '#') continue;

            int cur = (i * m + j) * 2;
            if (available(i, j, 0)) {
                if (board[i][j + 1] != '#') {
                    addEdge((i * m + j) * 2 + 1, (i * m + j + 1) * 2, 1);
                    addEdge((i * m + j + 1) * 2 + 1, (i * m + j) * 2, 1);
                }
            }

            if (available(i, j, 1) && board[i + 1][j] != '#') {
                addEdge((i * m + j) * 2 + 1, ((i + 1) * m + j) * 2, 1);
                addEdge(((i + 1) * m + j) * 2 + 1, (i * m + j) * 2, 1);
            }
        }
    }

    if (abs(start.first - end.first) + abs(start.second - end.second) == 1)
        cout << "-1\n";
    else {
        int source = start.first * m + start.second;
        int sink = end.first * m + end.second;
        cout << max_flow(source * 2, sink * 2 + 1) << "\n";
    }
    
    return 0;
}