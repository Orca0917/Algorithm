#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define MAX 500'001
#define MOD (1LL << 32)
using namespace std;

struct Tree {
    ll value;
    int lazy_add;
    int lazy_mul;
};

int n, q;

vector<int> adj[MAX];
vector<Tree> tree;

int hld_in[MAX];
int hld_out[MAX];
int hld_parent[MAX];
int hld_head[MAX];
int hld_depth[MAX];
int hld_cnt = 1;

int subtree_size[MAX];


void calc_subtree(int here, int parent) {
    subtree_size[here] = 1;
    for (int &there : adj[here]) {
        if (there == parent) continue;
        calc_subtree(there, here);
        subtree_size[here] += subtree_size[there];

        if (subtree_size[there] > subtree_size[adj[here][0]] || adj[here][0] == parent)
            swap(there, adj[here][0]);
    }
}


void hld(int here, int parent, int depth) {
    hld_in[here] = hld_cnt++;
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

    hld_out[here] = hld_cnt;
}


void lazy_propagation(int node, int start, int end) {
    if (tree[node].lazy_mul != 1 || tree[node].lazy_add != 0) {
        tree[node].value *= tree[node].lazy_mul;
        tree[node].value %= MOD; 
        tree[node].value += (end - start + 1) * tree[node].lazy_add;
        tree[node].value %= MOD;

        if (start != end) {
            tree[node * 2].lazy_mul *= tree[node].lazy_mul;
            tree[node * 2].lazy_mul %= MOD;

            tree[node * 2 + 1].lazy_mul *= tree[node].lazy_mul;
            tree[node * 2 + 1].lazy_mul %= MOD;

            tree[node * 2].lazy_add *= tree[node].lazy_mul;
            tree[node * 2].lazy_add %= MOD;
            tree[node * 2].lazy_add += tree[node].lazy_add;
            tree[node * 2].lazy_add %= MOD;

            tree[node * 2 + 1].lazy_add *= tree[node].lazy_mul;
            tree[node * 2 + 1].lazy_add %= MOD;
            tree[node * 2 + 1].lazy_add += tree[node].lazy_add;
            tree[node * 2 + 1].lazy_add %= MOD;
        }

        tree[node].lazy_add = 0;
        tree[node].lazy_mul = 1;
    }
}


void update_tree(int node, int start, int end, int left, int right, int mul, int add) {
    lazy_propagation(node, start, end);

    if (right < start || end < left) return;
    if (left <= start && end <= right) {
        tree[node].lazy_mul = mul;
        tree[node].lazy_add = add;
        lazy_propagation(node, start, end);
        return;
    }

    int mid = (start + end) / 2;
    update_tree(node * 2, start, mid, left, right, mul, add);
    update_tree(node * 2 + 1, mid + 1, end, left, right, mul, add);

    tree[node].value = tree[node * 2].value + tree[node * 2 + 1].value;
    tree[node].value %= MOD;
}


ll query_tree(int node, int start, int end, int left, int right) {
    lazy_propagation(node, start, end);

    if (right < start || end < left) return 0;
    if (left <= start && end <= right) return tree[node].value;

    int mid = (start + end) / 2;
    return (query_tree(node * 2, start, mid, left, right) + \
           query_tree(node * 2 + 1, mid + 1, end, left, right)) % MOD;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n >> q;

    for (int i = 1; i < n; ++i) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int tree_height = (int)ceil(log2(n + 1));
    int tree_size = (1 << (tree_height + 1));
    tree.resize(tree_size);

    calc_subtree(1, 0);
    hld_head[1] = 1;
    hld(1, 0, 1);
    

    int x, y, v;
    while (q--) {
        int option; cin >> option;

        if (option == 1) {
            cin >> x >> v;
            update_tree(1, 1, n, hld_in[x], hld_out[x], 1, v);
        }

        else if (option == 2) {
            cin >> x >> y >> v;
            while (hld_head[x] != hld_head[y]) {
                if (hld_depth[hld_head[x]] < hld_depth[hld_head[y]]) swap(x, y);
                update_tree(1, 1, n, hld_in[hld_head[x]], hld_in[x], 1, v);
                x = hld_parent[x];
            }

            if (hld_depth[x] > hld_depth[y]) swap(x, y);
            update_tree(1, 1, n, hld_in[x], hld_in[y], 1, v);
        }

        else if (option == 3) {
            cin >> x >> v;
            update_tree(1, 1, n, hld_in[hld_head[x]], hld_in[x], v, 0);
        }

        else if (option == 4) {
            cin >> x >> y >> v;
            while (hld_head[x] != hld_head[y]) {
                if (hld_depth[hld_head[x]] < hld_depth[hld_head[y]]) swap(x, y);
                update_tree(1, 1, n, hld_in[hld_head[x]], hld_in[x], v, 0);
                x = hld_parent[x];
            }

            if (hld_depth[x] > hld_depth[y]) swap(x, y);
            update_tree(1, 1, n, hld_in[x], hld_in[y], v, 0);
        }

        else if (option == 5) {
            cin >> x;
            cout << query_tree(1, 1, n, hld_in[x], hld_out[x]) << "\n";
        }

        else if (option == 6) {
            cin >> x >> y;
            int result = 0;
            
            while (hld_head[x] != hld_head[y]) {
                if (hld_depth[hld_head[x]] < hld_depth[hld_head[y]]) swap(x, y);
                result += query_tree(1, 1, n, hld_in[hld_head[x]], hld_in[x]);
                result %= MOD;
                x = hld_parent[x];
            }
            if (hld_depth[x] > hld_depth[y]) swap(x, y);
            result += query_tree(1, 1, n, hld_in[x], hld_in[y]);
            cout << result % MOD << "\n";
        }
    }
    return 0;
}