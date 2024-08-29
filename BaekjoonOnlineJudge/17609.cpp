#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

int solve(string &s, int left, int right, bool skipped) {
    // left와 right가 같아지거나 역전이 된 경우 : 탐색 종료
    if (left >= right) return (skipped ? 1 : 0);

    // 두 문자열이 대칭이므로 left, right를 이동
    if (s[left] == s[right]) return solve(s, left + 1, right - 1, skipped);

    // 두 문자가 다르므로, skip 권을 사용해서 left를 움직일 것인지, right를 움직일 것인지 판단
    if (s[left] != s[right] && !skipped) return min(solve(s, left + 1, right, true), solve(s, left, right - 1, true));

    // 방법이 없으므로 준-팰린드롬도 될 수 없음
    return 2;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int T; cin >> T;
    while (T--) {
        string s; cin >> s;
        cout << solve(s, 0, s.length() - 1, false) << "\n";
    }
    
    return 0;
}