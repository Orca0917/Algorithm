#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define MAX 400'000
#define PREFIX 200'000
#define MOD 1'000'000'007
using namespace std;

vector<pii> sorted_coord;
vector<ll> tree;
int n;

void update_tree(int node, int start, int end, int index, int diff) {
    if (index < start || end < index) return;

    tree[node] += diff;

    if (start != end) {
        int mid = (start + end) / 2;
        update_tree(node * 2, start, mid, index, diff);
        update_tree(node * 2 + 1, mid + 1, end, index, diff);
    }
}


ll query_tree(int node, int start, int end, int left, int right) {
    if (right < start || end < left) return 0;
    if (left <= start && end <= right) return tree[node];

    int mid = (start + end) / 2;
    ll L = query_tree(node * 2, start, mid, left, right);
    ll R = query_tree(node * 2 + 1, mid + 1, end, left, right);
    return (L + R) % MOD;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int tree_height = (int)ceil(log2(MAX));
    int tree_size = (1 << (tree_height + 1));
    tree.resize(tree_size, 0);

    cin >> n;
    for (int i = 0; i < n; ++i) {
        int x, y; cin >> x >> y;
        sorted_coord.push_back({x + PREFIX, y + PREFIX});
        update_tree(1, 0, MAX, x + PREFIX, 1);
    }

    sort(sorted_coord.begin(), sorted_coord.end(), [](const pii &a, const pii &b) -> bool {
        if (a.second == b.second) return a.first < b.first;
        return a.second < b.second;
    });

    ll answer = 0;
    int prev_y = -1;
    for (int std = 0; std < n; ++std) {
        if (prev_y < sorted_coord[std].second) {
            prev_y = sorted_coord[std].second;
            for (int j = std; j < n && sorted_coord[j].second == prev_y; ++j)
                update_tree(1, 0, MAX, sorted_coord[j].first, -1);
        }

        ll L = query_tree(1, 0, MAX, 0, sorted_coord[std].first - 1);
        ll R = query_tree(1, 0, MAX, sorted_coord[std].first + 1, MAX);
        answer += (L * R) % MOD;
        answer %= MOD;
    }

    cout << answer << "\n";
    
    return 0;
}