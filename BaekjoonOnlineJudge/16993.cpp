#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define INF (int)1e9

using namespace std;

struct Node {
    int m;
    int s;
    int e;
};

int n, q; 
vector<Node> tree;
vector<int> arr, psum;

Node init_tree(int node, int start, int end) {
    if (start == end) {
        return tree[node] = {arr[start], arr[start], arr[start]};
    }

    int mid = start + end >> 1;
    Node &left = tree[node * 2];
    Node &right = tree[node * 2 + 1];
    Node &now = tree[node];

    now = {-INF, -INF, -INF};

    int left_sum = 0;
    for (int i = end; i >= start; --i) {
        left_sum += arr[i];
        now.s = max(now.s, left_sum);
    }

    int right_sum = 0;
    for (int i = start; i <= end; ++i) {
        right_sum += arr[i];
        now.e = max(now.e, right_sum);
    }

    Node L = init_tree(node * 2, start, mid);
    Node R = init_tree(node * 2 + 1, mid + 1, end);

    now.m = max({L.m, R.m, L.s + R.e});

    return now;
}


Node query_tree(int node, int start, int end, int left, int right) {
    if (right < start || end < left) return {-INF, -INF, -INF};
    if (left <= start && end <= right) return tree[node];

    int mid = start + end >> 1;
    Node L = query_tree(node * 2, start, mid, left, right);
    Node R = query_tree(node * 2 + 1, mid + 1, end, left, right);

    Node ret;
    ret.s = max(L.s + psum[end] - psum[mid], R.s);
    ret.e = max(L.e, R.e + psum[mid] - psum[start - 1]);
    ret.m = max({L.m, R.m, L.s + R.e});

    return ret;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n;

    int tree_size = (int)ceil(log2(n + 1));
    int tree_height = (1 << (tree_size + 1));
    tree.resize(tree_height);

    arr.resize(n + 1, 0);
    psum.resize(n + 1, 0);

    for (int i = 1; i <= n; ++i) cin >> arr[i];
    for (int i = 1; i <= n; ++i) psum[i] = psum[i - 1] + arr[i];

    init_tree(1, 1, n);

    cin >> q;

    while (q--) {
        int x, y; cin >> x >> y;
        cout << query_tree(1, 1, n, x, y).m << "\n";
    }
    
    return 0;
}