#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int N; // 도시의 수
int C; // 수도의 번호
int Q; // 쿼리의 수

vector<ll> tree;
vector<int> adj[200'001];

int left_range[200'001];
int right_range[200'001];
int depth[200'001];

void dfs(int here, int parent, int dep, int &num) {
    depth[here] = dep;
    left_range[here] = ++num;
    for (int there : adj[here]) {
        if (there == parent) continue;
        dfs(there, here, dep + 1, num);
    }
    right_range[here] = num;
}

void update_tree(int node, int start, int end, int index) {
    if (index < start || end < index) return;

    tree[node] += 1;

    if (start == end) return;

    int mid = (start + end) / 2;

    update_tree(node * 2, start, mid, index);
    update_tree(node * 2 + 1, mid + 1, end, index);    
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

    cin >> N >> C;
    for (int i = 0; i < N - 1; ++i) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int tree_height = (int)ceil(log2(N));
    int tree_size = 1 << (tree_height + 1);
    tree.resize(tree_size, 0);

    int num = 0;
    dfs(C, C, 1, num);

    cin >> Q;
    int option, A;
    while (Q--) {
        cin >> option >> A;

        // 1 A : A도시에 물을 채운다.
        if (option == 1) {
            update_tree(1, left_range[C], right_range[C], left_range[A]);
        }

        // 2 A : 현재 A도시에 얼마만큼의 물이 채워져 있는지 출력하라.
        else if (option == 2) {
            cout << 1LL * query_tree(1, left_range[C], right_range[C], left_range[A], right_range[A]) * depth[A] << "\n";
        }
    }


    return 0;
}