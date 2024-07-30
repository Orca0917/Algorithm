#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

// timestep s / n * n / 중앙 k * k 색칠 / (r1, c1) ~ (r2, c2) 의 모습 출력
int s, n, k, r1, r2, c1, c2;

bool is_center(int timestep, int r, int c) {
    int N = pow(n, timestep);
    int K = k * pow(n, timestep - 1);
    int start = (N - K) / 2;
    int end = N - start;

    return (start <= r) && (r < end) && (start <= c) && (c < end);
}


int func(int timestep, int r, int c) {
    // timestep이 0인 경우: 흰색 타일 1개
    if (timestep == 0) return 0;

    // timestep이 1인 경우 중앙 판별
    if (timestep == 1) return is_center(timestep, r, c) ? 1: 0;
    
    // timestep이 2이상인 경우: 재귀 탐색
    if (is_center(timestep, r, c)) return 1;
    int pre_len = pow(n, timestep - 1);
    return func(timestep - 1, r % pre_len, c % pre_len);
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> s >> n >> k >> r1 >> r2 >> c1 >> c2;

    for (int i = r1; i <= r2; ++i) {
        for (int j = c1; j <= c2; ++j)
            cout << func(s, i, j);
        cout << "\n";
    }
    
    return 0;
}