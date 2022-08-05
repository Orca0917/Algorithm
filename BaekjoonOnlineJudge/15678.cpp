#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

int N, D;
vector<ll> arr(1'000'000, 0);
vector<ll> tree;
ll memo[100001];

ll find_tree(int node, int start, int end, int left, int right) {
    if (right < start || end < left) return 0;
    if (left <= start && end <= right) return tree[node];

    int mid = (start + end) / 2;
    ll L = find_tree(node * 2, start, mid, left, right);
    ll R = find_tree(node * 2 + 1, mid + 1, end, left, right);

    return max(L, R);
}

void update_tree(int node, int start, int end, int index, ll value) {
    if (index < start || end < index) return;

    tree[node] = max(tree[node], value);
    if (start == end) return;

    int mid = (start + end) / 2;
    update_tree(node * 2, start, mid, index, value);
    update_tree(node * 2 + 1, mid + 1, end, index, value);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> N >> D;

    for (int i = 0; i < N; ++i) cin >> arr[i];
    
    int tree_height = (int)ceil(log2(N));
    int tree_size = 1 << (tree_height + 1);
    tree.resize(tree_size, 0LL);

    memset(memo, 0LL, sizeof(memo));
    
    for (int i = 0; i < N; ++i) {
        memo[i] = arr[i];
        memo[i] = max(memo[i], arr[i] + find_tree(1, 0, N - 1, max(0, i - D), i - 1));
        update_tree(1, 0, N - 1, i, memo[i]);
    }

    ll answer = -1e9;
    for (int i = 0; i < N; ++i) answer = max(answer, memo[i]);

    cout << answer << "\n";

    return 0;
}