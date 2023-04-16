#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

int n;
int memo[1'000'001][2];
string s;

// 0~index까지의 문자를 모두 c가 되도록!
int dp(int index, char c) {
    if (index == n) return c == 'B'; // B는 한 번 뒤집어 줘야 함

    int &ret = memo[index][c - 'A'];
    if (ret != -1) return ret;

    ret = 1e9;
    if (s[index] == c) ret = min(dp(index + 1, c), dp(index + 1, c ^ ('A' ^ 'B')) + 1);
    else ret = min(dp(index + 1, c) + 1, dp(index + 1, c ^ ('A' ^ 'B')) + 1);

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n >> s;
    memset(memo, -1, sizeof(memo));
    cout << min(dp(0, 'A'), dp(0, 'B'));

    return 0;
}