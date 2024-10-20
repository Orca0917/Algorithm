#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

int N;  // 뛴 거리의 총합이 N이상이면 대머리
int K;  // 뛰는 보폭

int current;
char direction;

bool is_possible(int n) {
    // n 번 뛰는 경우 거리의 합: 등차수열의 합
    ll result = 1LL * n * (n + 1) * K / 2;
    return result <= (1LL * (N - 1));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    // 테스트케이스의 수
    int T; cin >> T;
    while (T--) {
        cin >> N >> K;

        // 이분탐색 구간설정
        int lo = 0, hi = 4500;
        int answer = hi;

        // 이분탐색
        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            if (is_possible(mid)) {
                answer = mid;
                lo = mid + 1;
            }
            else {
                hi = mid - 1;
            }
        }

        int total_distance = answer * (answer + 1) / 2 * K;
        int remaining = N - 1 - total_distance;

        if (answer % 2) {
            current = (answer + 1) / 2 * K - remaining;
            direction = 'L';
        }
        else {
            current = answer / 2 * -K + remaining;
            direction = 'R';
        }

        cout << current << " " << direction << "\n";
    }
    
    return 0;
}