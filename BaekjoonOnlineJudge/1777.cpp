#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int n;
vector<int> tree;
vector<int> arr;
vector<int> result;

int query_tree(int node, int start, int end, int left, int right) {
    if (right < start || end < left) return 0;
    if (left <= start && end <= right) return tree[node];

    int mid = (start + end) / 2;
    return query_tree(node * 2, start, mid, left, right) + query_tree(node * 2 + 1, mid + 1, end, left, right);
}

void update_tree(int node, int start, int end, int index, int diff) {
    if (index < start || end < index) return;

    if (start == end) {
        tree[node] += diff;
    } else {
        int mid = (start + end) / 2;
        update_tree(node * 2, start, mid, index, diff);
        update_tree(node * 2 + 1, mid + 1, end, index, diff);
        tree[node] = tree[node * 2] + tree[node * 2 + 1];
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n;

    arr.resize(n);
    for (int &e : arr) cin >> e;

    result.resize(n);

    int tree_height = (int)ceil(log2(n));
    int tree_size = (1 << (tree_height + 1));
    tree.resize(tree_size, 0);

    for (int index = n - 1; index >= 0; --index) {
        int small_than_index = arr[index];
        int lo = 0, hi = n - 1, answer = 0;
        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            if (n - 1 - mid - query_tree(1, 0, n - 1, mid, n - 1) >= small_than_index) {
                answer = mid;
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }

        result[answer] = index + 1;
        update_tree(1, 0, n - 1, answer, 1);
    }

    for (int i = 0; i < n; ++i) cout << result[i] << " ";
    
    return 0;
}