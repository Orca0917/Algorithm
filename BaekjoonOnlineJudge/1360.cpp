#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

map<int, string> m;
string op, c;
int rev, t;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    // 0이라는 시점에서는 아무것도 없었다.
    m[0] = "";

    // n개의 명령어를 받는다.
    int n; cin >> n;
    while (n--) {

        // operation의 종류: type, undo
        cin >> op;

        // 글자를 입력하는 경우
        if (op == "type") {
            cin >> c >> t;

            // 이전의 결과에 이어서 작성한다.
            auto it = m.end();
            m[t] = prev(it) -> second + c;
        }

        // 이전으로 되돌리는 경우
        else if (op == "undo") {
            cin >> rev >> t;

            // rev 시점만큼 되돌아가되 거기서 하나더 뒤로 가야한다.
            auto it = m.lower_bound(t - rev);
            m[t] = prev(it) -> second;
        }
    }

    cout << prev(m.end()) -> second;

    return 0;
}