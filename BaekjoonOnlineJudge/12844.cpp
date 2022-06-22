#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
using namespace std;

struct Node {
    int value;
    int lazy;
};

int n, m;
vector<int> arr;
vector<Node> tree;

void init_tree() {
    int tree_height = (int)ceil(log2(n)) + 1;
    int tree_size = (1 << tree_height);
    tree.resize(tree_size, {0, 0});
}

int make_tree(int node, int start, int end) {
    if (start == end) return tree[node].value = arr[start];
    int mid = (start + end) / 2;
    return tree[node].value = make_tree(node * 2, start, mid) ^ make_tree(node * 2 + 1, mid + 1, end);
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

    if (left > end || right < start) return 0;
    if (left <= start && end <= right) return tree[node].value;

    int mid = (start + end) / 2;
    int left_child = query_tree(node * 2, start, mid, left, right);
    int right_child = query_tree(node * 2 + 1, mid + 1, end, left, right);

    return left_child ^ right_child;
}


void update_tree(int node, int start, int end, int left, int right, int value) {
    lazy_propagation(node, start, end);

    if (right < start || end < left) return;

    if (left <= start && end <= right) {
        tree[node].lazy ^= value;
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
    
    cin >> n;

    // get element info.
    arr.resize(n);
    for (int &e : arr) cin >> e;

    // tree init. with arr
    init_tree();

    // make segement tree with arr
    make_tree(1, 0, n - 1);

    cin >> m;

    int option, left, right, value;
    while (m--) {
        cin >> option;

        if (option == 1) {
            cin >> left >> right >> value;
            update_tree(1, 0, n - 1, left, right, value);
        } else if (option == 2) {
            cin >> left >> right;
            cout << query_tree(1, 0, n - 1, left, right) << "\n";
        }
    }

    return 0;
}