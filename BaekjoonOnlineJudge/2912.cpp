#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

struct QUERY {
    int start;
    int end;
    int index;
};

int N; // 난쟁이의 수
int C; // 모자의 색상 수
int M; // 쿼리의 수

vector<vector<int>> tree;
vector<int> arr;
vector<QUERY> query;

int cnt[10001];
int result[30001];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> N >> C;

    arr.resize(N + 1);
    for (int i = 0; i < N; ++i) cin >> arr[i];
    int sqrt_N = (int)sqrt(N);

    cin >> M;
    query.resize(M);
    for (int i = 0; i < M; ++i) {
        int s, e; cin >> s >> e;
        query[i] = {s - 1, e - 1, i};
    }

    sort(query.begin(), query.end(), [sqrt_N](const QUERY &a, const QUERY &b) -> bool {
        if (a.start / sqrt_N != b.start / sqrt_N) return a.start / sqrt_N < b.start / sqrt_N;
        else return a.end < b.end;
    });

    memset(cnt, 0, sizeof(cnt));
    memset(result, 0 ,sizeof(result));
    
    int max_color = 0;
    int S = query[0].start;
    int E = query[0].end;

    for (int i = S; i <= E; ++i) cnt[arr[i]]++;
    for (int i = 1; i <= C; ++i) if (cnt[max_color] < cnt[i]) max_color = i;
    result[query[0].index] = cnt[max_color] <= (E - S + 1) / 2 ? 0 : max_color;

    for (int i = 1; i < M; ++i) {
        while (query[i].start < S) ++cnt[arr[--S]];
        while (E < query[i].end) ++cnt[arr[++E]];
        while (S < query[i].start) --cnt[arr[S++]];
        while (query[i].end < E) --cnt[arr[E--]];

        max_color = 0;
        for (int j = 1; j <= C; ++j) if (cnt[max_color] < cnt[j]) max_color = j;
        
        int mid = (E - S + 1) / 2;
        if (cnt[max_color] <= mid) result[query[i].index] = 0;
        else result[query[i].index] = max_color;
    }

    for (int i = 0; i < M; ++i) {
        if (result[i] == 0) cout << "no\n";
        else cout << "yes " << result[i] << "\n";
    }

    return 0;
}