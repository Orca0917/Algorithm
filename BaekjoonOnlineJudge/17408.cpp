#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int n, m;
vector<pii> tree;
vector<int> arr;

pii get_top2(pii L, pii R) {
    vector<int> v;
    v.push_back(L.first);
    v.push_back(L.second);
    v.push_back(R.first);
    v.push_back(R.second);
    sort(v.begin(), v.end());
    return {v[3], v[2]};
}

pii init_tree(int node, int start, int end) {
    if (start == end) return tree[node] = {arr[start], 0};
    int mid = (start + end) / 2;
    pii L = init_tree(node * 2, start, mid);
    pii R = init_tree(node * 2 + 1, mid + 1, end);
    return tree[node] = get_top2(L, R);    
}

void update_tree(int node, int start, int end, int index, int value) {
    if (index < start || end < index) return;

    if (start != end) {
        int mid = (start + end) / 2;
        update_tree(node * 2, start, mid, index, value);
        update_tree(node * 2 + 1, mid + 1, end, index, value);
        tree[node] = get_top2(tree[node * 2], tree[node * 2 + 1]);
    } else {
        tree[node] = {value, 0};
    }
}

pii query_tree(int node, int start, int end, int left, int right) {
    if (right < start || end < left) return {0, 0};
    if (left <= start && end <= right) return tree[node];

    int mid = (start + end) / 2;
    pii L = query_tree(node * 2, start, mid, left, right);
    pii R = query_tree(node * 2 + 1, mid + 1, end, left, right);
    
    return get_top2(L, R);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    // 수열의 크기 입력
    cin >> n;
    
    // 수열 입력
    arr.resize(n);
    for (int &e : arr) cin >> e;

    // 트리 설정
    int tree_height = (int)ceil(log2(n));
    int tree_size = (1 << (tree_height + 1));
    tree.resize(tree_size);

    // 트리 초기화
    init_tree(1, 0, n - 1);

    // 쿼리 수행
    cin >> m;

    while (m--) {
        int op, x, y; cin >> op >> x >> y;
        if (op == 1) {
            update_tree(1, 0, n - 1, x - 1, y);
        } else {
            pii res = query_tree(1, 0, n - 1, x - 1, y - 1);
            cout << res.first + res.second << "\n";
        }
    }

    return 0;
}