#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int N; // 수열의 크기
int M; // 쿼리의 개수

vector<int> A; // 수열
vector< vector<int> > tree; // 세그먼트 트리

// A : [left, right]
// want : [start, end]

int query_tree(int left, int right, int start, int end, int node, int search_value) {
    if (end < left || right < start) return 0;
    if (start <= left && right <= end) {
        return tree[node].end() - upper_bound(tree[node].begin(), tree[node].end(), search_value);
    }

    int mid = (left + right) / 2;
    return query_tree(left, mid, start, end, node * 2, search_value) + query_tree(mid + 1, right, start, end, node * 2 + 1, search_value);
}

void make_tree(int start, int end, int node, int idx, int val) {
    if (node < start || end < node) return;

    tree[idx].push_back(val);

    int mid = (start + end) / 2;
    if (start != end) {
        // result of each segements
        make_tree(start, mid, node, idx * 2, val);
        make_tree(mid + 1, end, node, idx * 2 + 1, val);
    }

}

void init_tree() {
    // -- decide tree size, height
    int tree_height = (int)ceil(log2(N));
    int tree_size = 1 << (tree_height + 1);
    tree.resize(tree_size);

    // -- make segment tree
    for (int i = 0; i < A.size(); ++i) {
        make_tree(0, N - 1, i, 1, A[i]);
    }

    for (int i = 1; i < tree_size; ++i) {
        sort(tree[i].begin(), tree[i].end());
    }

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    // -- input
    cin >> N;

    A.resize(N);
    for (int &a : A) cin >> a;

    // -- make tree
    init_tree();

    // -- process query
    cin >> M;
    while (M--) {
        int i, j, k; cin >> i >> j >> k;
        int result = query_tree(0, N - 1, i - 1, j - 1, 1, k);
        cout << result << "\n";
    }

    return 0;
}