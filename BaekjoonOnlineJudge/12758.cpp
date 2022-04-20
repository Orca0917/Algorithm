#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define MOD 1'000'000'007
using namespace std;

int memo[302][300];
vector<int> numbers[302]; // step 의 약수들을 저장

void make_numbers(vector<int> &h) {

    for (int i = 0; i < 302; ++i) {
        numbers[i].clear();
    }

    int idx = 1;
    for (int num : h) {
        for (int i = 1; i * i <= num; ++i) {
            if (num % i == 0) {
                numbers[idx].push_back(i);
                numbers[idx].push_back(num / i);
            }
            if (i * i == num) {
                numbers[idx].pop_back();
            }
        }
        sort(numbers[idx].begin(), numbers[idx].end());
        ++idx;
    }
}

bool cmp(const pii &a, const pii &b) {
    return a.first < b.first;
}

int dp(int step, int idx) {
    if (step == 1) return 1;

    int &ret = memo[step][idx];
    if (ret != -1) return ret;

    ret = 0;
    for (int i = 0; i < numbers[step - 1].size(); ++i) {
        if (numbers[step - 1][i] <= numbers[step][idx]) {
            ret += dp(step - 1, i) % MOD;
            ret %= MOD;
        }
    }

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int testcase; cin >> testcase;
    while (testcase--) {
        int n; cin >> n;

        vector<int> h(n);
        for (int &e : h) cin >> e;

        make_numbers(h);
        memset(memo, -1, sizeof(memo));
        numbers[n + 1].push_back(h.back());
        cout << dp(n + 1, 0) % MOD << "\n";
    }
    
    return 0;
}
