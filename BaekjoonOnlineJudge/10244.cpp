#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n;
    while (cin >> n && n) {
        vector<int> arr(n);
        for (int &a : arr) cin >> a;

        int answer = 0;

        int k = *max_element(arr.begin(), arr.end());
        // 1 ~ 100 을 순회하면서 나누어 떨어지는 값이 div인 것을 확인
        for (int div = 1; div <= k; ++div) {
            int gcd_val = 0;

            // 입력받은 원소들을 모두 순회
            for (int a : arr) {

                // 입력받은 원소가 div로 나누어 떨어지는 경우
                if (a % div == 0) {

                    // 이전의 gcd value가 없는 경우 -> 새로 할당
                    if (gcd_val == 0) gcd_val = a;

                    // 이전의 gcd value가 존재하는 경우 -> 누적
                    else gcd_val = __gcd(gcd_val, a);

                    // 마지막으로 나누어 떨어지는 값이 div
                    if (gcd_val == div) {
                        ++answer;
                        break;
                    }

                // 입력받은 원소가 div로 나누어 떨어지지 않는 경우
                } else {
                    gcd_val = 0;
                }
            }
        }

        cout << answer << "\n";
    }
    
    return 0;
}