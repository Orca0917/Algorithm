#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define MAX 100'001

using namespace std;

int N, Q;

int hld_num[MAX];
int hld_parent[MAX];
int hld_head[MAX];
int hld_depth[MAX];
int hld_cnt = 1;

vector<int> arr, tree;
vector<int> adj[MAX];

int subtree_size[MAX];


void update_tree(int node, int start, int end, int index, int value) {
    if (index < start || end < index) return;
    if (start != end) {
        int mid = (start + end) / 2;
        update_tree(node * 2, start, mid, index, value);
        update_tree(node * 2 + 1, mid + 1, end, index, value);
        tree[node] = tree[node * 2] ^ tree[node * 2 + 1];
    }
    else {
        tree[node] = value;
    }
}


int query_tree(int node, int start, int end, int left, int right) {
    if (right < start || end < left) return 0;
    if (left <= start && end <= right) return tree[node];

    int mid = (start + end) / 2;

    return query_tree(node * 2, start, mid, left, right) ^ \
           query_tree(node * 2 + 1, mid + 1, end, left, right);
}


void calc_subtree_size(int here, int parent) {
    subtree_size[here] = 1;
    for (int &there : adj[here]) {
        if (there == parent) continue;
        calc_subtree_size(there, here);
        subtree_size[here] += subtree_size[there];

        if (subtree_size[there] > subtree_size[adj[here][0]] || adj[here][0] == parent) {
            swap(there, adj[here][0]);
        }
    }
}


void heavy_light_decomposition(int here, int parent, int depth) {
    hld_num[here] = hld_cnt++;
    hld_depth[here] = depth;

    for (int there : adj[here]) {
        if (there == parent) continue;
        if (there == adj[here][0]) {
            hld_head[there] = hld_head[here];
            hld_parent[there] = hld_parent[here];
            heavy_light_decomposition(there, here, depth);
        }

        else {
            hld_head[there] = there;
            hld_parent[there] = here;
            heavy_light_decomposition(there, here, depth + 1);
        }
    }
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> N >> Q;

    int tree_height = (int)ceil(log2(N + 1));
    int tree_size = (1 << (tree_height + 1));
    tree.resize(tree_size);

    arr.resize(N + 1);
    for (int i = 1; i <= N; ++i) cin >> arr[i];

    for (int i = 1; i < N; ++i) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    calc_subtree_size(1, 0);
    hld_head[1] = 0;
    heavy_light_decomposition(1, 0, 1);

    for (int i = 1; i <= N; ++i) update_tree(1, 1, N, hld_num[i], arr[i]);

    while (Q--) {
        int op, x, y; cin >> op >> x >> y;

        if (op == 1) {
            update_tree(1, 1, N, hld_num[x], y);
        }

        else if (op == 2) {
            int result = 0;

            if (hld_depth[x] > hld_depth[y]) swap(x, y);
            while (hld_depth[x] < hld_depth[y]) {
                result ^= query_tree(1, 1, N, hld_num[hld_head[y]], hld_num[y]);
                y = hld_parent[y];
            }   

            while (hld_head[x] != hld_head[y]) {
                result ^= query_tree(1, 1, N, hld_num[hld_head[x]], hld_num[x]);
                result ^= query_tree(1, 1, N, hld_num[hld_head[y]], hld_num[y]);
                x = hld_parent[x];
                y = hld_parent[y];
            }

            if (hld_num[x] > hld_num[y]) swap(x, y);
            result ^= query_tree(1, 1, N, hld_num[x], hld_num[y]);

            cout << result << "\n";
        }
    }
    
    return 0;
}