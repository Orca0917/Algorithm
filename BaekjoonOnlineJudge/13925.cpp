#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define MOD 1'000'000'007
using namespace std;

struct Tree {
    ll value = 0;
    ll lazy_add = 0;
    ll lazy_mul = 1;
};

int n, m;
vector<Tree> tree;
vector<int> arr;

ll init_tree(int node, int start, int end) {
    if (start == end) {
        return tree[node].value = arr[start];
    }

    int mid = (start + end) / 2;
    tree[node].value = init_tree(node * 2, start, mid) + init_tree(node * 2 + 1, mid + 1, end);
    return tree[node].value %= MOD;
}

void lazy_propagation(int node, int start, int end) {
    if (tree[node].lazy_add != 0 || tree[node].lazy_mul != 1) {

        tree[node].value = tree[node].lazy_mul * tree[node].value + (end - start + 1) * tree[node].lazy_add;
        tree[node].value %= MOD;

        if (start != end) {
            tree[node * 2].lazy_mul = (tree[node * 2].lazy_mul * tree[node].lazy_mul) % MOD;
            tree[node * 2 + 1].lazy_mul = (tree[node * 2 + 1].lazy_mul * tree[node].lazy_mul) % MOD;

            tree[node * 2].lazy_add = (tree[node * 2].lazy_add * tree[node].lazy_mul + tree[node].lazy_add) % MOD;
            tree[node * 2 + 1].lazy_add = (tree[node * 2 + 1].lazy_add * tree[node].lazy_mul + tree[node].lazy_add) % MOD;
        }

        tree[node].lazy_add = 0;
        tree[node].lazy_mul = 1;
    }
}

void update_tree(int node, int start, int end, int left, int right, int mul, int add) {

    lazy_propagation(node, start, end);

    if (right < start || end < left) return;
    if (left <= start && end <= right) {
        tree[node].lazy_mul = mul;
        tree[node].lazy_add = add;
        lazy_propagation(node, start, end);
        return;
    }

    int mid = (start + end) / 2;
    update_tree(node * 2, start, mid, left, right, mul, add);
    update_tree(node * 2 + 1, mid + 1, end, left, right, mul, add);

    tree[node].value = (tree[node * 2].value + tree[node * 2 + 1].value) % MOD;
}

ll query_tree(int node, int start, int end, int left, int right) {

    lazy_propagation(node, start, end);

    if (right < start || end < left) return 0;
    if (left <= start && end <= right) return tree[node].value;

    int mid = (start + end) / 2;
    return (query_tree(node * 2, start, mid, left, right) + query_tree(node * 2 + 1, mid + 1, end, left, right)) % MOD;
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

    int option, x, y, v;
    while(m--) {
        cin >> option;

        // 1 x y v: Ai = (Ai + v) % MOD를 수행한다. (x ≤ i ≤ y)
        if (option == 1) {
            cin >> x >> y >> v;
            --x, --y;
            update_tree(1, 0, n - 1, x, y, 1, v);
        } 

        // 2 x y v: Ai = (Ai × v) % MOD를 수행한다. (x ≤ i ≤ y)
        else if (option == 2) {
            cin >> x >> y >> v;
            --x, --y;
            update_tree(1, 0, n - 1, x, y, v, 0);
        } 

        // 3 x y v: Ai = v를 수행한다. (x ≤ i ≤ y)
        else if (option == 3) {
            cin >> x >> y >> v;
            --x, --y;
            update_tree(1, 0, n - 1, x, y, 0, v);
        } 

        // 4 x y: (ΣAi) % MOD를 출력한다. (x ≤ i ≤ y)
        else if (option == 4) {
            cin >> x >> y;
            --x, --y;
            cout << query_tree(1, 0, n - 1, x, y) << "\n";
        }
    }
    return 0;
}