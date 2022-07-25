#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

struct QUERY {
    int start;
    int end;
    int index;
};

int N;  // 집의 개수
int Q;  // 쿼리의 개수

vector<int> arr;
vector<int> cnt;
vector<int> max_cnt;
vector<int> result;
vector<QUERY> query;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> N >> Q;

    arr.resize(N);
    for (int &e : arr) {
        cin >> e;
        e += 100'000;
    }

    cnt.resize(200'001);
    max_cnt.resize(200'001);
    result.resize(100'001);

    for (int i = 0; i < Q; ++i) {
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

    for (int i = 1; i < Q; ++i) {
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

    for (int i = 0; i < Q; ++i) 
        cout << result[i] << "\n";

    return 0;
}