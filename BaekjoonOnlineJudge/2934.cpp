#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

struct Tree {
    ll value;
    ll lazy;
};

vector<Tree> tree;
vector<ll> arr;

int N; // 식물을 심은 날의 수

ll init_tree(int node, int start, int end) {
    if (start == end) return tree[node].value = 0LL;

    int mid = (start + end) / 2;
    return tree[node].value = init_tree(node * 2, start, mid) + init_tree(node * 2 + 1, mid + 1, end);
}

void lazy_propagation(int node, int start, int end) {
    if (tree[node].lazy != 0LL) {
        tree[node].value += tree[node].lazy;

        if (start != end) {
            tree[node * 2].lazy += tree[node].lazy;
            tree[node * 2 + 1].lazy += tree[node].lazy;
        }

        tree[node].lazy = 0LL;
    }
}

void update_tree(int node, int start, int end, int left, int right, int value) {

    lazy_propagation(node, start, end);

    if (right < start || end < left) return;
    if (left <= start && end <= right) {
        tree[node].lazy += value;
        lazy_propagation(node, start, end);
        return;
    }

    int mid = (start + end) / 2;
    update_tree(node * 2, start, mid, left, right, value);
    update_tree(node * 2 + 1, mid + 1, end, left, right, value);
    tree[node].value = tree[node * 2].value + tree[node * 2 + 1].value;
}

ll query_tree(int node, int start, int end, int left, int right) {

    lazy_propagation(node, start, end);

    if (right < start || end < left) return 0LL;
    if (left <= start && end <= right) return tree[node].value;

    int mid = (start + end) / 2;
    return query_tree(node * 2, start, mid, left, right) + query_tree(node * 2 + 1, mid + 1, end, left, right);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N;

    int tree_height = (int)ceil(log2(100'001));
    int tree_size = (1 << (tree_height + 1));
    tree.resize(tree_size, {0LL, 0LL});
    arr.resize(100'001, 0LL);

    init_tree(1, 1, 100'000);

    while (N--) {
        int L, R; cin >> L >> R;

        ll ret_L = query_tree(1, 1, 100'000, L, L);
        ll ret_R = query_tree(1, 1, 100'000, R, R);

        // 피는 꽃의 수 계산
        cout << ret_L + ret_R << "\n";

        // arr값 초기화 (그날 핀 꽃의 수 초기화)
        update_tree(1, 1, 100'000, L, L, -ret_L);
        update_tree(1, 1, 100'000, R, R, -ret_R);

        // 사이에 식물을 심기
        update_tree(1, 1, 100'000, L + 1, R - 1, 1);
    }

    return 0;
}