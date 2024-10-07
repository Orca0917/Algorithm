#include <bits/stdc++.h>
using namespace std;

set<int> s; // 서로 다른 금액을 저장할 집합
vector<int> coins = {1, 5, 10, 50};
int n;

// 재귀를 사용하여 금액 계산
void solve(int sum, int picked, int index) {
    // 동전 n개를 모두 선택한 경우 금액 저장
    if (picked == n) {
        s.insert(sum);
        return;
    }

    for (int i = index; i < 4; ++i) {
        solve(sum + coins[i], picked + 1, i); // 재귀 호출
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n;
    solve(0, 0, 0);

    cout << (int)s.size(); // 서로 다른 금액의 수 출력
    
    return 0;
}
