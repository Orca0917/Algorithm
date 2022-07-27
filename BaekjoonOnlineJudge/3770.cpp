#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int N;      // 동해안 도시의 수
int M;      // 서해안 도시의 수
int K;      // 고속도로의 수

vector<ll> tree;
vector<pii> arr;

void update_tree(int node, int start, int end, int index, int value) {
    if (index < start || end < index) return;
    
    tree[node] += value;
    if (start == end) return;

    int mid = (start + end) / 2;
    update_tree(node * 2, start, mid, index, value);
    update_tree(node * 2 + 1, mid + 1, end, index, value);
}


ll query_tree(int node, int start, int end, int left, int right) {
    if (right < start || end < left) return 0;
    if (left <= start && end <= right) return tree[node];

    int mid = (start + end) / 2;
    ll L = query_tree(node * 2, start, mid, left, right);
    ll R = query_tree(node * 2 + 1, mid + 1, end, left, right);

    return L + R;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int testcase; cin >> testcase;
    int tc = 0;
    while (testcase--) {

        // init variables
        tree.clear();
        arr.clear();

        cin >> N >> M >> K;

        for (int i = 0; i < K; ++i) {
            int left, right; cin >> left >> right;
            arr.push_back({left, right});
        }

        sort(arr.begin(), arr.end(), [](const pii &a, const pii &b) -> bool {
            if (a.first == b.first) return a.second < b.second;
            return a.first < b.first;
        });

        int tree_height = (int)ceil(log2(M + 1));
        int tree_size = (1 << (tree_height + 1));
        tree.resize(tree_size, 0);

        ll answer = 0;
        for (int i = 0; i < K; ++i) {
            answer += query_tree(1, 1, M, arr[i].second + 1, M);
            update_tree(1, 1, M, arr[i].second, 1);
        }

        cout << "Test case " << ++tc << ": " << answer << "\n";
    }

    return 0;
}