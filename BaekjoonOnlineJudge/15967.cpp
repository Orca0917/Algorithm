#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int n, q1, q2;

vector<pair<ll, ll>> tree;
vector<int> arr;

void propagate(int node, int start, int end) {
    if (tree[node].second != 0) {
        tree[node].first += (end - start + 1) * tree[node].second;
        if (start != end) {
            tree[node << 1].second += tree[node].second;
            tree[node << 1 | 1].second += tree[node].second;
        }
        tree[node].second = 0;
    }
}

void update(int node, int start, int end, int left, int right, ll val) {
    propagate(node, start, end);

    if (right < start || end < left) return;
    if (left <= start && end <= right) {
        tree[node].second = val;
        propagate(node, start, end);
        return;
    }

    int mid = start + end >> 1;
    update(node << 1, start, mid, left, right, val);
    update(node << 1 | 1, mid + 1, end, left, right, val);
    tree[node].first = tree[node << 1].first + tree[node << 1 | 1].first;
}

ll query(int node, int start, int end, int left, int right) {
    propagate(node, start, end);

    if (right < start || end < left) return 0;
    if (left <= start && end <= right) return tree[node].first;

    int mid = start + end >> 1;
    return query(node << 1, start, mid, left, right) + query(node << 1 | 1, mid + 1, end, left, right);
}

ll init(int node, int start, int end) {
    if (start == end) {
        tree[node].first = arr[start];
        tree[node].second = 0;
        return tree[node].first;
    }

    int mid = start + end >> 1;
    return tree[node].first = init(node << 1, start, mid) + init(node << 1 | 1, mid + 1, end);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n >> q1 >> q2;

    arr.resize(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> arr[i];
    }    

    int tree_height = (int)ceil(log2(n + 1));
    int tree_size = (1 << (tree_height + 1));
    tree.resize(tree_size);

    init(1, 1, n);

    for (int i = 0; i < q1 + q2; ++i) {
        int cmd, u, v, l; cin >> cmd >> u >> v;
        if (cmd == 1) cout << query(1, 1, n, u, v) << "\n";
        else if (cmd == 2) cin >> l, update(1, 1, n, u, v, l);
    }

    return 0;
}