#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

vector<int> tree, arr;
int n;

int init_tree(int node, int start, int end) {
    if (start == end) return tree[node] = start;
    int mid = (start + end) / 2;

    int L = init_tree(node * 2, start, mid);
    int R = init_tree(node * 2 + 1, mid + 1, end);

    if (arr[L] <= arr[R]) return tree[node] = L;
    else return tree[node] = R;
}

ll query_tree(int node, int start, int end, int left, int right) {
    if (right < start || end < left) return -1;
    if (left <= start && end <= right) return tree[node];

    int mid = (start + end) / 2;
    ll L = query_tree(node * 2, start, mid, left, right);
    ll R = query_tree(node * 2 + 1, mid + 1, end, left, right);

    if (L == -1) return R;
    else if (R == -1) return L;
    else if (arr[L] <= arr[R]) return L;
    else return R;
}


ll find_tree(int start, int end) {
    int min_v = query_tree(1, 0, n - 1, start, end);
    ll area = 1LL * (end - start + 1) * arr[min_v];

    if (start < min_v)
        area = max(area, find_tree(start, min_v - 1));

    if (min_v < end)
        area = max(area, find_tree(min_v + 1, end));

    return area;
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
    cout << find_tree(0, n - 1) << "\n";
    return 0;
}