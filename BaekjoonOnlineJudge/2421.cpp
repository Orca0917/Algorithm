#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int n;
bool is_prime[1'000'000];
int memo[1000][1000];

void eratos() {
    for (int i = 2; i < 1'000'000; ++i) {
        if (!is_prime[i]) continue;
        for (int j = 2; i * j < 1'000'000; ++j) {
            is_prime[i * j] = false;
        }
    }
}

// 저금통에 각각 a원, b원이 들어있을 때
// n원씩 만들때까지 만날 수 있는 최대의 소수의 개수
int dp(int a, int b) {
    if (a > n || b > n) return 0;

    int &ret = memo[a][b];
    if (ret != -1) return ret;

    // c : 두 수를 이어 붙인 수
    string C = to_string(a) + to_string(b);
    int c = stoi(C);

    // 각 저금통에 1원씩 넣은 경우를 확인 : 둘중에 큰 값에 is_prime[c]를 더한다.
    ret = max(dp(a + 1, b), dp(a, b + 1)) + is_prime[c];
    return ret;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    memset(is_prime, true, sizeof(is_prime));
    memset(memo, -1, sizeof(memo));

    // 1 ~ 1'000'000 까지 소수인지 아닌지 확인
    is_prime[0] = is_prime[1] = false;
    eratos();

    cin >> n;
    
    // 초기 각 저금통에는 1씩 동전이 들어가 있다.
    // 가장 처음 11은 소수로 세지 않기 때문에 1을 빼준다.
    cout << dp(1, 1) - 1 << "\n";
    
    return 0;
}