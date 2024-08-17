#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

int n;
vector<int> primes;
map<int, ll> m;

// 0과 1로만 이루어진 수를 만들기 위해 이진법을 적용 (이진법을 숫자 그대로 사용)
ll int2bitll(int n) {
    string result = "";
    while (n) {
        result = to_string(n % 2) + result;
        n /= 2;
    }
    return stoll(result);
}

// 소수들만을 가지고 있는 리스트와, 각 소수들은 어떤 이진수로 나누어지는지 확인
void prepare() {
    for (int i = 1; i <= 200; ++i)
        // if (is_prime[i])
            primes.push_back(i);

    for (int prime : primes) {
        ll v = 1;
        while (true) {
            ll value = int2bitll(v++);
            if (value % prime == 0) {
                m[prime] = value;
                cout << value << "\n";
                break;
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    // idea : 어떤 양의 정수 n을 인수분해 하고, 인수분해한 값 들이 0과 1로 만 구성된 수들로 나누어진다면!
    // 그 수들을 모두 곱해도 여전히 0과 1로만 구성되어 있을 것!
    // 인수분해한 수 들은 모두 소수이므로, 소수를 판별하는 것도 필요해 보임
    prepare();
    while (cin >> n && n) cout << m[n] << "\n";
    
    return 0;
}