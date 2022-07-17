#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define MAX 30000

using namespace std;

struct COORD {
    int x = 0, y1 = 0, y2 = 0;
    bool is_start = false;
};

int N;
vector<COORD> arr;
vector<int> tree, cnt;

int init_tree(int node, int start, int end) {
    if (start == end) return tree[node] = 0;

    int mid = (start + end) / 2;
    int L = init_tree(node * 2, start, mid);
    int R = init_tree(node * 2 + 1, mid + 1, end);

    return tree[node] = L + R;
}

void update_tree(int node, int start, int end, int left, int right, int value) {
    if (right < start || end < left) return;
    if (left <= start && end <= right) cnt[node] += value;
    else {
        int mid = (start + end) / 2;
        update_tree(node * 2, start, mid, left, right, value);
        update_tree(node * 2 + 1, mid + 1, end, left, right, value);
    }

    if (cnt[node] != 0) tree[node] = end - start + 1;
    else {
        if (start == end) tree[node] = 0;
        else tree[node] = tree[node * 2] + tree[node * 2 + 1];
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N;
    
    for (int i = 0; i < N; ++i) {
        int x1, x2, y1, y2; cin >> x1 >> y1 >> x2 >> y2;

        arr.push_back({x1, y1, y2, true});
        arr.push_back({x2, y1, y2, false});
    }

    sort(arr.begin(), arr.end(), [](const COORD &a,  const COORD &b) -> bool {
        return a.x < b.x;
    });

    int tree_height = (int)ceil(log2(MAX + 1));
    int tree_size = 1 << (tree_height + 1);
    tree.resize(tree_size);
    cnt.resize(tree_size);

    init_tree(1, 0, MAX);

    ll answer = 0;
    for (int i = 0; i < 2 * N; ++i) {
        if (i > 0) {
            int diff = arr[i].x - arr[i - 1].x;
            int area = diff * tree[1];
            answer += area;
        }

        int value = arr[i].is_start == true ? 1 : -1;
        update_tree(1, 0, MAX, arr[i].y1, arr[i].y2 - 1, value);
    }

    cout << answer << "\n";


    return 0;
}