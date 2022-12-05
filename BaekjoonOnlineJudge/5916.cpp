#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define MAX 100'001

using namespace std;

int N, M;

int subtree_size[MAX];
int hld_num[MAX];
int hld_parent[MAX];
int hld_head[MAX];
int hld_depth[MAX];
int hld_cnt = 1;

vector<int> adj[MAX];
vector<pair<ll, ll>> tree;

void update_tree(int node, int start, int end, int left, int right, int value) {
    if (tree[node].second != 0) {
        tree[node].first += (end - start + 1) * tree[node].second;
        if (start != end) {
            tree[node * 2].second += tree[node].second;
            tree[node * 2 + 1].second += tree[node].second;
        }
        tree[node].second = 0;
    }

    if (right < start || end < left) return;

    if (left <= start && end <= right) {
        tree[node].first += (end - start + 1) * value;
        if (start != end) {
            tree[node * 2].second += value;
            tree[node * 2 + 1].second += value;
        }
        return;
    }

    int mid = (start + end) / 2;
    update_tree(node * 2, start, mid, left, right, value);
    update_tree(node * 2 + 1, mid + 1, end, left, right, value);

    tree[node].first = tree[node * 2].first + tree[node * 2 + 1].first;
}


ll query_tree(int node, int start, int end, int left, int right) {
    if (tree[node].second != 0) {
        tree[node].first += (end - start + 1) * tree[node].second;
        if (start != end) {
            tree[node * 2].second += tree[node].second;
            tree[node * 2 + 1].second += tree[node].second;
        }
        tree[node].second = 0;
    }

    if (right < start || end < left) return 0;
    if (left <= start && end <= right) return tree[node].first;

    int mid = (start + end) / 2;
    return query_tree(node * 2, start, mid, left, right) + \
           query_tree(node * 2 + 1, mid + 1, end, left, right);
}

void calculate_subtree_size(int here, int parent) {
    subtree_size[here] = 1;

    for (int &there : adj[here]) {
        if (there == parent) continue;
        calculate_subtree_size(there, here);
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
            hld_parent[there] = hld_parent[here];
            hld_head[there] = hld_head[here];
            heavy_light_decomposition(there, here, depth);
        } else {
            hld_parent[there] = here;
            hld_head[there] = there;
            heavy_light_decomposition(there, here, depth + 1);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> N >> M;

    for (int i = 1; i < N; ++i) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    calculate_subtree_size(1, 0);
    hld_head[1] = 0;
    heavy_light_decomposition(1, 0, 1);
    
    int tree_height = (int)ceil(log2(N + 1));
    int tree_size = (1 << (tree_height + 1));
    tree.resize(tree_size, {0, 0});

    char command;
    int u, v;

    while (M--) {
        cin >> command >> u >> v;
        if (command == 'P') {
            while (hld_head[u] != hld_head[v]) {
                if (hld_depth[hld_head[u]] < hld_depth[hld_head[v]]) swap(u, v);
                update_tree(1, 1, N, hld_num[hld_head[u]], hld_num[u], 1);
                u = hld_parent[hld_head[u]];
            }
            if (hld_num[u] > hld_num[v]) swap(u, v);
            update_tree(1, 1, N, hld_num[u] + 1, hld_num[v], 1);
        }

        else if (command == 'Q') {
            ll result = 0;
            while (hld_head[u] != hld_head[v]) {
                if (hld_depth[hld_head[u]] < hld_depth[hld_head[v]]) swap(u, v);
                result += query_tree(1, 1, N, hld_num[hld_head[u]], hld_num[u]);
                u = hld_parent[hld_head[u]];
            }
            if (hld_num[u] > hld_num[v]) swap(u, v);
            result += query_tree(1, 1, N, hld_num[u] + 1, hld_num[v]);

            cout << result << "\n";
        }
    }
    return 0;
}