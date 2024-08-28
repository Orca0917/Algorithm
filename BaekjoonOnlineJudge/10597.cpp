#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

vector<bool> status(51, false);
vector<int> answer;
string s;

bool is_connected(vector<int> v) {
    sort(v.begin(), v.end());
    for (int i = 1; i < v.size(); ++i) if (v[i] != v[i - 1] + 1) return false;
    return true;
}

void solve(int index, vector<int> &v) {

    if (!answer.empty()) return;

    // 종료조건: 모든 문자열 탐색 완료 + 수집한 모든 숫자들이 연결되어야 함
    if ((int)s.length() <= index && is_connected(v)) {
        answer = v;
        return;
    }

    // 숫자는 한자리 수 또는 두자리 수 숫자를 선택해본다.
    for (int select = 1; select <= 2; ++select) {
        if (index + select - 1 < (int)s.length()) {
            string sub = s.substr(index, select);   // 부분 문자열
            int isub = stoi(sub);                   // 문자열을 숫자로 변환하자
            if (status[isub] == false) {            // 이미 담았던 숫자라면 안되지
                status[isub] = true;
                v.push_back(isub);
                solve(index + select, v);           // 다음 문자열을 탐색해보자
                status[isub] = false;
                v.pop_back();
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> s;

    // 백트래킹 재귀
    vector<int> v;
    solve(0, v);

    // 정답 출력
    for (int e : answer) cout << e << " ";
    
    return 0;
}