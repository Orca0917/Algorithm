#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

int L; // 상자의 길이
int N; // 공의 개수
int T; // 시간

map<int, vector<char>> m, after;


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> L >> N >> T;

    // 공의 초기 위치와 방향 입력받기
    for (int i = 0; i < N; ++i) {
        int position; cin >> position;
        char direction; cin >> direction;
        m[position].push_back(direction);
    }

    // 충돌한 횟수
    int answer = 0;

    // T 시간 동안 시뮬레이션 진행
    while (T--) {
        
        after.clear();

        // 방향으로 진행
        for (int i = 0; i <= L; ++i) {
            for (char dir : m[i]) {
                if (dir == 'L') after[i - 1].push_back(dir);
                else after[i + 1].push_back(dir);
            }
        }

        // 공끼리 충돌 발생 여부 감지
        for (int i = 1; i < L; ++i)
            if (after[i].size() == 2)
                ++answer;

        // 벽에 닿은 경우
        for (char &e : after[0]) e = 'R';
        for (char &e : after[L]) e = 'L';
        
        // 새롭게 상황 업데이트
        m = after;
    }

    // 정답 출력
    cout << answer << "\n";
    
    return 0;
}