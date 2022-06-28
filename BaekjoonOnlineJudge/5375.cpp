#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

struct MALL {
    int p; // 공책 1개의 가격
    int o; // 배송비
    int s; // 공책 보유 수량
};


vector<MALL> v; // 쇼핑몰의 판매 정보
int memo[10001][101]; // dp[i][j] : 공책 i 개를 1 ~ j 번째 쇼핑몰을 사용하여 구매할 때의 최소비용
int n, m; // 구매하려고 하는 공책의 수(n), 쇼핑몰의 수(m)


int dp(int book, int mall) {

    // base condition
    if (mall == -1) {
        if (book == 0) return 0;
        else return 1e9;
    }
    else if (book == 0) return 0;

    // memoization
    int &ret = memo[book][mall];
    if (ret != -1) return ret;

    ret = 1e9;
    int buy = min(book, v[mall].s); // 최대 구매 가능 수량

    // (1) 현재 쇼핑몰에서 아무것도 구매 X
    ret = min(ret, dp(book, mall - 1));

    // (2) 현재 쇼핑몰에서 공책 모두 구매
    ret = min(ret, dp(book - buy, mall - 1) + v[mall].o + v[mall].p * buy);

    return ret;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int testcase; cin >> testcase;
    while (testcase--) {
        // 전역변수 초기화
        memset(memo, -1, sizeof(memo));
        v.clear();

        // 입력
        cin >> n >> m;
        v.resize(m);
        for (auto &e : v) cin >> e.s >> e.p >> e.o;

        // 가격이 낮은 쇼핑몰부터 모두 구매
        sort(v.begin(), v.end(), [](const MALL &a, const MALL &b) -> bool {
            return a.p > b.p;
        });

        cout << dp(n, m - 1) << "\n";
    }    

    return 0;
}