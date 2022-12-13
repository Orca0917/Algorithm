#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long
#define MAX 100005

using namespace std;

int n, q;
vector<int> adj[MAX];

int hld_num[MAX];
int hld_parent[MAX];
int hld_depth[MAX];
int hld_head[MAX];
int hld_tail[MAX];
int hld_cnt = 1;
int subtree_size[MAX];
int dep[MAX];

vector<pii> tree;


void propagate(int node, int start, int end) {
    if (tree[node].second != -1) {
        tree[node].first = (end - start + 1) * tree[node].second;
        if (start != end) {
            tree[node << 1].second = tree[node].second;
            tree[node << 1 | 1].second = tree[node].second;
        }
        tree[node].second = -1;
    }
}

void update(int node, int start, int end, int left, int right, int value) {
    propagate(node, start, end);
    if (right < start || end < left) return;
    if (left <= start && end <= right) {
        tree[node].second = value;
        propagate(node, start, end);
        return;
    }    

    int mid = (start + end) >> 1;
    update(node << 1, start, mid, left, right, value);
    update(node << 1 | 1, mid + 1, end, left, right, value);
    tree[node].first = tree[node << 1].first + tree[node << 1 | 1].first;    
}

int query(int node, int start, int end, int left, int right) {
    propagate(node, start, end);
    
    if (right < start || end < left) return 0;
    if (left <= start && end <= right) return tree[node].first;

    int mid = (start + end) >> 1;
    return query(node << 1, start, mid, left, right) + query(node << 1 | 1, mid + 1, end, left, right);   
}

void calc_sub(int here, int parent, int depth) {
    subtree_size[here] = 1;
    dep[here] = depth;

    for (int &there : adj[here]) {
        if (there == parent) continue;
        calc_sub(there, here, depth + 1);
        subtree_size[here] += subtree_size[there];
        if (subtree_size[there] > subtree_size[adj[here][0]]) {
            swap(there, adj[here][0]);
        }
    }
}


void hld(int here, int parent, int depth) {
    hld_num[here] = hld_cnt++;
    hld_depth[here] = depth;

    for (int there : adj[here]) {
        if (there == parent) continue;
        if (there == adj[here][0]) {
            hld_head[there] = hld_head[here];
            hld_parent[there] = hld_parent[here];
            hld(there, here, depth);
        } else {
            hld_head[there] = there;
            hld_parent[there] = here;
            hld(there, here, depth + 1);
        }
    }

    hld_tail[here] = hld_cnt - 1;
}

int qquery(int u, int v) {
    int result = 0;
    if (hld_depth[u] > hld_depth[v]) swap(u, v);
    while (hld_depth[u] < hld_depth[v]) {
        result += query(1, 1, n + 1, hld_num[hld_head[v]], hld_num[v]);
        v = hld_parent[v];
    }
    while (hld_head[u] != hld_head[v]) {
        result += query(1, 1, n + 1, hld_num[hld_head[u]], hld_num[u]);
        result += query(1, 1, n + 1, hld_num[hld_head[v]], hld_num[v]);
        u = hld_parent[u];
        v = hld_parent[v];
    }
    if (hld_num[u] > hld_num[v]) swap(u, v);
    result += query(1, 1, n + 1, hld_num[u], hld_num[v]);

    return result;
}

void uupdate(int u, int v, int x) {
    if (hld_depth[u] > hld_depth[v]) swap(u, v);
    while (hld_depth[u] < hld_depth[v]) {
        update(1, 1, n + 1, hld_num[hld_head[v]], hld_num[v], x);
        v = hld_parent[v];
    }
    while (hld_head[u] != hld_head[v]) {
        update(1, 1, n + 1, hld_num[hld_head[u]], hld_num[u], x);
        update(1, 1, n + 1, hld_num[hld_head[v]], hld_num[v], x);

        u = hld_parent[u];
        v = hld_parent[v];
    }

    if (hld_num[u] > hld_num[v]) swap(u, v);
    update(1, 1, n + 1, hld_num[u], hld_num[v], x);
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n;

    int tree_height = (int)ceil(log2(n + 2));
    int tree_size = (1 << (tree_height + 1));
    tree.resize(tree_size, {0, -1});

    for (int i = 1; i < n; ++i) {
        int p; cin >> p;
        adj[p].push_back(i);
    }

    calc_sub(0, 0, 1);
    hld_head[0] = 0;
    hld(0, 0, 1);

    cin >> q;
    while (q--) {
        string cmd; cin >> cmd;
        int x; cin >> x;

        if (cmd == "install") {
            cout << dep[x] - qquery(0, x) << "\n";
            uupdate(0, x, 1);
        }

        else if (cmd == "uninstall") {
            cout << query(1, 1, n + 1, hld_num[x], hld_tail[x]) << "\n";
            update(1, 1, n + 1, hld_num[x], hld_tail[x], 0);
        }
    }
    
    return 0;
}