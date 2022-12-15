#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define MAX 100001
using namespace std;

int n, q;

vector<pii> tree;
vector<int> adj[MAX];

int hld_num[MAX];
int hld_parent[MAX];
int hld_depth[MAX];
int hld_head[MAX];
int hld_cnt = 1;

int subtree[MAX];

void propagate(int node, int start, int end) {
    if (tree[node].second != 0) {
        tree[node].first += (end - start + 1) * tree[node].second;
        if (start != end) {
            tree[node << 1].second += tree[node].second;
            tree[node << 1 | 1].second += tree[node].second;
        }
        tree[node].second = 0;
    }
}


void tree_update(int node, int start, int end, int left, int right, int value) {
    propagate(node, start, end);
    if (right < start || end < left) return;
    if (left <= start && end <= right) {
        tree[node].second = value;
        propagate(node, start, end);
        return;
    }

    int mid = start + end >> 1;
    tree_update(node << 1, start, mid, left, right, value);
    tree_update(node << 1 | 1, mid + 1, end, left, right, value);
    tree[node].first = tree[node << 1].first + tree[node << 1 | 1].first;
}


// {range sum, range len}
pii tree_query(int node, int start, int end, int left, int right) {
    propagate(node, start, end);
    if (right < start || end < left) return {0, 0};
    if (left <= start && end <= right) return {tree[node].first, end - start + 1};

    int mid = start + end >> 1;
    pii ret1 = tree_query(node << 1, start, mid, left, right);
    pii ret2 = tree_query(node << 1 | 1, mid + 1, end, left, right);
    return {ret1.first + ret2.first, ret1.second + ret2.second};
}


void hld_update(int u, int v, int value) {
    if (hld_depth[u] > hld_depth[v]) swap(u, v);
    while (hld_depth[u] < hld_depth[v]) {
        tree_update(1, 1, n, hld_num[hld_head[v]], hld_num[v], value);
        v = hld_parent[v];
    }
    while (hld_head[u] != hld_head[v]) {
        tree_update(1, 1, n, hld_num[hld_head[u]], hld_num[u], value);
        tree_update(1, 1, n, hld_num[hld_head[v]], hld_num[v], value);

        u = hld_parent[u];
        v = hld_parent[v];
    }
    if (hld_num[u] > hld_num[v]) swap(u, v);
    tree_update(1, 1, n, hld_num[u], hld_num[v], value);
}


int hld_query(int u, int v) {
    int _sum = 0;
    int _len = 0;
    pii ret;

    if (hld_depth[u] > hld_depth[v]) swap(u, v);
    while (hld_depth[u] < hld_depth[v]) {
        ret = tree_query(1, 1, n, hld_num[hld_head[v]], hld_num[v]);
        _sum += ret.first;
        _len += ret.second;
        v = hld_parent[v];
    }
    while (hld_head[u] != hld_head[v]) {
        ret = tree_query(1, 1, n, hld_num[hld_head[u]], hld_num[u]);
        _sum += ret.first;
        _len += ret.second;
        ret = tree_query(1, 1, n, hld_num[hld_head[v]], hld_num[v]);
        _sum += ret.first;
        _len += ret.second;

        u = hld_parent[u];
        v = hld_parent[v];
    }
    if (hld_num[u] > hld_num[v]) swap(u, v);
    ret = tree_query(1, 1, n, hld_num[u], hld_num[v]);
    _sum += ret.first;
    _len += ret.second;

    return _sum - _len;
}


void calc_subtree(int here, int parent) {
    subtree[here] = 1;
    for (int &there : adj[here]) {
        if (there == parent) continue;
        calc_subtree(there, here);
        subtree[here] += subtree[there];
        if (subtree[there] > subtree[adj[here][0]]) swap(there, adj[here][0]);
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
        }
        else {
            hld_head[there] = there;
            hld_parent[there] = here;
            hld(there, here, depth + 1);
        }
    }
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n >> q;
    
    int tree_height = (int)ceil(log2(n + 1));
    int tree_size = (1 << (tree_height + 1));
    tree.resize(tree_size, {0, 0});

    for (int i = 1; i < n; ++i) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    calc_subtree(1, 0);
    hld_head[1] = 1;
    hld(1, 0, 1);
    
    int u1, u2, v1, v2;
    while (q--) {
        cin >> u1 >> v1 >> u2 >> v2;
        hld_update(u1, v1, 1);
        hld_update(u2, v2, 1);
        cout << hld_query(u2, v2) << "\n";
        hld_update(u2, v2, -1);
        hld_update(u1, v1, -1);
    }

    return 0;
}