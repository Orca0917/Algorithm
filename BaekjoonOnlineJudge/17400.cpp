#include <bits/stdc++.h>
#define ll long long
#define pii pair<ll, ll>

using namespace std;

int n, q;
vector<int> arr;
vector<pii> tree;

pii init_tree(int node, int start, int end) {
    if (start == end) {
        if (start % 2) return tree[node] = {0, arr[start]};
        else return tree[node] = {arr[start], 0};
    }

    int mid = (start + end) >> 1;
    pii L = init_tree(node << 1, start, mid);
    pii R = init_tree(node << 1 | 1, mid + 1, end);

    return tree[node] = {L.first + R.first, L.second + R.second};
}

void update_tree(int node, int start, int end, int index, int value) {
    if (index < start || end < index) return;

    if (start != end) {
        int mid = (start + end) >> 1;
        update_tree(node << 1, start, mid, index, value);
        update_tree(node << 1 | 1, mid + 1, end, index, value);

        tree[node] = {tree[node << 1].first + tree[node << 1 | 1].first, tree[node << 1].second + tree[node << 1 | 1].second};
    }

    else {
        if (start % 2) tree[node].second += value;
        else tree[node].first += value;
    }
}

pii query_tree(int node, int start, int end, int left, int right) {
    if (right < start || end < left) return {0, 0};
    if (left <= start && end <= right) return tree[node];

    int mid = (start + end) >> 1;
    pii L = query_tree(node << 1, start, mid, left, right);
    pii R = query_tree(node << 1 | 1, mid + 1, end, left, right);

    return {L.first + R.first, L.second + R.second};
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n >> q;

    int tree_height = (int)ceil(log2(n + 1));
    int tree_size = 1 << (tree_height + 1);
    tree.resize(tree_size);
    arr.resize(n + 1);
    
    for (int i = 1; i <= n; ++i) cin >> arr[i];
    
    init_tree(1, 1, n);

    while (q--) {
        int x, y, z; cin >> x >> y >> z;
        if (x == 1) {
            pii result = query_tree(1, 1, n, y, z);
            cout << abs(result.first - result.second) << "\n";
        }

        else {
            update_tree(1, 1, n, y, z);
        }
    }
    
    return 0;
}