#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int n, k;
int result[55];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n >> k;

    memset(result, 0, sizeof(result));

    // 만들 수 없는 경우 판별
    int N = n / 2;
    if (N * (n - N) < k) {
        cout << "-1\n";
        return 0;
    }

    // k = 0인 경우, 모든 자리를 A 로 채우기
    if (k == 0) {
        for (int i = 0; i < n; ++i) cout << "A";
        return 0;
    }

    int max_A = ceil(sqrt((double)k));
    int A_cnt = max_A;
    int B_cnt = k / A_cnt;
    result[A_cnt] += B_cnt;
    k -= A_cnt * B_cnt;

    while (k > 0) {
        if (k >= --A_cnt) {
            B_cnt = k / A_cnt;
            result[A_cnt] += B_cnt;
            k -= A_cnt * B_cnt;
        }
    }

    string answer = "";
    for (int i = 1; i <= max_A; ++i) {
        answer += "A";
        while (result[i]-- > 0) answer += "B";
    }

    while (answer.length() < n) answer += "A";
    cout << answer << "\n";

    return 0;
}