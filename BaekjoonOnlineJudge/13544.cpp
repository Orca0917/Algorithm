#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int n, m;
vector<int> A, tree[1 << 18];
int max_size = 1 << 17;

void _add(int node, int value) {
    node = node | max_size;
    tree[node].push_back(value);
}

void _make_tree() {
    for (int i = 1; i <= n; ++i) _add(i, A[i - 1]);
    for (int i = max_size - 1; i > 0; --i) {
        vector<int> &left_child = tree[i * 2];
        vector<int> &right_child = tree[i * 2 + 1];
        tree[i].resize(left_child.size() + right_child.size());

        merge(left_child.begin(), left_child.end(), right_child.begin(), right_child.end(), tree[i].begin());
    }
}

int _query(int i, int j, int k) {
    i = i | max_size;
    j = j | max_size;

    int ret = 0;
    while (i <= j) {
        if (i & 1) {
            ret += tree[i].end() - upper_bound(tree[i].begin(), tree[i].end(), k);
            ++i;
        }

        if (~j & 1) {
            ret += tree[j].end() - upper_bound(tree[j].begin(), tree[j].end(), k);
            --j;
        }

        i = i >> 1;
        j = j >> 1;
    }

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n;
    A.resize(n);
    for (int &e : A) cin >> e;

    _make_tree();

    for (int i = 1; i < (1 << 18); ++i) {
        sort(tree[i].begin(), tree[i].end());
    }

    cin >> m;
    int prev_answer = 0;
    while (m--) {
        int a, b, c; cin >> a >> b >> c;
        int left = a ^ prev_answer;
        int right = b ^ prev_answer;
        int k = c ^ prev_answer;
        prev_answer = _query(left, right, k);
        cout << prev_answer << "\n";
    }
    return 0;
}