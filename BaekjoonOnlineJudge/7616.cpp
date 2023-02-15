#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define MAX 10002
#define INF 1e9
using namespace std;

struct Edge {
    int destination, capacity, flow = 0;
    Edge* reverse;

    Edge(int destination, int capacity):
        destination(destination), capacity(capacity) {}

    int remain() {
        return capacity - flow;
    }

    void add_flow(int amount) {
        flow += amount;
        reverse -> flow -= amount;
    }
};

vector<Edge*> adj[MAX];

void add_edge(int u, int v, int capacity) {
    Edge* e1 = new Edge(v, capacity);
    Edge* e2 = new Edge(u, 0);

    e1 -> reverse = e2;
    e2 -> reverse = e1;

    adj[u].push_back(e1);
    adj[v].push_back(e2);
}

int network_flow(int source, int sink) {
    int max_flow = 0;

    while (true) {
        vector<int> parent(MAX, -1);
        parent[source] = source;

        vector<Edge*> path(MAX, nullptr);

        queue<int> q;
        q.push(source);

        while (!q.empty()) {
            int here = q.front(); q.pop();

            for (Edge* edge : adj[here]) {
                int there = edge -> destination;
                if (edge -> remain() && parent[there] == -1) {
                    path[there] = edge;
                    parent[there] = here;
                    q.push(there);
                }
            }
        }

        if (parent[sink] == -1) break;

        for (int node = sink; node != source; node = parent[node])
            path[node] -> add_flow(1);
        max_flow += 1;
    }

    return max_flow;
}

void print_path(int source, int sink) {
    while (true) {
        vector<int> parent(MAX, -1);
        parent[source] = source;

        vector<Edge*> path(MAX, nullptr);

        queue<int> q;
        q.push(source);

        while (!q.empty()) {
            int here = q.front(); q.pop();

            for (Edge* edge : adj[here]) {
                int there = edge -> destination;
                if (edge -> flow && parent[there] == -1) {
                    path[there] = edge;
                    parent[there] = here;
                    q.push(there);
                }
            }
        }

        if (parent[sink] == -1) break;

        int amount = 1;

        vector<int> ret_path;
        for (int node = sink; node != source; node = parent[node]) {
            ret_path.push_back(node);
            path[node] -> add_flow(-1);
        }
        for (int i = ret_path.size() - 2; i >= 2; i -= 2) cout << ret_path[i] / 2 << " ";
        cout << "2\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int num_path, num_line, testcase = 1; 

    while (cin >> num_path >> num_line && num_path) {
        for (int i = 0; i < MAX; ++i) adj[i].clear();
        cout << "Case " << testcase++ << ":\n";

        int source = 0, sink = num_line * 2 + 2;

        string str; getline(cin, str);
        for (int line = 1; line <= num_line; ++line) {
            add_edge(line * 2, line * 2 + 1, (line <= 2 ? num_path : 1));
            getline(cin, str);
            stringstream ss(str);
            int other;
            while (ss >> other) add_edge(line * 2 + 1, other * 2, 1);
        }

        add_edge(source, 2, num_path);
        add_edge(2 * 2 + 1, sink, 1e9);

        int ret = network_flow(source, sink);

        if (ret < num_path) cout << "Impossible\n";
        else {
            print_path(source, sink);
        }
        cout << "\n";
    }
    
    return 0;
}