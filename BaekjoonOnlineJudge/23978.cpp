#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

int N;  // 코인 가격 상승날 수
ll K;  // 현금화하고 싶은 최소 금액
int A[1'000'000];   // 가격 상승 날

bool is_possible(ll x) {

    // 가장 마지막 가격 상승 날에서 얻을 수 있는 수익
    ll total = x * (x + 1) / 2;

    // 상승날 구간마다 얻게 되는 수익 계산
    for (int i = 1; i < N; ++i) {
        ll diff = min(1LL * (A[i] - A[i - 1]), x);
        total += diff * x - diff * (diff - 1) / 2;
    }

    return total >= K;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    // 입력: 코인 가격 상승날 수
    cin >> N;

    // 입력: 현금화하고 싶은 최소 금액
    cin >> K;

    // 입력: 가격 상승날
    for (int i = 0; i < N; ++i) cin >> A[i];

    // 이분탐색 구간설정 (최대: 가격 상승날 하루인 경우)
    ll lo = 0, hi = 1e10;
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