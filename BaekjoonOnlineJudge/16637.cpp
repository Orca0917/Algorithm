#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

int n;
string s;
ll answer = -(1 << 31);


ll operation(string x, string op, string y) {
    ll val1 = (ll)stoll(x);
    ll val2 = (ll)stoll(y);

    if (op == "+") return val1 + val2;
    else if (op == "-") return val1 - val2;
    else return val1 * val2;
}


ll calc(vector<int> &stat) {
    int stat_idx = 0;

    // 먼저 괄호로 쌓인 것들을 계산
    deque<string> dq;
    for (int i = 0; i < n; ++i) {

        // 현재 operation이 괄호로 쌓인 경우
        if (stat_idx < (int)stat.size() && stat[stat_idx] == i) {
            string x = dq.back(); dq.pop_back();
            string oper(1, s[i]);
            string y(1, s[++i]);

            ll result = operation(x, oper, y);
            dq.push_back(to_string(result));
            ++stat_idx;
        }

        // 일반 숫자 또는 괄호로 쌓여있지 않은 경우
        else {
            string str_val(1, s[i]);
            dq.push_back(str_val);
        }
    }

    // 괄호로 쌓인 것들을 계산했으니, 순차적으로 계산
    string x = dq.front(); dq.pop_front();
    string op = dq.front(); dq.pop_front();
    string y = dq.front(); dq.pop_front();
    ll ret = operation(x, op, y);

    while (dq.size() >= 2) {
        op = dq.front(); dq.pop_front();
        y = dq.front(); dq.pop_front();
        ret = operation(to_string(ret), op, y);
    }

    return ret;
}


void brute(int index, vector<int> stat) {
    if (index > n - 1) answer = max(answer, calc(stat));

    else {
        brute(index + 2, stat); // index 번째 연산에 괄호를 씌우지 않음
        stat.push_back(index);
        brute(index + 4, stat); // index 번째 연산에 괄호를 씌움
    }
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n >> s;

    if (n > 3) {
        vector<int> status;
        brute(1, status);
    } else {
        if (n == 1) answer = s[0] - '0';
        else {
            string x(1, s[0]);
            string op(1, s[1]);
            string y(1, s[2]);
            answer = operation(x, op, y);
        }
    }
    cout << answer << "\n";

    return 0;
}