#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long
using namespace std;
bool isPrime[1000001];
void eratos() {
    memset(isPrime, true, sizeof(isPrime));
    isPrime[0] = isPrime[1] = false;
    for (int i = 2; i * i < 1000001; ++i) {
        if (isPrime[i]) {
            for (int j = 2; i * j < 1000001; ++j)
                isPrime[i * j] = false;
        }
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    eratos();
    int testcase; cin >> testcase;
    while (testcase--) {
        int n, e; cin >> n >> e;
        vector<int> arr(n + 1);
        vector<int> left(n + 1), right(n + 1);

        for (int i = 1; i <= n; ++i) cin >> arr[i];

        for (int start = 1; start <= e; ++start) {
            int i = start;
            int cnt = 0;
            while (i <= n) {
                if (arr[i] > 1) {
                    left[i] = cnt + 1;
                    cnt = 0;
                } else {
                    ++cnt;
                }
                i += e;
            }
            cnt = 0;
            i -= e;
            while (i >= 1) {
                if (arr[i] > 1) {
                    right[i] = cnt + 1;
                    cnt = 0;
                } else {
                    ++cnt;
                }
                i -= e;
            }
        }
        ll answer = 0;
            for (int i = 1; i <= n; ++i) {
                if (isPrime[arr[i]])
                    answer += 1LL * left[i] * right[i] - 1;
            }
        cout << answer << "\n";
    }
    return 0;
}