#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define MAX 250'001
using namespace std;

int n, m;

vector<int> tree;
vector<int> adj[MAX];

int hld_num[MAX];
int hld_parent[MAX];
int hld_depth[MAX];
int hld_head[MAX];
int hld_cnt = 1;

int subtree_size[MAX];


void update_tree(int node, int start, int end, int index, int value) {
    if (index < start || end < index) return;
    if (start ^ end) {
        int mid = (start + end) / 2;
        update_tree(node * 2, start, mid, index, value);
        update_tree(node * 2 + 1, mid + 1, end, index, value);
        tree[node] = tree[node * 2] + tree[node * 2 + 1];
    } else {
        tree[node] = value;
    }
}


int query_tree(int node, int start, int end, int left, int right) {
    if (right < start || end < left) return 0;
    if (left <= start && end <= right) return tree[node];

    int mid = (start + end) / 2;
    return query_tree(node * 2, start, mid, left, right) + query_tree(node * 2 + 1, mid + 1, end, left, right);
}


void calc_sub(int here, int parent) {
    subtree_size[here] = 1;
    for (int &there : adj[here]) {
        if (there == parent) continue;
        calc_sub(there, here);
        subtree_size[here] += subtree_size[there];
        if (subtree_size[there] > subtree_size[adj[here][0]] || adj[here][0] == parent)
            swap(there, adj[here][0]);
    }
}


void hld(int here, int parent, int depth) {
    hld_num[here] = hld_cnt++;
    hld_depth[here] = depth;
    for (int there : adj[here]) {
        if (there == parent) continue;
        if (there == adj[here][0]) {
            hld_parent[there] = hld_parent[here];
            hld_head[there] = hld_head[here];
            hld(there, here, depth);
        } else {
            hld_parent[there] = here;
            hld_head[there] = there;
            hld(there, here, depth + 1);
        }
    }
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n;

    int tree_height = (int)ceil(log2(n + 1));
    int tree_size = (1 << (tree_height + 1));
    tree.resize(tree_size);

    for (int i = 1; i < n; ++i) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }  

    calc_sub(1, 0);
    hld_head[1] = 0;
    hld(1, 0, 1);

    for (int i = 2; i <= n; ++i) update_tree(1, 1, n, hld_num[i], 1);

    cin >> m;

    char c;
    int x, y;
    for (int i = 1; i < n + m; ++i) {
        cin >> c;
        if (c == 'W') {
            cin >> y;
            x = 1;

            int result = 0;
            while (hld_head[x] != hld_head[y]) {
                if (hld_depth[hld_head[x]] < hld_depth[hld_head[y]]) swap(x, y);
                result += query_tree(1, 1, n, hld_num[hld_head[x]], hld_num[x]);
                x = hld_parent[x];
            }

            if (hld_num[x] > hld_num[y]) swap(x, y);
            result += query_tree(1, 1, n, hld_num[x] + 1, hld_num[y]);

            cout << result << "\n";
        }

        else if (c == 'A') {
            cin >> x >> y;
            if (hld_num[x] > hld_num[y]) swap(x, y);
            update_tree(1, 1, n, hld_num[y], 0);
        }
    }
    
    return 0;
}