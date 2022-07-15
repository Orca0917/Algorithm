#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

struct SCORE {
    int t1;
    int t2;
    int t3;
};

int N; // 학생의 수
int ranks;

vector<int> tree;
vector<SCORE> arr;

int query_tree(int node, int start, int end, int left, int right) {
    if (right < start || end < left) return 1e9;
    if (left <= start && end <= right) return tree[node];

    int mid = (start + end) / 2;
    int L = query_tree(node * 2, start, mid, left, right);
    int R = query_tree(node * 2 + 1, mid + 1, end, left, right);
    return min(L, R);
}

int update_tree(int node, int start, int end, int index, int val) {
    if (index < start || end < index) return tree[node];
    if (start == end) return tree[node] = val;

    int mid = (start + end) / 2;
    int L = update_tree(node * 2, start, mid, index, val);
    int R = update_tree(node * 2 + 1, mid + 1, end, index, val);
    return tree[node] = min(L, R);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N;

    arr.resize(N + 1, {0, 0, 0});
    for (int i = 1; i <= N; ++i) { cin >> ranks; arr[ranks].t1 = i; }
    for (int i = 1; i <= N; ++i) { cin >> ranks; arr[ranks].t2 = i; }
    for (int i = 1; i <= N; ++i) { cin >> ranks; arr[ranks].t3 = i; }

    sort(arr.begin(), arr.end(), [](const SCORE &a, const SCORE &b) { return a.t1 < b.t1; });

    int tree_height = (int)ceil(log2(N + 1));
    int tree_size = (1 << (tree_height + 1));
    tree.resize(tree_size, 1e9);

    int answer = 0;
    for (int i = 1; i <= N; ++i) {
        int result = query_tree(1, 1, N, 1, arr[i].t2);
        if (result > arr[i].t3) ++answer;
        update_tree(1, 1, N, arr[i].t2, arr[i].t3);
    }

    cout << answer << "\n";

    return 0;
}