#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

struct QUERY {
    int index;
    int start;
    int end;
};

int N;                  // 수열의 크기
int M;                  // 쿼리의 개수

int cnt[1'000'001];     // 숫자 i의 등장횟수
int answer[100'000];    // 정답

vector<int> A;          // 수열
vector<QUERY> Q;        // 쿼리 수열

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N;
    
    A.resize(N);
    for (int &e : A) cin >> e;

    cin >> M;

    Q.resize(M);
    for (int i = 0; i < M; ++i) {
        cin >> Q[i].start >> Q[i].end;
        Q[i].index = i;
        Q[i].start -= 1;
    }

    int sqrt_N = sqrt(N);

    sort(Q.begin(), Q.end(), [sqrt_N](const QUERY &a, const QUERY &b) -> bool {
        if (a.start / sqrt_N != b.start / sqrt_N) return a.start / sqrt_N < b.start / sqrt_N;
        else return a.end < b.end;
    });

    int uniq = 0;
    int S = Q[0].start;
    int E = Q[0].end;
    int I = Q[0].index;

    for (int i = S; i < E; ++i)
        if (cnt[A[i]]++ == 0) ++uniq;

    answer[I] = uniq;

    for (int i = 1; i < M; ++i) {
        while (Q[i].start < S) if (cnt[A[--S]]++ == 0) ++uniq;
        while (E < Q[i].end) if (cnt[A[E++]]++ == 0) ++uniq;
        while (S < Q[i].start) if (--cnt[A[S++]] == 0) --uniq;
        while (Q[i].end < E) if (--cnt[A[--E]] == 0) --uniq;

        answer[Q[i].index] = uniq;
    }

    for (int i = 0; i < M; ++i) cout << answer[i] << "\n";

    return 0;
}