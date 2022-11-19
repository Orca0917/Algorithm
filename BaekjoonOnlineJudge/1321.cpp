#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

vector<ll> tree;
vector<int> arr;
int n, m;

ll init_tree(int node, int start, int end) {
    if (start == end) return tree[node] = arr[start];

    int mid = (start + end) / 2;
    return tree[node] = init_tree(node * 2, start, mid) + \
                        init_tree(node * 2 + 1, mid + 1, end);
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

ll query_tree(int node, int start, int end, int left, int right) {
    if (right < start || end < left) return 0;
    if (left <= start && end <= right) return tree[node];

    int mid = (start + end) / 2;
    return query_tree(node * 2, start, mid, left, right) + \
           query_tree(node * 2 + 1, mid + 1, end, left, right);
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n;

    arr.resize(n);
    for (int &e : arr) cin >> e;

    int tree_height = (int)ceil(log2(n));
    int tree_size = (1 << (tree_height + 1));
    tree.resize(tree_size);

    init_tree(1, 0, n - 1);

    cin >> m;
    while (m--) {
        int op, x, y;
        cin >> op;

        if (op == 1) {
            cin >> x >> y;
            update_tree(1, 0, n - 1, x - 1, y);
        }

        else if (op == 2) {
            cin >> x;

            int lo = 0, hi = n - 1, answer = 0;
            while (lo <= hi) {
                int mid = (lo + hi) / 2;
                ll result = query_tree(1, 0, n - 1, 0, mid);
                if (result >= x) {
                    answer = mid;
                    hi = mid - 1;
                } else {
                    lo = mid + 1;
                }
            }
            cout << answer + 1 << "\n";
        }
    }
    
    return 0;
}