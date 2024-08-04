#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    

    int T; cin >> T;
    while (T--) {
        vector<int> r(1025, -1);
        vector<int> his_q(1025, -1);
        vector<bool> circ(1025, false);

        // 분자, 분모
        int son, mother; cin >> son >> mother;

        // 몫, 나머지 계산
        int Q = son / mother;
        int R = son % mother;
        
        // 소수점 이하를 출력하기 위한 출발 지점
        int init = R;
        
        // 소수점 아래 탐색 (0으로 나누어떨어지거나, 순환소수를 찾은 경우 종료)
        while (R) {
            
            // 나누어 떨어지지 못했으므로 10 곱해주기
            R *= 10;

            // 기존 나머지 R에 대한 몫 q의 값을 기록
            int q = R / mother;
            his_q[R / 10] = q;

            // 다음 나머지 값을 기록
            r[R / 10] = R % mother;

            // 다음 나머지 업데이트
            R %= mother;

            // 그런데 이미 해당 나머지를 계산한적이 있다? -- 순환소수
            if (r[R] != -1) {
                circ[R] = true;
                break;
            }
        }

        bool enter = true;
        circ[0] = true;
        r[0] = 0;
        his_q[0] = 0;

        cout << Q << ".";
        while (true) {
            if (circ[init]) {
                cout << (enter ? "(" : ")\n");
                if (!enter) break;
                enter = false;
            }
            cout << his_q[init];
            init = r[init];
        }
    }


    
    return 0;
}