#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int N;  // 순열의 길이
vector<int> arr;
vector<ll> tree;
vector<int> m(100'000, 0);

ll query_tree(int node, int start, int end, int left, int right) {
    if (right < start || end < left) return 0;
    if (left <= start && end <= right) return tree[node];

    int mid = (start + end) / 2;
    ll L = query_tree(node * 2, start, mid, left, right);
    ll R = query_tree(node * 2 + 1, mid + 1, end, left, right);

    return L + R;
}

void update_tree(int node, int start, int end, int index) {
    if (index < start || end < index) return;

    tree[node] += 1;
    if (start == end) return;

    int mid = (start + end) / 2;
    update_tree(node * 2, start, mid, index);
    update_tree(node * 2 + 1, mid + 1, end, index);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int testcase; cin >> testcase;
    while (testcase--) {
        cin >> N;

        arr.clear();
        arr.resize(N);
        for (int i = 0; i < N; ++i) {
            int k; cin >> k;
            m[k] = i + 1;
        }
        for (int i = 0; i < N; ++i) cin >> arr[i];

        tree.clear();
        int tree_height = (int)ceil(log2(N + 1));
        int tree_size = (1 << (tree_height + 1));
        tree.resize(tree_size, 0);

        ll answer = 0;
        for (int i = 0; i < N; ++i) {
            answer += query_tree(1, 1, N, m[arr[i]] + 1, N);
            update_tree(1, 1, N, m[arr[i]]);
        }

        cout << answer << "\n";
    }
    
    return 0;
}