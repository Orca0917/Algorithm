#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

struct QUERY {
    int start;
    int end;
    int index;
};

int N;                          // 수열의 길이
int M;                          // 쿼리의 길이

vector<int> arr;                // 수열
vector<int> cnt(200'001, 0);    // 수의 등장횟수 계산
vector<int> max_cnt(200'001, 0);// max인 수의 개수
vector<int> result(100'001);    // 쿼리의 결과 출력
vector<QUERY> query;            // 쿼리

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> N >> M;

    arr.resize(N);
    for (int &e : arr) {
        cin >> e;
        e += 100'000;
    }

    for (int i = 0; i < M; ++i) {
        int l, r; cin >> l >> r;
        query.push_back({l - 1, r - 1, i});
    }

    int sqrt_N = (int)sqrt(N);

    sort(query.begin(), query.end(), [sqrt_N](const QUERY &a, const QUERY &b) -> bool {
        if (a.start / sqrt_N != b.start / sqrt_N) return a.start / sqrt_N < b.start / sqrt_N;
        else return a.end < b.end;
    });

    int S = query[0].start;
    int E = query[0].end;
    int freq = 0;

    for (int i = S; i <= E; ++i) {
        if (max_cnt[cnt[arr[i]]] > 0) --max_cnt[cnt[arr[i]]];
        ++cnt[arr[i]];
        ++max_cnt[cnt[arr[i]]];
        freq = max(freq, cnt[arr[i]]);
    }

    result[query[0].index] = freq;

    for (int i = 1; i < M; ++i) {
        while (query[i].start < S) {
            --max_cnt[cnt[arr[--S]]];
            ++cnt[arr[S]];
            ++max_cnt[cnt[arr[S]]];
            freq = max(freq, cnt[arr[S]]);
        }
        while (E < query[i].end) {
            --max_cnt[cnt[arr[++E]]];
            ++cnt[arr[E]];
            ++max_cnt[cnt[arr[E]]];
            freq = max(freq, cnt[arr[E]]);
        }
        while (S < query[i].start) {
            --max_cnt[cnt[arr[S]]];
            --cnt[arr[S]];
            ++max_cnt[cnt[arr[S++]]];
        }
        while (query[i].end < E) {
            --max_cnt[cnt[arr[E]]];
            --cnt[arr[E]];
            ++max_cnt[cnt[arr[E--]]];
        }

        while (max_cnt[freq] == 0) --freq;
        result[query[i].index] = freq;
    }

    for (int i = 0; i < M; ++i) cout << result[i] << "\n";

    return 0;
}