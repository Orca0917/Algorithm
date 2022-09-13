#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

string s1, s2; 
int memo[1001][1001];

int dp(int idx1, int idx2) {
    if (idx1 == s1.length()) return s2.length() - idx2;     // 남은 문자 모두 추가
    if (idx2 == s2.length()) return s1.length() - idx1;     // 남은 문자 모두 삭제

    int &ret = memo[idx1][idx2];
    if (ret != -1) return ret;

    ret = 1e9;

    if (s1[idx1] == s2[idx2]) ret = min(ret, dp(idx1 + 1, idx2 + 1));
    else {
        ret = min(ret, dp(idx1, idx2 + 1) + 1);     // 삽입
        ret = min(ret, dp(idx1 + 1, idx2) + 1);     // 삭제
        ret = min(ret, dp(idx1 + 1, idx2 + 1) + 1); // 교체
    }

    return ret;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> s1 >> s2;

    memset(memo, -1, sizeof(memo));
    cout << dp(0, 0) << "\n";

    return 0;
}