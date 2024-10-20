#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

int N; // 풍선을 담당하는 스태프의 수
int A[1'000'000]; // 각 스태프가 풍선 하나를 만드는데 걸리는 시간
int M; // 만들어야하는 풍선의 수

bool is_possible(ll max_time) {
    ll count = 0;
    
    for (int i = 0; i < N; ++i) {
        // i 번째 사람이 max_time 동안 만들 수 있는 풍선의 수
        count += max_time / A[i];
    }

    // max_time 동안 M개 이상 만들 수 있는지 확인
    return count >= 1LL * M;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    // 스태프의 수와 풍선의 개수를 입력
    cin >> N >> M;

    // 각 스태프들이 풍선 하나를 만드는 데 걸린 시간
    for (int i = 0; i < N; ++i) cin >> A[i];

    // 이분탐색 구간 설정
    // 최대: 1명이 1개를 만드는데 1e6분 * 1e6개 만드는 경우
    ll lo = 0, hi = 1e12;
    ll answer = hi;

    while (lo <= hi) {
        ll mid = (lo + hi) / 2;
        if (is_possible(mid)) {
            answer = mid;
            hi = mid - 1;           
        } else {
            lo = mid + 1;
        }
    }

    cout << answer;
    
    return 0;
}