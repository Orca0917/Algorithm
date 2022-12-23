#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

int n;
vector<int> arr;
vector<int> tree;

// node가 담고있는 구간에서 가장 낮은 높이
int init_tree(int node, int start, int end) {
    if (start == end) return tree[node] = start;
    
    int mid = (start + end) >> 1;
    int L = init_tree(node << 1, start, mid);
    int R = init_tree(node << 1 | 1, mid + 1, end);
    
    if (arr[L] <= arr[R]) return tree[node] = L;
    else return tree[node] = R;
}


int query_tree(int node, int start, int end, int left, int right) {
    if (right < start || end < left) return -1;
    if (left <= start && end <= right) return tree[node];

    int mid = (start + end) >> 1;
    int L = query_tree(node << 1, start, mid, left, right);
    int R = query_tree(node << 1 | 1, mid + 1, end, left, right);

    if (L == -1) return R;
    else if (R == -1) return L;
    
    if (arr[L] <= arr[R]) return L;
    else return R;
}


ll get_max(int start, int end) {
    if (end < start) return 0;

    int idx = query_tree(1, 1, n, start, end);
    ll ret = 1LL * (end - start + 1) * arr[idx];

    return ret = max({ret, get_max(start, idx - 1), get_max(idx + 1, end)});
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n;

    int tree_height = (int)ceil(log2(n + 1));
    int tree_size = (1 << (tree_height + 1));
    tree.resize(tree_size);

    arr.resize(n + 1);
    for (int i = 1; i <= n; ++i) cin >> arr[i];

    init_tree(1, 1, n);
    cout << get_max(1, n) << "\n";

    return 0;
}