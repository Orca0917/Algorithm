#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define MAX 100001

using namespace std;

int n, q;

int hld_age[MAX];
int hld_num[MAX];
int hld_depth[MAX];
int hld_parent[MAX];
int hld_head[MAX];
int hld_cnt = 1;

int sz[MAX];
int age[MAX];
bool is_boss[MAX];

vector<int> adj[MAX];
vector<vector<int>> tree;
vector<vector<ll>> psum;

void merge_arr(int node, int lchild, int rchild) {
    int lp = 0, rp = 0;
    while (lp < tree[lchild].size() && rp < tree[rchild].size()) {
        if (tree[lchild][lp] <= tree[rchild][rp]) {
            tree[node].push_back(tree[lchild][lp++]);
        } else {
            tree[node].push_back(tree[rchild][rp++]);
        }
    }

    while (lp < tree[lchild].size())
        tree[node].push_back(tree[lchild][lp++]);
    
    while (rp < tree[rchild].size())
        tree[node].push_back(tree[rchild][rp++]);
}

void init_tree(int node, int start, int end) {
    if (start == end) {
        tree[node].push_back(hld_age[start]);
        psum[node].push_back(hld_age[start]);
        return;
    }

    // merge sort tree
    int mid = start + end >> 1;
    init_tree(node << 1, start, mid);
    init_tree(node << 1 | 1, mid + 1, end);
    merge_arr(node, node << 1, node << 1 | 1);

    // psum of segment tree
    psum[node].resize(end - start + 1);
    psum[node][0] = tree[node][0];
    for (int i = 1; i < tree[node].size(); ++i)
        psum[node][i] = psum[node][i - 1] + tree[node][i];
}


ll query_tree(int node, int start, int end, int left, int right, int _min, int _max) {
    if (right < start || end < left) return 0LL;
    if (left <= start && end <= right) {
        int it_begin = lower_bound(tree[node].begin(), tree[node].end(), _min) - tree[node].begin();
        int it_end = upper_bound(tree[node].begin(), tree[node].end(), _max) - tree[node].begin();

        ll L = 0, R = 0;
        if (it_begin > 0) L = psum[node][it_begin - 1];
        if (it_end > 0) R = psum[node][it_end - 1];
        return R - L;
    }

    int mid = start + end >> 1;
    return query_tree(node << 1, start, mid, left, right, _min, _max) + \
           query_tree(node << 1 | 1, mid + 1, end, left, right, _min, _max);
}


void calc_subtree(int here, int parent) {
    sz[here] = 1;
    for (int &there : adj[here]) {
        if (there == parent) continue;
        calc_subtree(there, here);
        sz[here] += sz[there];
        if (sz[there] > sz[adj[here][0]]) swap(there, adj[here][0]);
    }
}

void hld(int here, int parent, int depth) {
    hld_age[hld_cnt] = age[here];
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
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n >> q;
    for (int i = 1; i <= n; ++i) cin >> age[i];

    int tree_height = (int)ceil(log2(MAX));
    int tree_size = (1 << (tree_height + 1));
    tree.resize(tree_size);
    psum.resize(tree_size);

    memset(is_boss, true, sizeof(is_boss));
    for (int i = 1; i < n; ++i) {
        int u, v; cin >> u >> v;
        adj[v].push_back(u);
        adj[u].push_back(v);
    }

    calc_subtree(1, 0);
    hld_head[1] = 1;
    hld(1, 0, 1);
    init_tree(1, 1, n);

    while (q--) {
        int u, v, l, r; cin >> u >> v >> l >> r;
        ll result = 0;
        
        if (hld_depth[u] > hld_depth[v]) swap(u, v);
        while (hld_depth[u] < hld_depth[v]) {
            result += query_tree(1, 1, n, hld_num[hld_head[v]], hld_num[v], l, r);
            v = hld_parent[v];
        }
        while (hld_head[u] != hld_head[v]) {
            result += query_tree(1, 1, n, hld_num[hld_head[u]], hld_num[u], l, r);
            result += query_tree(1, 1, n, hld_num[hld_head[v]], hld_num[v], l, r);
            u = hld_parent[u];
            v = hld_parent[v];
        }
        if (hld_num[u] > hld_num[v]) swap(u, v);
        result += query_tree(1, 1, n, hld_num[u], hld_num[v], l, r);

        cout << result << "\n";
    }
    
    return 0;
}