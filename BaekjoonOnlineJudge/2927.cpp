#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define MAX 30'001
using namespace std;

int N;      // number of islands
int Q;      // number of queries

string command;
int arg1, arg2;

vector<int> tree;                           // segment tree (summation)
vector<int> island;                         // number of penguins live in kth island
vector<tuple<string, int, int>> query;      // save query information (offline query)
vector<int> adj[MAX];                       // adjacency list
vector<string> answer;                      // answer for offline query (caution for index)


//// heavy-light-decomposition ////
int subtree_size[MAX];                      // size of subtree per node
int HLD_head[MAX];                          // start of HLD group
int HLD_parent[MAX];                        // parent group of current HLD group
int HLD_depth[MAX];                         // depth of HLD group
int HLD_num[MAX];                           // HLD group number
int HLD_cnt = 1;
///////////////////////////////////

/////////// Union-Find ////////////
int UF_parent[MAX];                         // union-find parent node
///////////////////////////////////


//-- union find
int find_f(int u) {
    if (UF_parent[u] != u) return UF_parent[u] = find_f(UF_parent[u]);
    return u;
}


void union_f(int u, int v) {
    u = find_f(u);
    v = find_f(v);

    if (u == v) return;

    UF_parent[u] = v;
}


//-- segment tree
void update_tree(int node, int start, int end, int index, int value) {
    if (index < start || end < index) return;
    if (start != end) {
        int mid = (start + end) / 2;
        update_tree(node * 2, start, mid, index, value);
        update_tree(node * 2 + 1, mid + 1, end, index, value);
        tree[node] = tree[node * 2] + tree[node * 2 + 1];
    }

    // leaf node.
    else {
        tree[node] = value;
    }
}

int query_tree(int node, int start, int end, int left, int right) {
    if (right < start || end < left) return 0;
    if (left <= start && end <= right) return tree[node];

    int mid = (start + end) / 2;
    return query_tree(node * 2, start, mid, left, right) + \
           query_tree(node * 2 + 1, mid + 1, end, left, right);
}


//-- heavy light decomposition
void calculate_subtree_size(int here, int parent) {
    subtree_size[here] = 1;
    for (int &there : adj[here]) {
        if (there == parent) continue;
        calculate_subtree_size(there, here);
        subtree_size[here] += subtree_size[there];
        
        // heaviest subtree goes to front
        if (subtree_size[there] > subtree_size[adj[here][0]] || adj[here][0] == there) {
            swap(there, adj[here][0]);
        }
    }
}


void heavy_light_decomposition(int here, int parent, int level) {
    HLD_num[here] = HLD_cnt++;
    HLD_depth[here] = level;

    for (int there : adj[here]) {
        if (there == parent) continue;

        if (there == adj[here][0]) {
            HLD_head[there] = HLD_head[here];
            HLD_parent[there] = HLD_parent[here];
            heavy_light_decomposition(there, here, level);
        }

        else {
            HLD_head[there] = there;
            HLD_parent[there] = here;
            heavy_light_decomposition(there, here, level + 1);
        }

        update_tree(1, 1, N, HLD_num[there], island[there]);
    }
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> N;
    
    // size initialization
    island.resize(N + 1);

    // set segment tree size
    int tree_height = (int)ceil(log2(N + 1));
    int tree_size = (1 << (tree_height + 1));
    tree.resize(tree_size, 0);
    
    // get number of penguins live in each island
    for (int i = 1; i <= N; ++i) cin >> island[i];
    // union-find parent information initialization
    for (int i = 1; i <= N; ++i) UF_parent[i] = i;

    cin >> Q;

    // size initialization
    query.resize(Q);
    answer.resize(Q);

    // save as offline query
    for (int i = 0; i < Q; ++i) {
        cin >> command >> arg1 >> arg2;
        query[i] = {command, arg1, arg2};
    }

    // process offline query 1
    for (int i = 0; i < Q; ++i) {
        tie(command, arg1, arg2) = query[i];

        // connect islands
        if (command == "bridge") {
            // new bridge needed
            if (find_f(arg1) != find_f(arg2)) {
                union_f(arg1, arg2);
                adj[arg1].push_back(arg2);
                adj[arg2].push_back(arg1);
                answer[i] = "yes";
            }

            // no need for connecting two islands
            else {
                answer[i] = "no";
            }
        }

        // query segment tree
        else if (command == "excursion") {
            if (find_f(arg1) != find_f(arg2)) {
                answer[i] = "impossible";
            }
        }
    }

    // get subtree size of heavy light decomposition
    for (int node = 1; node <= N; ++node) {
        if (subtree_size[node] == 0) {
           calculate_subtree_size(node, -1);
           HLD_head[node] = -1;
           heavy_light_decomposition(node, -1, 1);
        }
    }

    // add penguins
    for (int i = 1; i <= N; ++i)
        update_tree(1, 1, N, HLD_num[i], island[i]);

    // process offline query 2
    for (int i = 0; i < Q; ++i) {

        tie(command, arg1, arg2) = query[i];
        if (command == "penguins") {
            update_tree(1, 1, N, HLD_num[arg1], arg2);
        }

        else if (command == "excursion") {
            if (answer[i] == "impossible") continue;

            // Euler technique + least common ancestor
            int result = 0;
            if (HLD_depth[arg1] > HLD_depth[arg2]) swap(arg1, arg2);
            while (HLD_depth[arg1] < HLD_depth[arg2]) {
                result += query_tree(1, 1, N, HLD_num[HLD_head[arg2]], HLD_num[arg2]);
                arg2 = HLD_parent[arg2];
            }

            while (HLD_head[arg1] != HLD_head[arg2]) {
                result += query_tree(1, 1, N, HLD_num[HLD_head[arg1]], HLD_num[arg1]);
                result += query_tree(1, 1, N, HLD_num[HLD_head[arg2]], HLD_num[arg2]);
                
                arg1 = HLD_parent[arg1];
                arg2 = HLD_parent[arg2];
            }

            if (HLD_num[arg1] > HLD_num[arg2]) swap(arg1, arg2);
            result += query_tree(1, 1, N, HLD_num[arg1], HLD_num[arg2]);
            answer[i] = to_string(result);
        }
    }

    // print answer of offline query
    for (int i = 0; i < Q; ++i) {
        tie(command, arg1, arg2) = query[i];
        if (command == "penguins") continue;
        cout << answer[i] << "\n";
    }

    
    return 0;
}