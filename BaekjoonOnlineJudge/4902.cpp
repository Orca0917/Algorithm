#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;
int triangle[405][888];
int psum[405][888];
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int line, testcase = 1;

    while (cin >> line && line) {
        memset(triangle, 0, sizeof(triangle));
        memset(psum, 0, sizeof(psum));

        int answer = -1000001;
        // 삼각형 입력받고, line별 acc_sum값 구하기
        for (int i = 1; i <= line; ++i) {
            for (int j = 1; j <= 2 * i - 1; ++j) {
                cin >> triangle[i][j];
                // answer = max(answer, triangle[i][j]);
                psum[i][j] = psum[i][j - 1] + triangle[i][j];
            }
        }


        // Original 삼각형 (^)
        for (int i = 1; i <= line; ++i) {
            for (int j = 1; j <= 2 * i - 1; j += 2) {
                int temp = 0;

                for (int length = 0; length <= line - i; ++length) {
                    temp += (psum[i + length][j + length * 2] - psum[i + length][j - 1]);
                    answer = max(answer, temp);
                }
            }
        }

        // 역삼각형 (v)
        for (int i = line; i >= 1; --i) {
            for (int j = 2; j <= 2 * i - 1; j += 2) {
                int temp = 0;

                for (int length = 0; length < min(j / 2, i - j / 2); ++length) {
                    int id1 = i - length;
                    int id2 = j;
                    int id3 = j - length * 2 - 1;
                    temp += (psum[id1][id2] - psum[id1][id3]);
                    answer = max(answer, temp);
                }
            }
        }

        cout << testcase++ << ". " << answer << "\n";

    }
    return 0;
}