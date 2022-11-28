#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int n;
vector<int> arr, tree;
vector<ll> psum;
ll max_size = 0;
pii answer;

int init_tree(int node, int start, int end) {
    if (start == end) return tree[node] = start;
    int mid = (start + end) / 2;
    int L = init_tree(node * 2, start, mid);
    int R = init_tree(node * 2 + 1, mid + 1, end);

    if (arr[L] <= arr[R]) return tree[node] = L;
    else return tree[node] = R;
}


int query_tree(int node, int start, int end, int left, int right) {
    if (right < start || end < left) return -1;
    if (left <= start && end <= right) return tree[node];

    int mid = (start + end) / 2;
    int L = query_tree(node * 2, start, mid, left, right);
    int R = query_tree(node * 2 + 1, mid + 1, end, left, right);

    if (L == -1) return R;
    if (R == -1) return L;

    if (arr[L] <= arr[R]) return L;
    else return R;
}


ll search_area(int start, int end) {
    if (end < start) return 0;

    // index를 기준으로 탐색
    ll len = 0;
    if (start == 0) len = psum[end];
    else len = psum[end] - psum[start - 1];

    int index = query_tree(1, 0, n - 1, start, end);
    ll area = 1LL * len * arr[index];

    if (max_size < area) {
        max_size = area;
        answer = {start, end};
    }

    area = search_area(start, index - 1);
    if (max_size < area) {
        max_size = area;
        answer = {start, index - 1};
    }

    area = search_area(index + 1, end);
    if (max_size < area) {
        max_size = area;
        answer = {index + 1, end};
    }

    return max_size;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n;
    int tree_height = (int)ceil(log2(n));
    int tree_size = (1 << (1 + tree_height));
    
    tree.resize(tree_size);
    arr.resize(n);
    psum.resize(n);

    for (int i = 0; i < n; ++i) cin >> arr[i];

    psum[0] = arr[0];
    for (int i = 1; i < n; ++i) {
        psum[i] = psum[i - 1] + arr[i];
    }

    init_tree(1, 0, n - 1);
    cout << search_area(0, n - 1) << "\n";
    cout << answer.first + 1 << " " << answer.second + 1 << "\n";
    
    return 0;
}