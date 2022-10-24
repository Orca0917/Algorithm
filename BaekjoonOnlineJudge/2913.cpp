#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

vector<int> isPrime(1'000'001, 1);
vector<int> prefix_prime(1'000'001, 0);
vector<int> fermat_prime(1'000'001, 0);

// 에라토스테네스의 체를 활용한 소수 판별
void eratos() {
    isPrime[0] = isPrime[1] = 0;

    for (int i = 2; i <= 1'000'000; ++i) {
        for (int j = 2; i * j <= 1'000'000 && isPrime[i]; ++j) {
            isPrime[i * j] = 0;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    eratos();
    
    // 누적합 계산
    for (int i = 1; i <= 1'000'000; ++i) {
        prefix_prime[i] = prefix_prime[i - 1] + isPrime[i];
        fermat_prime[i] = fermat_prime[i - 1] + (isPrime[i] && ((i - 1) % 4 == 0) || (i == 2));
    }

    while (true) {
        int L, R; cin >> L >> R;
        // 종료 조건
        if (L == -1 && R == -1) break;

        // 입력 받은 구간 출력
        cout << L << " " << R << " ";

        // 음수인 구간은 최저 1로 설정
        L = max(1, L);
        R = max(1, R);

        // 정답 출력
        cout << prefix_prime[R] - prefix_prime[L - 1] << " ";
        cout << fermat_prime[R] - fermat_prime[L - 1] << "\n";
    }
    
    return 0;
}