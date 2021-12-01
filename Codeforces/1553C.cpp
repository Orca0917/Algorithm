#include <bits/stdc++.h>
#define pii pair<int, int>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int testcase; cin >> testcase;
    while (testcase--) {
        vector<char> a(5), b(5);
        for (int i = 0; i < 5; ++i) {
            cin >> a[i] >> b[i];
        }

        int answerA = 10, answerB = 10;
        int answer = 10;
        // A를 이기게 했을 때
        int scoreA = 0, scoreB = 0;
        for (int i = 0; i < 5; ++i) {
            if (a[i] != '?') {
                scoreA += a[i] - '0';
            } else {
                scoreA += 1;
            }
            // A의 득점으로 경기가 끝나는지 확인
            if (scoreA > scoreB + 5 - i || scoreA + 4 - i < scoreB) {
                answerA = 2 * i + 1;
                break;
            }

            if (b[i] != '?')
                scoreB += b[i] - '0';
            else
                scoreB += 0;

            // B의 득점으로 경기가 끝나는지 확인
            if (scoreB > scoreA + 4 - i || scoreB + 4 - i < scoreA) {
                answerA = 2 * i + 2;
                break;
            }
        }
        answer = min(answerA, answerB);

        scoreA = 0, scoreB = 0;
        for (int i = 0; i < 5; ++i) {
            if (a[i] != '?') {
                scoreA += a[i] - '0';
            } else {
                scoreA += 0;
            }
            // A의 득점으로 경기가 끝나는지 확인
            if (scoreA > scoreB + 5 - i || scoreA + 4 - i < scoreB) {
                answerA = 2 * i + 1;
                break;
            }

            if (b[i] != '?')
                scoreB += b[i] - '0';
            else
                scoreB += 1;

            // B의 득점으로 경기가 끝나는지 확인
            if (scoreB > scoreA + 4 - i || scoreB + 4 - i < scoreA) {
                answerB = 2 * i + 2;
                break;
            }
        }

        cout << min(answer, min(answerA, answerB)) << "\n";
    }
    return 0;
}