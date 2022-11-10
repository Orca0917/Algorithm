#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n, m;
    string ans;

    cin >> n >> m;

    // 문자열 '?'로 초기화
    for(int i = 0; i < n; i++) {
        ans.push_back('?');
    }

    int curPos = 0;    // 화살표 위치 (화살표가 가리키고 있는 곳)
    bool flag = true;

    for (int i = 0; i < m; i++) {
        int k;
        char s;
        
        cin >> k >> s;

        k %= n;
        curPos -= k;

        if (curPos < 0) curPos += n;

        if (ans[curPos] != '?' && ans[curPos] != s) {
            cout << "!" << '\n';
            flag = false;
            break;
        }

        if (ans.find(s) != string::npos && ans[curPos] != s) {
            cout << "!" << '\n';
            flag = false;
            break;
        }

        ans[curPos] = s;
    }
    
    for (int i = 0; flag && i < n; ++i)
        cout << ans[(curPos + i) % n];

    
    return 0;
}