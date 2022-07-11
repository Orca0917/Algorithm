#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int memo[10001][4][4];
int enemy[10001][2];

int n, w; // 구역의 수 (2 * n), 1개 소대원의 수 (w)


/** [prev] params.
 * 0 : 블록이 사용되지 않음 
 * 1 : 안쪽이 사용됨
 * 2 : 바깥쪽이 사용됨
 * 3 : 안밖 둘다 사용됨
 */
int dp(int area, int prev, int shape) {

    int &ret = memo[area][prev][shape];
    if (ret != -1) return ret;

    bool bind_inner_left = (enemy[area][0] + enemy[area ? area - 1 : n - 1][0]) <= w;
    bool bind_outer_left = (enemy[area][1] + enemy[area ? area - 1 : n - 1][1]) <= w;
    bool bind_updown = (enemy[area][0] + enemy[area][1]) <= w;

    // 종료지점 (N 에 도달)
    if (area == n - 1) {
        if (area == 0) return bind_updown ? 1 : 2;
        ret = 2;

        if (shape == 0) {
            if (bind_inner_left && !(prev & 1)) ret = 1;
            if (bind_outer_left && prev < 2) ret = 1;
            if (bind_updown) ret = 1;
            if (bind_inner_left && bind_outer_left && prev == 0) ret = 0;
        } else if (shape == 1) {
            if (bind_outer_left && prev < 2) ret = 1;
        } else if (shape == 2) {
            if (bind_inner_left && !(prev & 1)) ret = 1;
        }
        return ret;
    }

    ret = 2 + dp(area + 1, 0, area ? shape : 0);
    if (bind_inner_left && !(prev & 1)) ret = min(ret, dp(area + 1, 1, area ? shape : 1) + 1);
    if (bind_outer_left && prev < 2) ret = min(ret, dp(area + 1, 2, area ? shape : 2) + 1);
    if (bind_inner_left && bind_outer_left && prev == 0) ret = min(ret, dp(area + 1, 3, area ? shape : 3));
    if (bind_updown) ret = min(ret, dp(area + 1, 3, area ? shape : 0) + 1);

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int testcase; cin >> testcase;
    while (testcase--) {
        
        // 1. 전역 변수 초기화
        memset(memo, -1, sizeof(memo));
        memset(enemy, 0, sizeof(enemy));

        // 2. 문제의 입력
        cin >> n >> w;
        for (int i = 0; i < n; ++i) cin >> enemy[i][0];
        for (int i = 0; i < n; ++i) cin >> enemy[i][1];

        // 3. 동적계획법
        cout << dp(0, 0, 0) << "\n";
    }
    
    return 0;
}