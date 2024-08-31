#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

struct Data {
    string value;
    int strike;
    int ball;
};

int answer = 0;
vector<Data> v;

// 정답이 answer이라고 했을 때, result의 입력에 대해 내보낼 결과
int strike(string answer, string result) {
    int cnt = 0;
    for (int i = 0; i < 3; ++i)
        if (answer[i] == result[i]) ++cnt;
    return cnt;
}

int ball(string answer, string result) {
    int cnt = 0;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (i != j && answer[i] == result[j]) {
                ++cnt;
                break;
            }
        }
    }
    return cnt;
}

bool is_valid(int x) {
    string sx = to_string(x);
    
    // 0을 포함하거나 중복된 숫자가 있는지 확인
    if (sx.find('0') != string::npos) return false;
    if (sx[0] == sx[1] || sx[1] == sx[2] || sx[0] == sx[2]) return false;
    
    return true;
}

void solve() {
    for (int x = 123; x <= 987; ++x) {
        if (!is_valid(x)) continue;

        string sx = to_string(x);
        bool flag = true;

        for (const Data &e : v) {
            int _strike = strike(sx, e.value);
            int _ball = ball(sx, e.value);

            if (_strike != e.strike || _ball != e.ball) {
                flag = false;
                break;
            }
        }
        if (flag) ++answer;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n; cin >> n;
    v.resize(n);

    for (Data &e : v) 
        cin >> e.value >> e.strike >> e.ball;

    solve();
    cout << answer;
    
    return 0;
}