#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

struct Tree {
    int value;
    int lazy;
};

int n, m;
vector<Tree> tree;
vector<int> arr;

int init_tree(int node, int start, int end) {
    if (start == end) {
        tree[node].value = arr[start];
        tree[node].lazy = 0;
        return tree[node].value;
    }

    int mid = (start + end) / 2;
    init_tree(node * 2, start, mid);
    init_tree(node * 2 + 1, mid + 1, end);

    tree[node].value = tree[node * 2].value ^ tree[node * 2 + 1].value;
    tree[node].lazy = 0;
    return tree[node].value;
}

void lazy_propagation(int node, int start, int end) {

    if (tree[node].lazy != 0) {
        if ((end - start + 1) % 2)
            tree[node].value ^= tree[node].lazy;

        if (start != end) {
            tree[node * 2].lazy ^= tree[node].lazy;
            tree[node * 2 + 1].lazy ^= tree[node].lazy;
        }

        tree[node].lazy = 0;
    }
}

void update_tree(int node, int start, int end, int left, int right, int k) {

    lazy_propagation(node, start, end);

    if (right < start || end < left) return; 
    if (left <= start && end <= right) {
        tree[node].lazy ^= k;
        lazy_propagation(node, start, end);
        return;
    }

    int mid = (start + end) / 2;
    update_tree(node * 2, start, mid, left, right, k);
    update_tree(node * 2 + 1, mid + 1, end, left, right, k);

    tree[node].value = tree[node * 2].value ^ tree[node * 2 + 1].value;
}

int query_tree(int node, int start, int end, int k) {
    
    lazy_propagation(node, start, end);

    if (k < start || end < k) return 0;
    if (start == end) return tree[node].value;

    int mid = (start + end) / 2;
    return query_tree(node * 2, start, mid, k) ^ query_tree(node * 2 + 1, mid + 1, end, k);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n;
    
    arr.resize(n);
    for (int &e : arr) cin >> e;

    int tree_height = (int)ceil(log2(n));
    int tree_size = (1 << (tree_height + 1));
    tree.resize(tree_size);

    init_tree(1, 0, n - 1);

    cin >> m;

    while (m--) {
        int option; cin >> option;
        if (option == 1) {
            int a, b, k; cin >> a >> b >> k;
            update_tree(1, 0, n - 1, a, b, k);
        }
        else if (option == 2) {
            int a; cin >> a;
            cout << query_tree(1, 0, n - 1, a) << "\n";
        }
    }
    
    return 0;
}