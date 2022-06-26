#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define MAX 100001
using namespace std;

struct Tree {
    int value;
    int lazy;
};

int n, m; // 회사 직원의 수(n), 쿼리의 개수(m)
vector<int> under_boss[MAX];
vector<Tree> tree;
int left_range[MAX], right_range[MAX];

void init_tree(int node, int start, int end) {
    if (start == end) {
        tree[node].value = 0;
        tree[node].lazy = 0;
        return;
    }

    int mid = (start + end) / 2;
    init_tree(node * 2, start, mid);
    init_tree(node * 2 + 1, mid + 1, end);
}

void lazy_propagation(int node, int start, int end) {
    // 전파할 lazy가 남아 있는 경우
    if (tree[node].lazy != 0) {
        tree[node].value += tree[node].lazy;

        if (start != end) {    
            // 자식들에게 전파
            tree[node * 2].lazy += tree[node].lazy;
            tree[node * 2 + 1].lazy += tree[node].lazy;
        }

        tree[node].lazy = 0;
    }
}

void update_tree(int node, int start, int end, int left, int right, int value) {
    
    lazy_propagation(node, start, end);

    if (right < start || end < left) return;
    if (left <= start && end <= right) {
        tree[node].value += value;
        if (start != end) {
            tree[node * 2].lazy += value;
            tree[node * 2 + 1].lazy += value;
        }
        return;
    }

    int mid = (start + end) / 2;
    update_tree(node * 2, start, mid, left, right, value);
    update_tree(node * 2 + 1, mid + 1, end, left, right, value);
}

int query_tree(int node, int start, int end, int person) {

    lazy_propagation(node, start, end);

    if (person < start || end < person) return 0;
    if (start == end) return tree[node].value;

    int mid = (start + end) / 2;
    return query_tree(node * 2, start, mid, person) + query_tree(node * 2 + 1, mid + 1, end, person);
}

void dfs(int node, int &num) {
    left_range[node] = ++num;
    for (int there : under_boss[node])
        dfs(there, num);
    right_range[node] = num;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> m;

    for (int person = 1; person <= n; ++person) {
        int boss; cin >> boss;
        if (boss == -1) continue; // 직속 상사가 없는 경우
        under_boss[boss].push_back(person);
    }

    // dfs 를 통해 사원의 번호를 다시 매긴다.
    int reorder_num = 0;
    dfs(1, reorder_num);

    // 세그먼트 트리 생성
    int tree_height = (int)ceil(log2(n));
    int tree_size = (1 << (tree_height + 1));
    tree.resize(tree_size);

    // 세그먼트 트리 초기화
    init_tree(1, 1, n);

    // 쿼리 수행
    while (m--) {
        int option; cin >> option;
        if (option == 1) {
            // 칭찬을 받는 경우 (내리 칭찬)
            int person, value; cin >> person >> value;
            update_tree(1, 1, n, left_range[person], right_range[person], value);
        } else {
            // 직원의 칭찬 수치 출력
            int person; cin >> person;
            cout << query_tree(1, 1, n, left_range[person]) << "\n";
        }
    }
    
    return 0;
}