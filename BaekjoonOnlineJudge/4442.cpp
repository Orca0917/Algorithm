#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

map<string, int> m;
vector<int> tree;
int n;

int query_tree(int node, int start, int end, int left, int right) {
    if (right < start || end < left) return 0;
    if (left <= start && end <= right) return tree[node];

    int mid = (start + end) / 2;
    return query_tree(node * 2, start, mid, left, right) + \
            query_tree(node * 2 + 1, mid + 1, end, left, right);
}


void update_tree(int node, int start, int end, int index, int diff) {
    if (index < start || end < index) return;
    tree[node] += diff;
    if (start != end) {
        int mid = (start + end) / 2;
        update_tree(node * 2, start, mid, index, diff);
        update_tree(node * 2 + 1, mid + 1, end, index, diff);
    }
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    

    while (cin >> n && n) {
        tree.clear();
        m.clear();

        for (int i = 0; i < n; ++i) {
            string s; cin >> s;
            m[s] = i;
        }

        int tree_height = (int)ceil(log2(n));
        int tree_size = (1 << (tree_height + 1));
        tree.resize(tree_size);

        ll answer = 0;
        for (int i = 0; i < n; ++i) {
            string s; cin >> s;
            answer += query_tree(1, 0, n - 1, m[s], n - 1);
            update_tree(1, 0, n - 1, m[s], 1);
        }

        cout << answer << "\n";
    }
    
    
    return 0;
}