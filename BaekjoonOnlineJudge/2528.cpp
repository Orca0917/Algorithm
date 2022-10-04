#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

struct STICK {
    int start;
    int end;
    int dir;
};

int N; // 층 수
int L; // 층의 길이

vector<STICK> floors;

bool is_intersect(int floor1, int floor2) {
    if (floors[floor1].end >= floors[floor2].start && floors[floor1].start <= floors[floor2].end) return true;
    else if (floors[floor1].start <= floors[floor2].end && floors[floor2].start <= floors[floor1].end) return true;
    else return false;
}


void move_sticks() {
    for (int floor = 0; floor < N; ++floor) {

        // 스틱이 오른쪽으로 이동
        if (floors[floor].dir == 0) {
            // 끝에 도달하여 반대방향으로 이동
            if (floors[floor].end == L) {
                floors[floor].start -= 1;
                floors[floor].end -= 1;
                floors[floor].dir = 1;
            } else {
                floors[floor].start += 1;
                floors[floor].end += 1;
            }
        } 
        
        // 스틱이 왼쪽으로 이동
        else {
            if (floors[floor].start == 0) {
                floors[floor].start += 1;
                floors[floor].end += 1;
                floors[floor].dir = 0;
            } else {
                floors[floor].start -= 1;
                floors[floor].end -= 1;
            }
        }
    }
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> N >> L;
    for (int i = 0; i < N; ++i) {
        int l;  // 막대기의 길이
        int d;  // 움직이는 방향 (0: right, 1: left)

        cin >> l >> d;
        if (d == 0) floors.push_back({0, l, d});
        else floors.push_back({L - l, L, d});
    }

    int answer = 0;     // 최소 시간
    int cur_floor = 0;  // 현재 층수

    while (cur_floor < N - 1) {
        while (cur_floor < N - 1 && is_intersect(cur_floor, cur_floor + 1)) ++cur_floor;
        move_sticks();
        if (cur_floor != N - 1) ++answer;
    }

    cout << answer << "\n";
    
    return 0;
}