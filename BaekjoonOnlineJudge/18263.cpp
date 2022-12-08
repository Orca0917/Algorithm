#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define MAX 100'001
using namespace std;

struct Query {
    int index;
    int u;
    int v;
    int typo;
    string answer;
};

int n, m;

vector<int> mp[MAX];
vector<int> adj[MAX];
vector<int> tree;
vector<Query> query;

int subtree_size[MAX];
int hld_cnt = 1;

int hld_num[MAX];
int hld_head[MAX];
int hld_parent[MAX];
int hld_depth[MAX];


// segment tree update
void update_tree(int node, int start, int end, int index, int value) {
    if (index < start || end < index) return;
    
    if (start != end) {
        int mid = (start + end) / 2;
        update_tree(node * 2, start, mid, index, value);
        update_tree(node * 2 + 1, mid + 1, end, index, value);

        tree[node] = tree[node * 2] | tree[node * 2 + 1];
    }
    else 
        tree[node] = value;
}


// segment tree query
int query_tree(int node, int start, int end, int left, int right) {
    if (right < start || end < left) return 0;
    if (left <= start && end <= right) return tree[node];

    int mid = (start + end) / 2;
    return query_tree(node * 2, start, mid, left, right) | \
           query_tree(node * 2 + 1, mid + 1, end, left, right);
}


// calculate subtree size
void calc_subtree(int here, int parent) {
    subtree_size[here] = 1;
    for (int &there : adj[here]) {
        if (there == parent) continue;
        calc_subtree(there, here);
        subtree_size[here] += subtree_size[there];
        if (subtree_size[there] > subtree_size[adj[here][0]]) {
            swap(adj[here][0], there);
        }
    }
}


// heavy light decomposition
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
}



int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n >> m;
    
    // init tree size
    int tree_height = (int)ceil(log2(n + 1));
    int tree_size = (1 << (1 + tree_height));
    tree.resize(tree_size);


    // save milk type index
    for (int i = 1; i <= n; ++i) {
        int typo; cin >> typo;
        mp[typo].push_back(i);
    }

    
    // make adjacency list
    for (int i = 1; i < n; ++i) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }


    // prepare hld
    calc_subtree(1, 0);
    hld_head[1] = 0;
    hld(1, 0, 1);


    // make offline query list
    for (int i = 0; i < m; ++i) {
        int u, v, t; cin >> u >> v >> t;
        query.push_back({i, u, v, t, "0"});
    }


    // sort offline query by type.
    sort(query.begin(), query.end(), [](const Query &a, const Query &b) {
        return a.typo < b.typo;
    });


    // process offline query & update
    int cur_type = 0;
    for (int i = 0; i < m; ++i) {
        if (cur_type != query[i].typo) {
            for (int idx : mp[cur_type]) update_tree(1, 1, n, hld_num[idx], 0);
            cur_type = query[i].typo;
            for (int idx : mp[cur_type]) update_tree(1, 1, n, hld_num[idx], 1);
        }

        int u = query[i].u;
        int v = query[i].v;
        int result = 0;

        if (hld_depth[u] > hld_depth[v]) swap(u, v);
        while (hld_depth[u] < hld_depth[v]) {
            result |= query_tree(1, 1, n, hld_num[hld_head[v]], hld_num[v]);
            v = hld_parent[v];
        }

        while (hld_head[u] != hld_head[v]) {
            result |= query_tree(1, 1, n, hld_num[hld_head[u]], hld_num[u]);
            result |= query_tree(1, 1, n, hld_num[hld_head[v]], hld_num[v]);
            u = hld_parent[u];
            v = hld_parent[v];
        }

        if (hld_num[u] > hld_num[v]) swap(u, v);
        result |= query_tree(1, 1, n, hld_num[u], hld_num[v]);

        query[i].answer = (result ? "1" : "0");
    }

    sort(query.begin(), query.end(), [](const Query &a, const Query &b) {
        return a.index < b.index;
    });

    for (int i = 0; i < m; ++i) cout << query[i].answer;
    cout << "\n";

    return 0;
}