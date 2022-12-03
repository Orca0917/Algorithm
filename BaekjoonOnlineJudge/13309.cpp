#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define MAX 200'001

using namespace std;

int N;  // number of nodes in tree
int Q;  // number of queries

vector<int> tree;           // AND operation segment tree
vector<int> adj[MAX];       // adjacency list

int subtree_size[MAX];      // subtree size that root node is index i
int HLD_num[MAX];           // heavy-light-decomposition id
int HLD_head[MAX];          // top of group
int HLD_depth[MAX];         // end of group
int HLD_parent[MAX];        // parent group
int HLD_cnt = 1;            // heavy-light-decomposition id numbering


// update segment tree
void update_tree(int node, int start, int end, int index, int value) {
    // out of range
    if (index < start || end < index) return;

    tree[node] = value;

    // not leaf node
    if (start != end) {
        int mid = (start + end) / 2;
        update_tree(node * 2, start, mid, index, value);
        update_tree(node * 2 + 1, mid + 1, end, index, value);
        tree[node] = tree[node * 2] & tree[node * 2 + 1];
    }
}


// query segment tree
int query_tree(int node, int start, int end, int left, int right) {
    // out of range
    if (right < start || end < left) return 1;
    // query range in node range
    if (left <= start && end <= right) return tree[node];

    int mid = (start + end) / 2;
    return query_tree(node * 2, start, mid, left, right) & \
           query_tree(node * 2 + 1, mid + 1, end, left, right);
}


void calc_subtree_size(int here, int level) {
    subtree_size[here] = 1;     // self

    for (int &there : adj[here]) {
        calc_subtree_size(there, level + 1);
        subtree_size[here] += subtree_size[there];

        // for heavy light decomposition, place heaviest subtree to front.
        if (subtree_size[there] > subtree_size[adj[here][0]] || adj[here][0] == there) {
            swap(adj[here][0], there);
        }
    }
}


void heavy_light_decomposition(int here, int depth) {
    HLD_num[here] = HLD_cnt++;
    HLD_depth[here] = depth;

    for (int there : adj[here]) {
        // heaviest subtree
        if (there == adj[here][0]) {
            HLD_head[there] = HLD_head[here];
            HLD_parent[there] = HLD_parent[here];
            heavy_light_decomposition(there, depth);
        }

        else {
            HLD_head[there] = there;
            HLD_parent[there] = here;
            heavy_light_decomposition(there, depth + 1);
        }
        
        // update segment tree with AND(&) calculation
        update_tree(1, 1, N, HLD_num[there], 1);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> N >> Q;

    int tree_height = (int)ceil(log2(N));
    int tree_size = (1 << (tree_height + 1));
    tree.resize(tree_size, 1);

    for (int i = 1; i < N; ++i) {
        int p; cin >> p;
        adj[p].push_back(i + 1);
    }

    // calculate subtree size before heavy-light-decomposition
    HLD_head[1] = 1;
    calc_subtree_size(1, 1);
    heavy_light_decomposition(1, 1);

    while (Q--) {
        bool result = true;
        int b, c, d; cin >> b >> c >> d;
        int B = b, C = c;

        // check path that connects b vertex and c vertex
        if (HLD_depth[b] > HLD_depth[c]) swap(b, c);

        // equalize HLD group depth
        while (HLD_depth[b] < HLD_depth[c]) {
            result &= query_tree(1, 1, N, HLD_num[HLD_head[c]], HLD_num[c]);
            c = HLD_parent[c];
        }

        // find same group
        while (HLD_head[b] != HLD_head[c]) {
            result &= query_tree(1, 1, N, HLD_num[HLD_head[b]], HLD_num[b]);
            result &= query_tree(1, 1, N, HLD_num[HLD_head[c]], HLD_num[c]);

            b = HLD_parent[b];
            c = HLD_parent[c];
        }

        // difference in same group
        if (HLD_num[b] > HLD_num[c]) swap(b, c);
        result &= query_tree(1, 1, N, HLD_num[b] + 1, HLD_num[c]);

        cout << (result ? "YES" : "NO") << "\n";

        if (d) {
            // check path that connects b vertex and c vertex.
            // if that path exists, delete edge which connects b vertex and its parent node.
            // elif that path not exists, delete edge which connects c vertex and its parent node.
            if (result) update_tree(1, 1, N, HLD_num[B], 0);
            else update_tree(1, 1, N, HLD_num[C], 0);
        }
    }
    
    return 0;
}