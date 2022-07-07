#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int n; // 별이 떨어지는 점의 수
int q; // 쿼리의 수

struct Tree {
    int value;
    int lazy;
};

vector<Tree> tree;
vector<int> arr;

void lazy_propagation(int node, int start, int end) {
    if (tree[node].lazy != 0) {
        tree[node].value += (end - start + 1) * tree[node].lazy;

        if (start != end) {
            tree[node * 2].lazy += tree[node].lazy;
            tree[node * 2 + 1].lazy += tree[node].lazy;
        }

        tree[node].lazy = 0;
    }
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
    
    cin >> n;

    arr.resize(n + 1);
    for (int i = 1; i <= n; ++i) cin >> arr[i];

    int tree_height = (int)ceil(log2(n + 1));
    int tree_size = (1 << (tree_height + 1));
    tree.resize(tree_size);

    for (int i = 1; i <= n; ++i) update_tree(1, 1, n, i, i, arr[i] - arr[i - 1]);

    cin >> q;

    while (q--) {
        int option; cin >> option;

        if (option == 1) {
            int L, R; cin >> L >> R;
            update_tree(1, 1, n, L, R, 1);
            update_tree(1, 1, n, R + 1, R + 1, -(R - L + 1));
        }

        else if (option == 2) {
            int X; cin >> X;
            cout << query_tree(1, 1, n, 1, X) << "\n";
        }
    }

    return 0;
}