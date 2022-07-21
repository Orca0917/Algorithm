#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int n;              // DVD의 수
int k;              // Query의 수

vector<pii> tree;   // 세그먼트 트리 (min, max)
vector<int> cur;    // 현재 DVD 상태

pii init_tree(int node, int start, int end) {
    if (start == end) {
        tree[node] = {start, end};
        cur[start] = start;
        return tree[node];
    }

    int mid = (start + end) / 2;
    pii L = init_tree(node * 2, start, mid);
    pii R = init_tree(node * 2 + 1, mid + 1, end);

    tree[node].first = min(L.first, R.first);
    tree[node].second = max(L.second, R.second);

    return tree[node];
}

void update_tree(int node, int start, int end, int index, int value) {
    if (index < start || end < index) return;
    if (start == end && start == index) {
        cur[start] = value;
        tree[node] = {value, value};
        return;
    }

    int mid = (start + end) / 2;
    update_tree(node * 2, start, mid, index, value);
    update_tree(node * 2 + 1, mid + 1, end, index, value);

    tree[node].first = min(tree[node * 2].first, tree[node * 2 + 1].first);
    tree[node].second = max(tree[node * 2].second, tree[node * 2 + 1].second);
}

pii query_tree(int node, int start, int end, int left, int right) {
    if (right < start || end < left) return {1e9, -1e9};
    if (left <= start && end <= right) return tree[node];

    int mid = (start + end) / 2;
    pii L = query_tree(node * 2, start, mid, left, right);
    pii R = query_tree(node * 2 + 1, mid + 1, end, left, right);

    return {min(L.first, R.first), max(L.second, R.second)};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int testcase; cin >> testcase;
    while (testcase--) {
        
        // initialize
        tree.clear();

        cin >> n >> k;

        int tree_height = (int)ceil(log2(n + 1));
        int tree_size = (1 << (tree_height + 1));
        tree.resize(tree_size);
        cur.resize(n);
        
        init_tree(1, 0, n - 1);

        int option, a, b;
        while (k--) {
            cin >> option >> a >> b;
            
            // update_tree
            if (option == 0) {
                int x = cur[a];
                int y = cur[b];

                update_tree(1, 0, n - 1, a, y);
                update_tree(1, 0, n - 1, b, x);
            }

            // query_tree
            else if (option == 1) {
                pii result = query_tree(1, 0, n - 1, a, b);
                if (a <= result.first && result.second <= b) cout << "YES\n";
                else cout << "NO\n";
            }
        }
        
    }
        
    return 0;
}