#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int N, T, Q; // 집의 개수 / 색의 개수 / 작업의 개수

struct Tree {
    int value = 1;
    int lazy = 0;
};

vector<Tree> tree;

// 트리의 정보 초기화
int init_tree(int node, int start, int end) {
    if (start == end) {
        tree[node].value = (1 << 1);
        tree[node].lazy = 0;
        return tree[node].value;
    }

    int mid = (start + end) / 2;
    return tree[node].value = init_tree(node * 2, start, mid) | init_tree(node * 2 + 1, mid + 1, end);
}

void lazy_propagation(int node, int start, int end) {

    // 전파할 lazy 값이 있는지 확인
    if (tree[node].lazy != 0) {
        tree[node].value = tree[node].lazy;

        // 자식이 있는 경우, 자식에게 lazy 값을 전파
        if (start != end) {
            tree[node * 2].lazy = tree[node].lazy;
            tree[node * 2 + 1].lazy = tree[node].lazy;
        }

        // 전파된 현재 노드의 lazy 값 제거
        tree[node].lazy = 0;
    }
}


void update_tree(int node, int start, int end, int left, int right, int value) {
    lazy_propagation(node, start, end);

    if (right < start || end < left) return;

    if (left <= start && end <= right) {
        // 현재 노드에 lazy 값을 추가하고 1차 전파
        tree[node].lazy = value;
        lazy_propagation(node, start, end);
        return;
    }

    int mid = (start + end) / 2;
    update_tree(node * 2, start, mid, left, right, value);
    update_tree(node * 2 + 1, mid + 1, end, left, right, value);

    tree[node].value = tree[node * 2].value | tree[node * 2 + 1].value;
}

int query_tree(int node, int start, int end, int left, int right) {

    lazy_propagation(node, start, end);

    if (right < start || end < left) return 0;
    if (left <= start && end <= right) return tree[node].value;

    int mid = (start + end) / 2;
    int left_child = query_tree(node * 2, start, mid, left, right);
    int right_child = query_tree(node * 2 + 1, mid + 1, end, left, right);
    return left_child | right_child;
}

int get_on_bits(int bits) {
    int ret = 0;
    while (bits) {
        int bit = bits & 1;
        ret += bit;

        bits >>= 1;
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> T >> Q;

    // 트리의 크기 재설정
    int tree_height = (int)ceil(log2(N + 1));
    int tree_size = (1 << (tree_height + 1));
    tree.resize(tree_size);

    // 트리 초기 설정 진행
    init_tree(1, 1, N);

    // Q개의 질의 진행
    while (Q--) {
        char option; cin >> option;

        // C x y z : [x, y] 구간의 집들을 z색으로 변경
        if (option == 'C') {
            int x, y, z; cin >> x >> y >> z;
            if (x > y) swap(x, y);
            update_tree(1, 1, N, x, y, (1 << z));
        }

        // Q x y : [x, y] 구간의 집들에 존재하는 색의 가짓수 출력
        else if (option == 'Q') {
            int x, y; cin >> x >> y;
            if (x > y) swap(x, y);
            int bits = query_tree(1, 1, N, x, y);
            cout << get_on_bits(bits) << "\n";
        }
    }

    return 0;
}