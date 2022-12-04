#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define MAX 100'001

using namespace std;

int N;
int M;

vector<int> adj[MAX];
vector<int> tree;
vector<int> arr;

int subtree_size[MAX];

int hld_head[MAX];
int hld_parent[MAX];
int hld_depth[MAX];
int hld_num[MAX];
int hld_cnt = 1;

int hld_num2node[MAX];


/// @brief segment tree update function
/// @param node     segment tree's node number
/// @param start    start range that current node contains
/// @param end      end range that current node contains
/// @param index    update index (hld_num)
/// @param value    update value (infinity or hld_num)
void update_tree(int node, int start, int end, int index, int value) {
    if (index < start || end < index) return;
    if (start != end) {
        int mid = (start + end) / 2;
        update_tree(node * 2, start, mid, index, value);
        update_tree(node * 2 + 1, mid + 1, end, index, value);
        tree[node] = min(tree[node * 2], tree[node * 2 + 1]);
    } else {
        tree[node] = value;
    }
}


/// @brief segment tree query function
/// @param node     segment tree's node number
/// @param start    start range that current node contains
/// @param end      end range that current node contains
/// @param left     start range that we want to know (query range)
/// @param right    end range that we want to know (query range)
/// @return         minimum hld_num
int query_tree(int node, int start, int end, int left, int right) {
    if (right < start || end < left) return 1e9;
    if (left <= start && end <= right) return tree[node];

    int mid = (start + end) / 2;
    return min(query_tree(node * 2, start, mid, left, right), \
                query_tree(node * 2 + 1, mid + 1, end, left, right));
}


/// @brief caculate subtree at each node
/// @param here     current node 
/// @param parent   parent node
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


/// @brief heavy light decompostion with adj list
/// @param here     current node
/// @param parent   parent node
/// @param depth    depth in "heavy light decomposition tree"
void heavy_light_decomposition(int here, int parent, int depth) {
    hld_num[here] = hld_cnt++;
    hld_num2node[hld_num[here]] = here;
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
    
    cin >> N;

    int tree_height = (int)ceil(log2(N + 1));
    int tree_size = (1 << (tree_height + 1));
    tree.resize(tree_size);
    arr.resize(N + 1, 0);

    for (int i = 1; i < N; ++i) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    calculate_subtree_size(1, 0);
    hld_head[1] = 0;
    heavy_light_decomposition(1, 0, 1);

    for (int i = 1; i <= N; ++i) update_tree(1, 1, N, hld_num[i], 1e9);

    cin >> M;

    while (M--) {
        int c, x; cin >> c >> x;
        if (c == 1) {
            arr[x] ^= 1;
            update_tree(1, 1, N, hld_num[x], (arr[x] == 1) ? hld_num[x] : 1e9);
        } 
        
        else if (c == 2) {
            int answer = 1e9;
            
            while (hld_head[1] != hld_head[x]) {
                answer = min(answer, query_tree(1, 1, N, hld_num[hld_head[x]], hld_num[x]));
                x = hld_parent[x];
            }
            answer = min(answer, query_tree(1, 1, N, hld_num[hld_head[x]], hld_num[x]));

            if (answer == 1e9) cout << "-1\n";
            else cout << hld_num2node[answer] << "\n";
        }
    }
    
    return 0;
}