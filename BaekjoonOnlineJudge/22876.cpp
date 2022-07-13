#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define MAX 1'000'001

using namespace std;

int N;                          // 제비의 수

vector<pii> bird_in_x[MAX];     // bird_in_x[x] = x좌표 값이 x인 점 : bird_in_x[x] = {y, v}
vector<pii> bird_in_y[MAX];     // bird_in_y[y] = y좌표 값이 y인 점 : bird_in_y[y] = {x, v}
vector<int> tree;               // 세그먼트 트리

ll score_sum_x[MAX];              // score_sum_x[x] = x좌표 값이 x인 점들의 점수 합
ll score_sum_y[MAX];              // score_sum_y[y] = y좌표 값이 y인 점들의 점수 합


ll init_tree(int node, int start, int end, int option) {
    if (start == end) {
        if (option == 1) return tree[node] = score_sum_x[start];
        else return tree[node] = score_sum_y[start];
    }

    int mid = (start + end) / 2;
    return tree[node] = max(init_tree(node * 2, start, mid, option), init_tree(node * 2 + 1, mid + 1, end, option));
}


ll update_tree(int node, int start, int end, int idx, int val) {
    if (idx < start || end < idx) return tree[node];
    if (start == end) return tree[node] += val;

    int mid = (start + end) / 2;
    ll L = update_tree(node * 2, start, mid, idx, val);
    ll R = update_tree(node * 2 + 1, mid + 1, end, idx, val);
    return tree[node] = max(L, R);
}


int find_max_index(int node, int start, int end, int value) {
    if (start == end) return start;
    
    int mid = (start + end) / 2;
    if (tree[node * 2] == value) return find_max_index(node * 2, start, mid, value);
    else if (tree[node * 2 + 1] == value) return find_max_index(node * 2 + 1, mid + 1, end, value);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    // 입력
    cin >> N;

    for (int i = 0; i < N; ++i) {
        int x, y, v; cin >> x >> y >> v;

        bird_in_x[x].push_back({y, v});
        bird_in_y[y].push_back({x, v});

        score_sum_x[x] += v;
        score_sum_y[y] += v;
    }

    // 트리의 크기 설정
    int tree_height = (int)ceil(log2(MAX));
    int tree_size = (1 << (tree_height + 1));
    tree.resize(tree_size, 0);

    ll answer = 0;
    
    // 가로1 + 세로2
    init_tree(1, 0, MAX - 1, 1);
    for (int ypos = 0; ypos < MAX; ++ypos) {
        if (bird_in_y[ypos].empty()) continue;
        ll current_score = score_sum_y[ypos];

        for (pii e : bird_in_y[ypos]) update_tree(1, 0, MAX - 1, e.first, -e.second);

        int recover_this = tree[1];

        current_score += tree[1];
        int max_idx = find_max_index(1, 0, MAX - 1, tree[1]);
        update_tree(1, 0, MAX - 1, max_idx, -tree[1]);

        current_score += tree[1];

        answer = max(answer, current_score);

        update_tree(1, 0, MAX - 1, max_idx, recover_this);
        for (pii e : bird_in_y[ypos]) update_tree(1, 0, MAX - 1, e.first, e.second);
    }

    // 세로1 + 가로2
    init_tree(1, 0, MAX - 1, 2);
    for (int xpos = 0; xpos < MAX; ++xpos) {
        if (bird_in_x[xpos].empty()) continue;
        ll current_score = score_sum_x[xpos];

        for (pii e : bird_in_x[xpos]) update_tree(1, 0, MAX - 1, e.first, -e.second);

        ll recover_this = tree[1];
        current_score += tree[1];

        int max_idx = find_max_index(1, 0, MAX - 1, tree[1]);
        update_tree(1, 0, MAX - 1, max_idx, -tree[1]);

        current_score += tree[1];

        answer = max(answer, current_score);

        update_tree(1, 0, MAX - 1, max_idx, recover_this);
        for (pii e : bird_in_x[xpos]) update_tree(1, 0, MAX - 1, e.first, e.second);
    }

    // 가로3 or 세로3 을 위해 점수 정렬 (내림차순)
    sort(score_sum_x, score_sum_x + MAX, [](const ll a, const ll b) { return a > b; });
    sort(score_sum_y, score_sum_y + MAX, [](const ll a, const ll b) { return a > b; });

    // 가로 3번 & 세로 3번
    answer = max(answer, score_sum_x[0] + score_sum_x[1] + score_sum_x[2]);
    answer = max(answer, score_sum_y[0] + score_sum_y[1] + score_sum_y[2]);

    cout << answer << "\n";

    return 0;
}