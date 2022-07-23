#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int N;                      // 줄을 서 있는 사람의 수
int tree_height;            // 세그먼트 트리의 높이
int tree_size;              // 세그먼트 트리의 크기

vector<int> tree;           // 세그먼트 트리 (합)
vector<int> heights;        // 키 정보 (중복 존재)
vector<int> query;          // 쿼리 정보
vector<int> answer;         // 최종 정답


int init_tree(int node, int start, int end) {
    if (start == end) return tree[node] = 1;

    int mid = (start + end) / 2;
    int L = init_tree(node * 2, start, mid);
    int R = init_tree(node * 2 + 1, mid + 1, end);
    return tree[node] = L + R;
}


void update_tree(int node, int start, int end, int index, int value) {
    tree[node] -= 1;

    if (start == end) {
        answer[index] = heights[start];
        return;
    }

    int mid = (start + end) / 2;
    if (value <= tree[node * 2]) update_tree(node * 2, start, mid, index, value);
    else update_tree(node * 2 + 1, mid + 1, end, index, value - tree[node * 2]);
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> N;

    heights.resize(N);
    query.resize(N);
    answer.resize(N, 0);

    for (int &e : heights) cin >> e;
    for (int &e : query) cin >> e;

    sort(heights.begin(), heights.end());

    tree_height = (int)ceil(log2(N));
    tree_size = 1 << (tree_height + 1);
    tree.resize(tree_size, 0);

    init_tree(1, 0, N - 1);

    for (int i = N - 1; i >= 0; --i) update_tree(1, 0, N - 1, i, query[i] + 1);
    for (int e : answer) cout << e << "\n";

    return 0;
}