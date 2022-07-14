#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int n; // 배열의 크기
int m; // 함수 Q를 호출한 횟수

vector<vector<int>> tree;
vector<int> a;

vector<int> init_tree(int node, int start, int end) {
    if (start == end) {
        tree[node].push_back(a[start]);
        return tree[node];
    }

    int mid = (start + end) / 2;
    vector<int> L = init_tree(node * 2, start, mid);
    vector<int> R = init_tree(node * 2 + 1, mid + 1, end);

    tree[node].resize(L.size() + R.size());
    merge(L.begin(), L.end(), R.begin(), R.end(), tree[node].begin());
    return tree[node];
}

int query(int node, int start, int end, int left, int right, int value) {
    if (right < start || end < left) return 0;
    if (left <= start && end <= right) {
        auto it = upper_bound(tree[node].begin(), tree[node].end(), value);
        return it - tree[node].begin();
    }

    int mid = (start + end) / 2;
    int L = query(node * 2, start, mid, left, right, value);
    int R = query(node * 2 + 1, mid + 1, end, left, right, value);
    return L + R;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n >> m;

    a.resize(n + 1);
    for (int i = 1; i <= n; ++i) cin >> a[i];

    int tree_height = (int)ceil(log2(n + 1));
    int tree_size = (1 << (tree_height + 1));
    tree.resize(tree_size);

    init_tree(1, 1, n);

    while (m--) {
        int l, r, k; cin >> l >> r >> k;
        int lo = -1e9, hi = 1e9;

        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            if (query(1, 1, n, l, r, mid) < k) {
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }

        cout << lo << "\n";
    }

    return 0;
}