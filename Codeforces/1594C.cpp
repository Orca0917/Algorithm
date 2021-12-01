#include <iostream>
#define MOD 1000000007
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int testcase; cin >> testcase;
    while (testcase--) {
       int stringLen; cin >> stringLen;
       char c; cin >> c;
       string s; cin >> s;

       bool isStrange = false;
       for (auto ch : s)
        if (ch != c) {
            isStrange = true;
            break;
        }

        // 모든 문자열이 c로 이루어져 있음
        if (!isStrange) {
            cout << 0 << "\n";
            continue;
        }

        bool notFound = true;
        // 1번의 연산 수행으로 끝내는 경우2 : 중간 ~ 마지막 문자가 c
        for (int x = stringLen / 2; x < stringLen && notFound; ++x) {
            if (s[x] == c) {
                cout << 1 << "\n";
                cout << x + 1 << "\n";
                notFound = false;
            }
        }

        if (notFound) {
            cout << 2 << "\n";
            cout << stringLen - 1 << " " << stringLen << "\n";
        }
    }

    return 0;
}