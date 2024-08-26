#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

int v[1001][5];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n; cin >> n;

    // 학생들의 학년 정보 입력받기
    for (int student = 0; student < n; ++student)
        for (int grade = 0; grade < 5; ++grade)
            cin >> v[student][grade];

    // ! 초기값 설정에 주의
    int answer = 1, max_cnt = 0;

    // student1 번학생과 student2 번 학생이 grade 학년때 같은반?
    for (int student1 = 0; student1 < n; ++student1) {
        
        // 겹치는 인원 수
        int cnt = 0;
        for (int student2 = 0; student2 < n; ++student2) {
            
            // 동일 인물
            if (student1 == student2) continue;

            // 모든 학년에 대해서 비교
            for (int grade = 0; grade < 5; ++grade) {
                if (v[student1][grade] == v[student2][grade]) {
                    ++cnt;
                    break;
                }
            }
        }

        if (max_cnt < cnt) {
            max_cnt = cnt;
            answer = student1 + 1;
        }
    }

    cout << answer;
    
    return 0;
}