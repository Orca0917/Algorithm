#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

bool check(deque<char> &dq, string &targ, int opt) {
    if (opt == 1) {
        for (int i = 0; i < targ.length(); ++i)
            if (targ[i] != dq[dq.size() - targ.length() + i])
                return false;
    } else {
        for (int i = 0; i < targ.length(); ++i)
            if (targ[i] != dq[i]) return false;
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    string target; cin >> target; // A
    int tLen = target.length();

    string s; cin >> s;

    int st = 0, ed = s.length() - 1;
    deque<char> start, end;

    while (st <= ed) {
        while (st <= ed) {
            start.push_back(s[st++]);
            if (start.size() >= tLen && check(start, target, 1)) {
                for (int i = 0; i < tLen; ++i)
                    start.pop_back();
                break;
            }
        }

        while (st <= ed) {
            end.push_front(s[ed--]);
            if (end.size() >= tLen && check(end, target, 2)) {
                for (int i = 0; i < tLen; ++i)
                    end.pop_front();
                break;
            }
        }
    }

    string res;
    for (char c : start) res += c;
    for (char c : end) res += c;

    while (res.find(target) != string::npos)
        res.erase(res.find(target), tLen);

    cout << res << "\n";
    return 0;
}