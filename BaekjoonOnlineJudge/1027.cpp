#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

int n;
vector<int> v;
vector<int> cnt;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    // 입력, 초기화
    cin >> n;
    v.resize(n);
    cnt.resize(n, 0);

    for (int &e : v) cin >> e;

    // 빌딩 i와 빌딩j 사이를 잇는 직선의 기울기를 계산해주는 함수
    auto calc_angle = [&](int i, int j) -> double {
        return (v[i] - v[j]) / (double)(i - j);
    };

    // 각 고층빌딩마다 보이는 고층빌딩의 수를 계산한다.
    for (int current = 0; current < n; ++current) {

        double min_angle = 2e9;
        for (int other = current - 1; other >= 0; --other) {
            // 이전 기울기보다 작아져야지 볼 수 있음
            double angle = calc_angle(current, other);
            if (min_angle > angle) {
                min_angle = angle;
                cnt[current] += 1;
            }
        }

        double max_angle = -2e9;
        for (int other = current + 1; other < n; ++other) {
            // 이전 기울기보다 커지면 볼 수 있음
            double angle = calc_angle(current, other);
            if (max_angle < angle) {
                max_angle = angle;
                cnt[current] += 1;
            }
        }
    }

    cout << *max_element(cnt.begin(), cnt.end()) << "\n";

    return 0;
}