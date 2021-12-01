#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int testcase, n;
string s;

int palin(int start, int end, char c) {
    int ret = 1;
    while (start < end) {
        if (s[start] == s[end]) {
            ++start;
            --end;
        } else {
            if (s[start] == c) {
                ++ret;
                ++start;
            } else if (s[end] == c) {
                ++ret;
                --end;
            } else {
                return -1;
            }
        }
    }
   
    return ret;
}

int checkPalin(int start, int end) {
    int ret = 0;
    while (start < end) {
        if (s[start] == s[end]) {
            ++start;
            --end;
        } else {
            int ret1 = palin(start + 1, end, s[start]);
            int ret2 = palin(start, end - 1, s[end]);

            if (ret1 < 0 && ret2 < 0) return -1;
            else if (ret1 < 0) return ret2;
            else if (ret2 < 0) return ret1;
            else return min(ret1, ret2);
        }
    }

    return ret;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> testcase;
    while (testcase--) {
        cin >> n >> s;
        cout << checkPalin(0, n - 1) << "\n";
    }

    return 0;
}