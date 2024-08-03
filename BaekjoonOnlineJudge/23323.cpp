#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int T; cin >> T;
    while (T--) {
        ll n, m; // 초기 체력, 추가 식량
        cin >> n >> m;

        // 최대 생존일: 남은 기간 하루 남을 때마다 먹이 1개씩 주면 최대!
        ll lived = 1 + m;

        while (n > 1) {
            n /= 2;
            ++lived;
        }

        cout << lived << "\n";
    }
    
    return 0;
}