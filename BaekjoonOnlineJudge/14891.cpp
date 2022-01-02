#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

vector<string> A(4);
vector<int> change(4);
int number, option, rotation;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    
    for (int i = 0; i < 4; ++i)
        cin >> A[i];

    int K; cin >> K;
    while (K--) {
        cin >> number >> option;

        fill(change.begin(), change.end(), 0);
        change[number - 1] = option;

        rotation = -option;

        // 3번 톱니와, 6번 톱니를 비교
        for (int i = number - 2; i >= 0; --i) {
            if (A[i][2] == A[i + 1][6]) break;
            change[i] = rotation;
            rotation *= -1;
        }

        rotation = -option;
        for (int i = number; i < 4; ++i) {
            if (A[i - 1][2] == A[i][6]) break;
            change[i] = rotation;
            rotation *= -1;
        }

        for (int i = 0; i < 4; ++i) {
            if (change[i] == 1) {
                A[i] = A[i][7] + A[i].substr(0, 7);
            } else if (change[i] == -1) {
                A[i] = A[i].substr(1, 7) + A[i][0];                   
            }
        }
    }

    int answer = 0;
    for (int i = 0; i < 4; ++i) {
        if (A[i][0] == '1') answer += pow(2, i);
    }

    cout << answer << "\n";
    return 0;
}