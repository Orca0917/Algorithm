#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int N; // 홍준이가 뛰는 코스의 길이
int M; // 홍준이의 시야 범위

vector<int> tree;
vector<int> arr;

int init_tree(int node, int start, int end) {
    if (start == end) return tree[node] = arr[start];
    int mid = (start + end) / 2;
    return tree[node] = max(init_tree(node * 2, start, mid), init_tree(node * 2 + 1, mid + 1, end));
}

int query_tree(int node, int start, int end, int left, int right) {
    if (right < start || end < left) return 0;
    if (left <= start && end <= right) return tree[node];

    int mid = (start + end) / 2;
    return max(query_tree(node * 2, start, mid, left, right), query_tree(node * 2 + 1, mid + 1, end, left, right));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> N >> M;

    int tree_height = (int)ceil(log2(N + 1));
    int tree_size = 1 << (tree_height + 1);
    tree.resize(tree_size);

    arr.resize(N + 1);
    for (int i = 1; i <= N; ++i) cin >> arr[i];

    init_tree(1, 1, N);

    for (int i = M; i <= N - M + 1; ++i) {
        cout << query_tree(1, 1, N, i - M + 1, i + M - 1) << " ";
    }
    cout << "\n";
    
    return 0;
}