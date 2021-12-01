#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int testcase; cin >> testcase;
    while (testcase--) {
        int n; cin >> n;
        string s; cin >> s;

        int leftZero = -1, rightZero = -1;
        for (int i = 0; i < n / 2; ++i) {
            if (s[i] == '0') {
                leftZero = i;
                break;
            }
        }

        for (int i = n / 2; i < n; ++i) {
            if (s[i] == '0') {
                rightZero = i;
                break;
            }
        }


        if (leftZero != -1) {
            ++leftZero;
            cout << leftZero + 1 << " " << n << " " << leftZero << " " << n << "\n";
        } else if(rightZero != -1) {
            ++rightZero;
            cout << "1 " << rightZero << " 1 " << rightZero - 1 << "\n";
        } else {
            cout << "2 " << n << " 1 " << n - 1 << "\n";
        }
    }
    return 0;
}