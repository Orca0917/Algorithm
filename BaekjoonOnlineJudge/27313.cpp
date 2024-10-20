#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

int N;  // 보지 못한 애니메이션의 수
int M;  // 애니메이션 최대 시청가능 시간
int K;  // 동시에 애니메이션 시청

int l[100'000]; // 각 애니메이션을 보는 데에 걸리는 시간

bool is_possible(int x) {

    // K개씩 묶어서 볼 때 필요한 시간
    ll require = 0;

    // 긴것들 먼저 묶어서 보기 시작
    for (int i = x - 1; i >= 0; i -= K) {
        require += l[i];
    }

    return require <= 1LL * M;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    // 입력: 봐야하는 애니메이션의 수
    cin >> N;

    // 입력: 애니메이션을 보는 데에 사용할 수 있는 시간
    cin >> M;

    // 입력: 동시에 볼 수 있는 애니메이션의 수
    cin >> K;

    // 애니메이션을 가장 많이 보려면 짧은 시간것들 먼저 많이 묶어서 보기
    for (int i = 0; i < N; ++i) cin >> l[i];
    sort(l, l + N);

    // 이분탐색 구간 설정 (최대: 모든 애니메이션 다보기)
    int lo = 0, hi = N;
    int answer = 0;

    // 이분탐색
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        if (is_possible(mid)) {
            answer = mid;
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }

    // 출력: 정답
    cout << answer;

    return 0;
}