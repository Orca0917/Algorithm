#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

struct QUERY {
    int start;
    int end;
    int index;
};

int N;  // 수의 개수
int K;  // 수의 최대 크기
int M;  // 쿼리의 개수

vector<int> arr;
vector<QUERY> query;
vector<int> result;
vector<pii> position(100'001, {1e9, -1});

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> N >> K;

    arr.resize(N);
    for (int &e : arr) cin >> e;

    int sqrt_N = (int)sqrt(N);
    
    cin >> M;
    result.resize(M);
    for (int i = 0; i < M; ++i) {
        int l, r; cin >> l >> r;
        query.push_back({l, r, i});
    }

    sort(query.begin(), query.end(), [sqrt_N](const QUERY &a, const QUERY &b) -> bool {
        if (a.start / sqrt_N != b.start / sqrt_N) return a.start / sqrt_N < b.start / sqrt_N;
        else return a.end < b.end;
    });

    int S = query[0].start;
    int E = query[0].end;
    int diff = 0;

    for (int i = S; i <= E; ++i) {
        position[arr[i]].first = min(position[arr[i]].first, i);
        position[arr[i]].second = max(position[arr[i]].second, i);

        if (position[arr[i]].first != 1e9 && position[arr[i]].second != -1) 
            diff = max(diff, position[arr[i]].second - position[arr[i]].first);
    }

    result[query[0].index] = diff;

    for (int i = 1; i < M; ++i) {
        while (query[i].start < S) {

        }

        while (E < query[i].end) {

        }

        while (S < query[i].start) {

        }

        while (query[i].end < E) {

        }
    }

    for (int &e : result) cout << e << "\n";

    return 0;
}