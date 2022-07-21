#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

struct TREE {
    int value;
    int lazy;
};

int n;          // 회사 직원의 수
int m;          // 쿼리의 개수

vector<TREE> tree;
vector<int> adj[100001];

int left_range[100001];
int right_range[100001];


void lazy_propagation(int node, int start, int end) {
    if (tree[node].lazy != 0) {
        tree[node].value += tree[node].lazy;
        if (start != end) {
            tree[node * 2].lazy += tree[node].lazy;
            tree[node * 2 + 1].lazy += tree[node].lazy;
        }

        tree[node].lazy = 0;
    }
}

void dfs(int here, int &num) {
    left_range[here] = ++num;
    for (int there : adj[here]) dfs(there, num);
    right_range[here] = num;
}


void update_tree(int node, int start, int end, int left, int right, int value) {

    lazy_propagation(node, start, end);

    if (right < start || end < left) return;
    if (left <= start && end <= right) {
        tree[node].lazy += value;
        lazy_propagation(node, start, end);
        return;
    }

    int mid = (start + end) / 2;
    update_tree(node * 2, start, mid, left, right, value);
    update_tree(node * 2 + 1, mid + 1, end, left, right, value);

    tree[node].value = tree[node * 2].value + tree[node * 2 + 1].value;
}


int query_tree(int node, int start, int end, int left, int right) {

    lazy_propagation(node, start, end);

    if (right < start || end < left) return 0;
    if (left <= start && end <= right) return tree[node].value;

    int mid = (start + end) / 2;
    return query_tree(node * 2, start, mid, left, right) + query_tree(node * 2 + 1, mid + 1, end, left, right);
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> m;
    for (int person = 1; person <= n; ++person) {
        int boss; cin >> boss;
        if (boss == -1) continue;
        adj[boss].push_back(person);
    }

    int num = 0;    // 오일러 테크닉
    dfs(1, num);

    int tree_height = (int)ceil(log2(n));
    int tree_size = 1 << (tree_height + 1);
    tree.resize(tree_size);

    int option, x, y;
    while (m--) {
        cin >> option;
        if (option == 1) {
            cin >> x >> y;
            update_tree(1, 1, n, left_range[x], left_range[x], y);
        }

        else if (option == 2) {
            cin >> x;
            cout << query_tree(1, 1, n, left_range[x], right_range[x]) << "\n";
        }
    }

    return 0;
}