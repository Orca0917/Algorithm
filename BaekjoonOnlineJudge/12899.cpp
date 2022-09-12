#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define MAX 2'000'000

using namespace std;

vector<int> tree;

void insert_tree(int node, int start, int end, int x) {
    if (start == end) {
        tree[node] += 1;
        return;
    }

    int mid = (start + end) / 2;
    
    if (x <= mid) insert_tree(node * 2, start, mid, x);
    else insert_tree(node * 2 + 1, mid + 1, end, x);

    tree[node] = tree[node * 2] + tree[node * 2 + 1];
}


int update_tree(int node, int start, int end, int x) {
    if (start == end) {
        tree[node] -= 1;
        return start;
    }

    int mid = (start + end) / 2;
    int ret;

    if (x <= tree[node * 2]) ret = update_tree(node * 2, start, mid, x);
    else ret = update_tree(node * 2 + 1, mid + 1, end, x - tree[node * 2]);

    tree[node] = tree[node * 2] + tree[node * 2 + 1];
    return ret;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n; cin >> n;

    int tree_height = (int)ceil(log2(MAX + 1));
    int tree_size = 1 << (tree_height + 1);
    tree.resize(tree_size, 0);

    while (n--) {
        int option, x; cin >> option >> x;

        if (option == 1) {
            insert_tree(1, 1, MAX, x);
        } else if (option == 2) {
            cout << update_tree(1, 1, MAX, x) << "\n";
        }
    }
    
    return 0;
}