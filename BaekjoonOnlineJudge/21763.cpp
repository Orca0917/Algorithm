#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

bool mask[100][100];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n, k; cin >> n >> k;

    // 빙고가 무조건 1번 이상 나오는 경우
    if ((n == 2 && k >= 2) || k > n * n - n) {
        cout << "NO\n";
    }

    // 빙고 없이 채울 수 있는 경우
    else {

        cout << "YES\n";

        // 대각선 모두 비워놓기
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                mask[i][j] = (i != j);

        // 짝수면 반대쪽 대각선이 되니까, 맨 위 아래 바꾸기
        if (n % 2 == 0) {
            swap(mask[0][0], mask[0][n - 1]);
            swap(mask[n - 1][0], mask[n - 1][n - 1]);
        }

        // 나머지 개수에 맞게 채우고 그 외는 빈칸!
        int filled = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j)
                if (mask[i][j] && filled++ < k) cout << "#";
                else cout << ".";
            cout << "\n";
        }
    }
    
    return 0;
}