#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
using namespace std;

struct Tree {
    int value;
    int lazy;
};

vector<Tree> tree;
vector<int> arr;
vector<pii> query;

int N;

void lazy_propagation(int node, int start, int end) {
    if (tree[node].lazy != 0) {
        tree[node].value = max(tree[node].value, tree[node].lazy);
        if (start != end) {
            tree[node * 2].lazy = max(tree[node * 2].lazy, tree[node].lazy);
            tree[node * 2 + 1].lazy = max(tree[node * 2 + 1].lazy, tree[node].lazy);
        }
        tree[node].lazy = 0;
    }
}

void update_tree(int node, int start, int end, int left, int right, int val) {
    lazy_propagation(node, start, end);
    if (right < start || end < left) return;
    if (left <= start && end <= right) {
        tree[node].lazy = max(tree[node].lazy, val);
        lazy_propagation(node, start, end);
        return;
    }
    int mid = (start + end) / 2;
    update_tree(node * 2, start, mid, left, right, val);
    update_tree(node * 2 + 1, mid + 1, end, left, right, val);
    tree[node].value = max(tree[node * 2].value, tree[node * 2 + 1].value);
}

int query_tree(int node, int start, int end, int left, int right) {
    lazy_propagation(node, start, end);
    if (right < start || end < left) return 0;
    if (left <= start && end <= right) return tree[node].value;
    int mid = (start + end) / 2;
    return max(query_tree(node * 2, start, mid, left, right), query_tree(node * 2 + 1, mid + 1, end, left, right));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N;

    int width, left_padding; 
    for (int i = 0; i < N; ++i) {
        cin >> width >> left_padding;
        arr.push_back(left_padding);
        arr.push_back(width + left_padding - 1);
        query.push_back({left_padding, width + left_padding - 1});
    }    

    sort(arr.begin(), arr.end());

    int n = arr.size();
    int tree_height = (int)ceil(log2(n + 1));
    int tree_size = (1 << (tree_height + 1));
    tree.resize(tree_size, {0, 0});

    int answer = 0;
    for (pii &q : query) {
        int LEFT = lower_bound(arr.begin(), arr.end(), q.first) - arr.begin();
        int RIGHT = lower_bound(arr.begin(), arr.end(), q.second) - arr.begin();
        int MH = query_tree(1, 1, 2 * N, LEFT, RIGHT);
        update_tree(1, 1, 2 * N, LEFT, RIGHT, MH + 1);
        answer = max(answer, MH + 1);
    }

    cout << answer << "\n";

    return 0;
}