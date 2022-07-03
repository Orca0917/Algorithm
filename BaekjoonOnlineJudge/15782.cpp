#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define MAX 100'001

using namespace std;

struct Tree {
    int value;
    int lazy;
};

vector<Tree> tree;
vector<int> arr, order;
vector<bool> vis;
vector<int> adj[MAX];

int left_r[MAX], right_r[MAX];

void dfs(int here, int &num) {
    if (vis[here]) return;
    vis[here] = true;
    
    left_r[here] = ++num;
    for (int there : adj[here]) dfs(there, num);
    right_r[here] = num;
}


int init_tree(int node, int start, int end) {
    if (start == end) {
        return tree[node].value = order[start];
    }

    int mid = (start + end) / 2;
    return tree[node].value = init_tree(node * 2, start, mid) ^ init_tree(node * 2 + 1, mid + 1, end);
}


void lazy_propagation(int node, int start, int end) {
    if (tree[node].lazy != 0) {
        if ((end - start + 1) % 2) tree[node].value ^= tree[node].lazy;

        if (start != end) {
            tree[node * 2].lazy ^= tree[node].lazy;
            tree[node * 2 + 1].lazy ^= tree[node].lazy;
        }

        tree[node].lazy = 0;
    }
}


int query_tree(int node, int start, int end, int left, int right) {

    lazy_propagation(node, start, end);

    if (right < start || end < left) return 0;
    if (left <= start && end <= right) return tree[node].value;

    int mid = (start + end) / 2;
    return query_tree(node * 2, start, mid, left, right) ^ query_tree(node * 2 + 1, mid + 1, end, left, right);
}


void update_tree(int node, int start, int end, int left, int right, int value) {
    
    lazy_propagation(node, start, end);

    if (right < start || end < left) return;
    if (left <= start && end <= right) {
        tree[node].lazy = value;
        lazy_propagation(node, start, end);
        return;
    }

    int mid = (start + end) / 2;
    update_tree(node * 2, start, mid, left, right, value);
    update_tree(node * 2 + 1, mid + 1, end, left, right, value);

    tree[node].value = tree[node * 2].value ^ tree[node * 2 + 1].value;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    memset(left_r, 0, sizeof(left_r));
    memset(right_r, 0, sizeof(left_r));
    int n, m; cin >> n >> m;
    
    // 노드의 상하관계를 표현
    for (int i = 1; i < n; ++i) {
        int from, to; cin >> from >> to;
        adj[from].push_back(to);
        adj[to].push_back(from);
    }

    // 각 노드에 담겨지는 초기 value
    arr.resize(n + 1);
    for (int i = 1; i <= n; ++i) cin >> arr[i];

    // 노드의 번호를 다시 부여하기
    int node_num = 0;
    vis.resize(n + 1, false);
    dfs(1, node_num);

    // 트리의 크기만큼 vector 공간 할당 진행
    int tree_height = (int)ceil(log2(n + 1));
    int tree_size = (1 << (tree_height + 1));
    tree.resize(tree_size, {0, 0});

    order.resize(n + 1);
    for (int node = 1; node <= n; ++node)
        order[left_r[node]] = arr[node];

    // 초기의 트리 상태로 업데이트
    init_tree(1, 1, n);

    // m 개의 쿼리 진행
    while (m--) {
        int query; cin >> query;
        if (query == 1) {
            int x; cin >> x;
            cout << query_tree(1, 1, n, left_r[x], right_r[x]) << "\n";
        }

        else if (query == 2) {
            int x, value; cin >> x >> value;
            update_tree(1, 1, n, left_r[x], right_r[x], value);
        }
    }

    return 0;
}