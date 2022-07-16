#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define MOD 1'000'000'007

using namespace std;

int N; // 나무의 개수
const int max_coord = 200'000 - 1;

vector<pair<ll, int>> tree;   // merge-sort tree
vector<int> x;      // 나무를 심을 위치


pair<ll, int> update_tree(int node, int start, int end, int index) {
    if (index < start || end < index) return tree[node];
    if (start == end) {
        tree[node].first += index;
        tree[node].second += 1;
        return tree[node];
    }

    int mid = (start + end) / 2;
    pair<ll, int> L = update_tree(node * 2, start, mid, index);
    pair<ll, int> R = update_tree(node * 2 + 1, mid + 1, end, index);

    return tree[node] = {L.first + R.first, L.second + R.second};
}

pair<ll, int> query_tree(int node, int start, int end, int left, int right) {
    if (right < start || end < left) return {0, 0};
    if (left <= start && end <= right) return tree[node];

    int mid = (start + end) / 2;
    pair<ll, int> L = query_tree(node * 2, start, mid, left, right);
    pair<ll, int> R = query_tree(node * 2 + 1, mid + 1, end, left, right);

    return tree[node] = {L.first + R.first, L.second + R.second};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N;

    int tree_height = (int)ceil(log2(max_coord + 1));
    int tree_size = 1 << (tree_height + 1);
    tree.resize(tree_size, {0LL, 0});

    x.resize(N);
    for (int &e : x) cin >> e;

    ll answer = 1;
    update_tree(1, 0, max_coord, x[0]); // 첫번째 나무를 심는 것은 무료

    for (int i = 1; i < N; ++i) {
        pair<ll, int> L = query_tree(1, 0, max_coord, 0, max(x[i] - 1, 0));
        pair<ll, int> R = query_tree(1, 0, max_coord, min(x[i] + 1, max_coord), max_coord);

        ll left_ret = L.second * x[i] - L.first;
        ll right_ret = R.first - x[i] * R.second;

        ll result = (left_ret + right_ret) % MOD;

        answer *= result;
        answer %= MOD;

        update_tree(1, 0, max_coord, x[i]);
    }    

    cout << answer << "\n";
    
    return 0;
}