#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define MAX 100'001
using namespace std;

int n, m; 
struct Tree {
    int value;
    int lazy;
};

vector<Tree> tree;
vector<int> under_boss[MAX];
int left_range[MAX], right_range[MAX];

void dfs(int here, int &num) {
    left_range[here] = ++num;
    for (int there : under_boss[here]) dfs(there, num);
    right_range[here] = num;
}

void init_tree(int node, int start, int end) {
    if (start == end) {
        tree[node].value = 1;
        tree[node].lazy = -1;
        return;
    }

    int mid = (start + end) / 2;
    init_tree(node * 2, start, mid);
    init_tree(node * 2 + 1, mid + 1, end);

    tree[node].value = tree[node * 2].value + tree[node * 2 + 1].value;
}

void lazy_propagation(int node, int start, int end) {
    if (tree[node].lazy != -1) {
        tree[node].value = tree[node].lazy * (end - start + 1);
        if (start != end) {
            tree[node * 2].lazy = tree[node].lazy;
            tree[node * 2 + 1].lazy = tree[node].lazy;
        }
        tree[node].lazy = -1;
    }
}

void update_tree(int node, int start, int end, int left, int right, int value) {
    lazy_propagation(node, start, end);

    if (right < start || end < left) return;
    if (left <= start && end <= right) {
        tree[node].value = (end - start + 1) * value;
        if (start != end) {
            tree[node * 2].lazy = value;
            tree[node * 2 + 1].lazy = value;
        }
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

    cin >> n;
    for (int person = 1; person <= n; ++person) {
        int boss; cin >> boss;
        if (boss == 0) continue;
        under_boss[boss].push_back(person);
    }

    int order_num = 0;
    dfs(1, order_num);

    int tree_height = (int)ceil(log2(n));
    int tree_size = (1 << (tree_height + 1));
    tree.resize(tree_size, {0, -1});

    init_tree(1, 1, n);

    cin >> m;
    while (m--) {
        int option, person; cin >> option >> person;
       
        if (option == 1) {
            // turn on computer
            update_tree(1, 1, n, left_range[person] + 1, right_range[person], 1);
        }

        else if (option == 2) {
            // turn off computer
            update_tree(1, 1, n, left_range[person] + 1, right_range[person], 0);
        }

        else if (option == 3) {
            // query
            cout << query_tree(1, 1, n, left_range[person] + 1, right_range[person]) << "\n";
        }
    }
    
    return 0;
}