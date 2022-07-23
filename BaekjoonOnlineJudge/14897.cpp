#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

struct QUERY {
    int start;
    int end;
    int index;
};

int N;                  // 배열의 크기
int Q;                  // 쿼리의 개수

vector<int> arr;        // 수열
vector<int> result;     // 쿼리 결과
vector<int> cnt;        // 값의 등장 횟수를 저장
vector<QUERY> query;    // 쿼리 목록

map<int, int> m;        // 값 압축에 사용

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N;

    arr.resize(N);
    for (int &e : arr) cin >> e;

    // 값 압축 진행
    int num = 0;
    for (int &e : arr) {
        if (m.find(e) == m.end()) m[e] = num++;
        e = m[e];
    }

    cin >> Q;
    for (int i = 0; i < Q; ++i) {
        int l, r; cin >> l >> r;
        query.push_back({l - 1, r - 1, i});
    }

    int sqrt_N = (int)sqrt(N);
    sort(query.begin(), query.end(), [sqrt_N](const QUERY &a, const QUERY &b) -> bool {
        if (a.start / sqrt_N != b.start / sqrt_N) return a.start / sqrt_N < b.start / sqrt_N;
        else return a.end < b.end;
    });

    result.resize(Q);
    cnt.resize(1'000'001, 0);
    int S = query[0].start;
    int E = query[0].end;
    int uniq = 0;
    
    for (int i = S; i <= E; ++i) {
        if (cnt[arr[i]] == 0) ++uniq;
        ++cnt[arr[i]]; 
    }

    result[query[0].index] = uniq;

    for (int i = 1; i < Q; ++i) {
        while (S < query[i].start) if (--cnt[arr[S++]] == 0) --uniq;
        while (E < query[i].end) if (cnt[arr[++E]]++ == 0) ++uniq;
        while (query[i].start < S) if (cnt[arr[--S]]++ == 0) ++uniq;
        while (query[i].end < E) if (--cnt[arr[E--]] == 0) --uniq;

        result[query[i].index] = uniq;
    }

    for (int i = 0; i < Q; ++i) cout << result[i] << "\n";
    return 0;
}