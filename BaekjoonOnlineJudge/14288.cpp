#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define MAX 100'001
#define DOWN 1
#define UP -1

using namespace std;

struct Tree {
    int value;
    int lazy;
};

int n, m; // 직원의 수(n), 쿼리의 수(m)
vector<Tree> tree_down, tree_up;
vector<int> under_boss[MAX];
int left_range[MAX], right_range[MAX];
int direction = DOWN;
int num = 0;

void dfs(int here, int parent) {
    left_range[here] = ++num;
    for (int there : under_boss[here]) {
        if (there == parent) continue;
        dfs(there, here);
    }
    right_range[here] = num;
}

void init_tree(vector<Tree> &tree, int node, int start, int end) {
    if (start == end) {
        tree[node].value = 0;
        tree[node].lazy = 0;
        return;
    }

    int mid = (start + end) / 2;
    init_tree(tree, node * 2, start, mid);
    init_tree(tree, node * 2 + 1, mid + 1, end);
}

void lazy_propagation(vector<Tree> &tree, int node, int start, int end) {

    if (tree[node].lazy != 0) {
        tree[node].value += tree[node].lazy * (end - start + 1);

        if (start != end) {
            tree[node * 2].lazy += tree[node].lazy;
            tree[node * 2 + 1].lazy += tree[node].lazy;
        }

        tree[node].lazy = 0;
    }

}


void update_tree(vector<Tree> &tree, int node, int start, int end, int left, int right, int value) {

    lazy_propagation(tree, node, start, end);

    if (right < start || end < left) return;
    if (left <= start && end <= right) {
        tree[node].lazy += value;
        lazy_propagation(tree, node, start, end);
        return;
    }

    int mid = (start + end) / 2;
    update_tree(tree, node * 2, start, mid, left, right, value);
    update_tree(tree, node * 2 + 1, mid + 1, end, left, right, value);
    tree[node].value = tree[node * 2].value + tree[node * 2 + 1].value;
    
}

int query_tree(vector<Tree> &tree, int node, int start, int end, int left, int right) {

    lazy_propagation(tree, node, start, end);

    if (right < start || end < left) return 0;
    if (left <= start && end <= right) return tree[node].value;

    int mid = (start + end) / 2;
    return query_tree(tree, node * 2, start, mid, left, right) + query_tree(tree, node * 2 + 1, mid + 1, end, left, right);
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    memset(left_range, 0, sizeof(left_range));
    memset(right_range, 0, sizeof(right_range));

    cin >> n >> m;

    // boss 아래에 누가 있는지 연결 리스트로 생성
    for (int person = 1; person <= n; ++person) {
        int boss; cin >> boss;
        if (boss == -1) continue;
        under_boss[boss].push_back(person);
    }

    int order_num = 0;
    dfs(1, order_num);

    int tree_height = (int)ceil(log2(n));
    int tree_size = (1 << (tree_height + 1));
    tree_down.resize(tree_size);
    tree_up.resize(tree_size);

    init_tree(tree_down, 1, 1, n);
    init_tree(tree_up, 1, 1, n);

    while (m--) {
        int option; cin >> option;
        if (option == 1) {
            int person, value; cin >> person >> value;
            if (direction == DOWN)
                update_tree(tree_down, 1, 1, n, left_range[person], right_range[person], value);
            else
                update_tree(tree_up, 1, 1, n, left_range[person], left_range[person], value);
        }

        else if (option == 2) {
            int person; cin >> person;
            int res1 = query_tree(tree_down, 1, 1, n, left_range[person], left_range[person]);
            int res2 = query_tree(tree_up, 1, 1, n, left_range[person], right_range[person]);
            cout << res1 + res2 << "\n";
        }

        else if (option == 3) {
            direction *= -1;
        }
    }

    return 0;
}