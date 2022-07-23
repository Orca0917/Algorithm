#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

struct QUERY {
    int start;
    int end;
    int index;
};

int N; // 배열의 크기
int T; // 부분 배열의 개수 (쿼리의 수)

vector<QUERY> query;
vector<int> arr;

int cnt[1'000'001];
ll result[100'001];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> N >> T;

    arr.resize(N);
    for (int &e : arr) cin >> e;

    for (int i = 0; i < T; ++i) {
        int l, r; cin >> l >> r;
        query.push_back({l - 1, r - 1, i});
    }    

    int sqrt_N = (int)sqrt(N);
    sort(query.begin(), query.end(), [sqrt_N](const QUERY &a, const QUERY &b) -> bool {
        if (a.start / sqrt_N != b.start / sqrt_N) return a.start / sqrt_N < b.start / sqrt_N;
        else return a.end < b.end;
    });
    
    memset(cnt, 0, sizeof(cnt));

    int S = query[0].start;
    int E = query[0].end;
    ll P = 0;

    int min_v = 1e9;
    int max_v = 0;

    for (int i = S; i <= E; ++i) {
        ++cnt[arr[i]];
        min_v = min(min_v, arr[i]);
        max_v = max(max_v, arr[i]);   
    }

    for (int i = min_v; i <= max_v; ++i) P += 1LL * cnt[i] * cnt[i] * i;

    result[query[0].index] = P;

    for (int i = 1; i < T; ++i) {
        while (query[i].start < S) {
            ++cnt[arr[--S]];
            int now_cnt = cnt[arr[S]];
            int prev_cnt = now_cnt - 1;
            P += 1LL * ((now_cnt * now_cnt) - (prev_cnt * prev_cnt)) * arr[S];
        }
        while (E < query[i].end) {
            ++cnt[arr[++E]];
            int now_cnt = cnt[arr[E]];
            int prev_cnt = now_cnt - 1;
            P += 1LL * ((now_cnt * now_cnt) - (prev_cnt * prev_cnt)) * arr[E];
        }
        while (S < query[i].start) {
            --cnt[arr[S++]];
            int now_cnt = cnt[arr[S - 1]];
            int prev_cnt = now_cnt + 1;
            P += 1LL * ((now_cnt * now_cnt) - (prev_cnt * prev_cnt)) * arr[S - 1];
        }
        while (query[i].end < E) {
            --cnt[arr[E--]];
            int now_cnt = cnt[arr[E + 1]];
            int prev_cnt = now_cnt + 1;
            P += 1LL * ((now_cnt * now_cnt) - (prev_cnt * prev_cnt)) * arr[E + 1];
        }

        result[query[i].index] = P;
    }

    for (int i = 0; i < T; ++i) 
        cout << result[i] << "\n";
    
    return 0;
}