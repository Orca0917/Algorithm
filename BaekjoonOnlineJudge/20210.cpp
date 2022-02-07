#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int n;
vector<string> v;

char to_lower(char c) {
    if (c >= 'a') return c;
    else return c - 'A' + 'a';
}

bool isDigit(char c) {
    return (c >= '0' && c <= '9');
}

pair<int, string> getNum(string a, int ai) {
    int a_zero = 0;
    string a_num;

    bool flag = true;
    for (int i = ai; i < a.length() && isDigit(a[i]); i++) {
        if (flag && a[i] == '0') ++a_zero;
        else {
            flag = false;
            a_num += a[i];
        }
    }

    return {a_zero, a_num};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n;
    v.resize(n);
    for (auto &e : v) {
        cin >> e;
    }

    // 문자열은 알파벳 대소문자와 숫자로만 이루어져 있다
    sort(v.begin(), v.end(), [](const string &a, const string &b) -> bool {

        for (int index = 0; index < min(a.length(), b.length()); index++) {

            char ch_a = a[index], ch_b = b[index];
            
            // 숫자열끼리는 십진법으로 읽어서 더 작은 것이 앞에 온다. 이때 예제 2에서와 같이 값이 2^63을 초과할 수 있다.
            // 같은 값을 가지는 숫자열일 경우 앞에 따라붙는 0의 개수가 적은 것이 앞에 온다.
            if (isDigit(ch_a) && isDigit(ch_b)) {
                pair<int, string> a_val = getNum(a, index);
                pair<int, string> b_val = getNum(b, index);

                // 숫자 부분이 정확히 동일한 경우
                if (a_val.second == b_val.second && a_val.first == b_val.first) {
                    index += a_val.first + a_val.second.length() - 1;
                    continue;
                } else if (a_val.second == b_val.second) return a_val.first < b_val.first;
                else if (a_val.second.length() == b_val.second.length()) return a_val.second < b_val.second;
                else return a_val.second.length() < b_val.second.length();
            } 
            
            // 숫자열이 알파벳보다 앞에 오고, 알파벳끼리는 AaBbCc...XxYyZz의 순서를 따른다.
            else if (isDigit(ch_a) == false && isDigit(ch_b) == false)
                if (to_lower(ch_a) == to_lower(ch_b)) {
                    if (ch_a == ch_b) continue;
                    else return ch_a < ch_b;
                } else {
                    return to_lower(ch_a) < to_lower(ch_b);
                }
            
            
            // 문자열을 비교하는 중 숫자가 있을 경우 그 다음에 오는 숫자를 최대한 많이 묶어 한 단위로 비교한다. 예를 들어 "a12bc345"는 "a", "12", "b", "c", "345"의 다섯 단위로 이루어져 있다.
            else {
                if (isDigit(ch_a)) return true;
                else return false;
            }
        }

        return a.length() < b.length();

    });

    for (string e : v) cout << e << "\n";
    return 0;
}