#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    // 평일 중, 학생들이 가장 많이 수강할 수 있는 2일 조합을 구하는 문제
    // 평일이 5일밖에 되지 않아, 완전 탐색으로 계산 가능

    int n_students;
    cin >> n_students;

    // 각 학생의 5일간의 수강 가능 여부를 저장하는 배열
    vector<vector<int>> available(n_students, vector<int>(5, 0));
    for (int student = 0; student < n_students; ++student) {
        for (int day = 0; day < 5; ++day) {
            cin >> available[student][day];
        }
    }

    int max_student = 0;
    pii answer = {0, 1}; // {첫 번째 요일, 두 번째 요일} -- 초기화 주의!!

    // 두 개의 요일 조합을 완전 탐색
    for (int day1 = 0; day1 < 5; ++day1) {
        for (int day2 = day1 + 1; day2 < 5; ++day2) {
            int count = 0;
            // 학생들이 두 요일 모두 수강 가능한지 체크
            for (int student = 0; student < n_students; ++student) {
                if (available[student][day1] && available[student][day2]) {
                    ++count;
                }
            }
            // 가장 많은 학생들이 수강 가능한 조합 업데이트
            if (count > max_student) {
                max_student = count;
                answer = {day1, day2};
            }
        }
    }

    cout << max_student << "\n";
    for (int i = 0; i < 5; ++i) {
        cout << ((i == answer.first || i == answer.second) ? 1 : 0) << " ";
    }

    return 0;
}
