#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define MAX 500'001
using namespace std;

struct Tree {
    ll value;
    ll lazy;
};

vector<Tree> tree;
vector<ll> salary, order, subordinate[MAX];
int left_range[MAX], right_range[MAX];

void reorder_nodes(int here, int &index) {
    left_range[here] = ++index;
    for (int there : subordinate[here])
        reorder_nodes(there, index);
    right_range[here] = index;
}

void lazy_propagate(int node, int start, int end) {
    if (tree[node].lazy != 0) {
        tree[node].value += tree[node].lazy;
        if (start != end) {
            tree[node * 2].lazy += tree[node].lazy;
            tree[node * 2 + 1].lazy += tree[node].lazy;
        }
        tree[node].lazy = 0;
    }
}

void init_tree(int node, int start, int end) {
    if (start == end) {
        tree[node].value = order[start];
        return;
    }

    int mid = (start + end) / 2;
    init_tree(node * 2, start, mid);
    init_tree(node * 2 + 1, mid + 1, end);
}

void update_tree(int node, int start, int end, int LEFT, int RIGHT, ll value) {
    lazy_propagate(node, start, end);

    if (RIGHT < start || end < LEFT) return;
    if (LEFT <= start && end <= RIGHT) {
        tree[node].value += value;
        if (start != end) {
            tree[node * 2].lazy += value;
            tree[node * 2 + 1].lazy += value;
        }
        return;
    }

    int mid = (start + end) / 2;
    update_tree(node * 2, start, mid, LEFT, RIGHT, value);
    update_tree(node * 2 + 1, mid + 1, end, LEFT, RIGHT, value);
}

ll query_tree(int node, int start, int end, int index) {
    lazy_propagate(node, start, end);

    if (index < start || end < index) return 0;
    if (start == end) return tree[node].value;

    int mid = (start + end) / 2;
    return query_tree(node * 2, start, mid, index) + query_tree(node * 2 + 1, mid + 1, end, index);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    // 직원의 수(n), 쿼리의 수(m)
    int n, m; cin >> n >> m;

    salary.resize(n + 1);
    order.resize(n + 1);

    // 사장이라서 상사가 존재하지 않음
    cin >> salary[1];

    // 각 직원마다 급여와 상사의 번호 입력
    int boss;
    for (int employee = 2; employee <= n; ++employee) {
        cin >> salary[employee] >> boss;
        subordinate[boss].push_back(employee);
    }

    // 노드의 번호 재설정
    int order_idx = 0;
    reorder_nodes(1, order_idx);
    for (int employee = 1; employee <= n; ++employee) {
        order[left_range[employee]] = salary[employee];
    }

    // segment tree size 설정
    int tree_height = (int)ceil(log2(n));
    int tree_size = (1 << (tree_height + 1));
    tree.resize(tree_size);

    init_tree(1, 1, n);

    while (m--) {
        char option; cin >> option;
        if (option == 'p') {
            int a, x; cin >> a >> x;
            update_tree(1, 1, n, left_range[a] + 1, right_range[a], x);
        }

        else if (option == 'u') {
            int a; cin >> a;
            ll result = query_tree(1, 1, n, left_range[a]);
            cout << result << "\n";
        }
    }
    return 0;
}