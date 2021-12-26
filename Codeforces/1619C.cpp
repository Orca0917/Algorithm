#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
 
using namespace std;
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int testcase; cin >> testcase;
    while (testcase--) {
        string a, s; cin >> a >> s;
        int sidx = s.length() - 1;
        bool nosuit = false;
        deque<int> answer;

        int aidx = a.length() - 1;
        while (sidx >= 0 && aidx >= 0 && !nosuit) {
            int x = a[aidx--] - '0';

            int y = s[sidx--] - '0';
            if (y - x < 0) 
                if (sidx >= 0) y = (s[sidx--] - '0') * 10 + y;
                else nosuit = true;

            // cout << "y = " << y << ", x = " << x << "\n";
            if (y - x >= 10 || y - x < 0) nosuit = true;

            answer.push_front(y - x);
        }

        while (sidx >= 0) {
            answer.push_front(s[sidx--] - '0');
        }

        if (aidx >= 0 || nosuit) cout << "-1";
        else {
            bool leading = true;
            for (int e : answer) {
                if (e == 0 && leading) continue;
                else {
                    cout << e;
                    leading = false;
                }
            }
        }
        cout << "\n";

    }
       
    return 0;
}