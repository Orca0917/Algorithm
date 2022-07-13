#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

struct TILE {
    int index;
    int health;
    bool robot = false;
};

deque<TILE> belt_up;
deque<TILE> belt_down;
set<int> zero_set;

int n, k, a;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n >> k;
    for (int i = 0; i < n; ++i) {
        cin >> a;
        belt_up.push_back({i, a, false});
        if (a == 0) zero_set.insert(i);
    }

    for (int i = n; i < 2 * n; ++i) {
        cin >> a;
        belt_down.push_front({i, a, false});
        if (a == 0) zero_set.insert(i);
    }

    int step = 0;
    while (k > 0) {

        // 1. 벨트가 각 칸위에 있는 로봇과 함께 한 칸 회전한다.
        TILE front_last = belt_up.back(); belt_up.pop_back();
        belt_down.push_back(front_last);
        TILE back_last = belt_down.front(); belt_down.pop_front();
        belt_up.push_front(back_last);

        belt_up.back().robot = false; // * 로봇 내리기

        // 2. 가장 먼저 벨트에 올라간 로봇부터, 벨트가 회전하는 방향으로 한 칸 이동할 수 있다면 이동한다. 만약 이동할 수 없다면 가만히 있는다.
        for (int i = belt_up.size() - 1; i > 0; --i) {
            if (belt_up[i].health > 0 && belt_up[i - 1].robot == true && belt_up[i].robot == false) {
                belt_up[i].robot = true;
                belt_up[i - 1].robot = false;
                belt_up[i].health -= 1;
                if (belt_up[i].health == 0) --k;
            }            
        }

        belt_up.back().robot = false; // * 로봇 내리기

        // 3. 올리는 위치에 있는 칸의 내구도가 0이 아니면 올리는 위치에 로봇을 올린다.
        if (belt_up.front().health > 0) {
            belt_up.front().robot = true;
            belt_up.front().health -= 1;
            if (belt_up.front().health == 0) --k;
        }

        ++step;
    }

    cout << step << "\n";
    return 0;
}