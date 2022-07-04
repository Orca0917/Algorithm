#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

struct Tree {
    int value;
    int lazy;
};

vector<Tree> tree;
vector<int> acc_sum;
string s;

int M; // 쿼리의 개수

int init_tree(int node, int start, int end) {
    if (start == end) {
        return tree[node].value = acc_sum[start];
    }

    int mid = (start + end) / 2;
    int left_child = init_tree(node * 2, start, mid);
    int right_child = init_tree(node * 2 + 1, mid + 1, end);

    return tree[node].value = min(left_child, right_child);
}

void lazy_propagation(int node, int start, int end) {

    if (tree[node].lazy != 0) {

        tree[node].value += tree[node].lazy;

        if (start != end) {
            tree[node * 2].lazy += tree[node].lazy;
            tree[node * 2 + 1].lazy += tree[node].lazy;
        }

        tree[node].lazy = 0;
    }
}

int update_tree(int node, int start, int end, int left, int right, int value) {

    lazy_propagation(node, start, end);

    if (right < start || end < left) return tree[node].value;
    if (left <= start && end <= right) {
        tree[node].lazy += value;
        lazy_propagation(node, start, end);
        return tree[node].value;
    }

    int mid = (start + end) / 2;
    int left_child = update_tree(node * 2, start, mid, left, right, value);
    int right_child = update_tree(node * 2 + 1, mid + 1, end, left, right, value);

    return tree[node].value = min(left_child, right_child);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    // 초기 괄호문자열의 상태, 쿼리의 개수 입력
    cin >> s >> M;

    // 괄호 문자열의 누적합 생성
    int value = 0;
    for (char &c : s) {
        if (c == ')') value = -1, ++RIGHT;
        else if (c == '(') value = 1, ++LEFT;

        if (acc_sum.empty()) acc_sum.push_back(value);
        else acc_sum.push_back(acc_sum.back() + value);
    }

    // 트리의 크기 정보 설정
    int N = s.length();
    int tree_height = (int)ceil(log2(N));
    int tree_size = (1 << (tree_height + 1));
    tree.resize(tree_size);

    // 트리 초기화
    init_tree(1, 0, N - 1);

    int answer = 0, val = 0, tot = acc_sum.back();
    while (M--) {
        int x; cin >> x; --x;

        if (s[x] == '(') val = -2;
        else if (s[x] == ')') val = 2;

        s[x] = s[x] ^ ('(' ^ ')');
        tot += val;

        update_tree(1, 0, N - 1, x, N - 1, val);

        if (tot == 0 && tree[1].value == 0) ++answer;
    }

    cout << answer << "\n";

    return 0;
}