#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

vector<int> A;

void manacher(string &s) {
    int r = 0, p = 0;
    int n = (int)s.length();

    // 모든 문자열의 index를 한 번씩 순회
    for (int i = 0; i < n; ++i) {

        // r = 이전에서 나올 수 있는 가장 큰 팰린드롬 범위 (마지막 index)
        // r = p + A[p]
        if (i > r) A[i] = 0;
        else A[i] = min(r - i, A[2 * p - i]);

        // 현재 위치로 부터 가능한 가장 큰 팰린드롬의 반지름 찾기
        while (i - A[i] - 1 >= 0 && i + A[i] + 1 < n && s[i - A[i] - 1] == s[i + A[i] + 1]) ++A[i];

        // r 업데이트
        if (r < i + A[i]) {
            r = i + A[i];
            p = i;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    string s; cin >> s;

    string processed_s;
    for (char &c : s) {
        processed_s += "#";
        processed_s += c;
    } processed_s += "#";

    A.resize(processed_s.length(), 0);
    manacher(processed_s);

    cout << *max_element(A.begin(), A.end()) << "\n";

    return 0;
}