#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int num2idx[100'001];
vector<int> tree;
int N;

int init_tree(int node, int start, int end) {
    if (start == end) return tree[node] = 1;

    int mid = (start + end) / 2;
    return tree[node] = init_tree(node * 2, start, mid) + \
                        init_tree(node * 2 + 1, mid + 1, end);
}

// node의 구간 : start, end
// 찾고 싶은 구간 : left, right
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
    
    cin >> N;
    for (int i = 0; i < N; ++i) {
        int x; cin >> x;
        num2idx[x] = i;
    }    

    int tree_height = (int)ceil(log2(N + 1));
    int tree_size = (1 << (tree_height + 1));
    tree.resize(tree_size);

    init_tree(1, 0, N - 1);
    
    int target_L = 1;
    int target_R = N;
    for (int i = 1; i <= N; ++i) {
        if (i % 2) {
            cout << query_tree(1, 0, N - 1, 0, num2idx[target_L]) - 1 << "\n";
            update_tree(1, 0, N - 1, num2idx[target_L], -1);
            ++target_L;
        } else {
            cout << query_tree(1, 0, N - 1, num2idx[target_R], N - 1) - 1 << "\n";
            update_tree(1, 0, N - 1, num2idx[target_R], -1);
            --target_R;
        }
    }

    return 0;
}