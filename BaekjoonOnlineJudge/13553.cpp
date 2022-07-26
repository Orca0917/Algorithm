#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

struct QUERY {
    int start;
    int end;
    int index;
};

int N;                  // 수열의 크기
int K;                  // 절댓값의 차이 K 이하인 것의 수
int M;                  // 쿼리의 수

vector<ll> tree;
vector<int> arr;
vector<QUERY> query;
vector<ll> result;

void update_tree(int node, int value) {
    while (node <= 100'000) {
        tree[node] += value;
        node += (node & -node);
    }
}

ll query_tree(int node) {
    ll ret = 0;
    if (node < 1) return 0;
    if (node > 100'000) node = 100'000;

    while (node > 0) {
        ret += tree[node];
        node -= (node & -node);
    }

    return ret;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> N >> K;

    arr.resize(N + 1);
    for (int i = 1; i <= N; ++i) cin >> arr[i];

    tree.resize(100'001, 0);

    cin >> M;
    result.resize(M);
    for (int i = 0; i < M; ++i) {
        int left, right; cin >> left >> right;
        query.push_back({left, right, i});
    }

    int sqrt_N = (int)sqrt(N);
    sort(query.begin(), query.end(), [sqrt_N](const QUERY &a, const QUERY &b) -> bool {
        if (a.start / sqrt_N != b.start / sqrt_N) return a.start / sqrt_N < b.start / sqrt_N;
        else return a.end < b.end;
    });

    int S = query[0].start;
    int E = S - 1;

    ll ret = 0;

    for (int i = 0; i < M; ++i) {

        while (S < query[i].start) {
            update_tree(arr[S], -1);
            ret -= query_tree(arr[S] + K) - query_tree(arr[S] - K - 1);
            ++S;
        }

        while (query[i].end < E) {
            update_tree(arr[E], -1);
            ret -= query_tree(arr[E] + K) - query_tree(arr[E] - K - 1);
            --E;
        }

        while (query[i].start < S) {
            --S;
            ret += query_tree(arr[S] + K) - query_tree(arr[S] - K - 1);
            update_tree(arr[S], 1);
        }

        while (E < query[i].end) {
            ++E;
            ret += query_tree(arr[E] + K) - query_tree(arr[E] - K - 1);
            update_tree(arr[E], 1);
        }

        result[query[i].index] = ret;
    }

    for (ll e : result) cout << e << "\n";

    return 0;
}