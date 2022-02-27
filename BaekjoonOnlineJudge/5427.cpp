#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define MAX_BOARD 1001
#define FIRE '*'
#define PERSON '@'
#define WALL '#'
using namespace std;

struct tri {
    int x, y, moved;
};

int n, m;
char board[MAX_BOARD][MAX_BOARD];
// x좌표, y좌표, 이동횟수
queue<tri> person;
queue<pii> fire;

void init_global_variables() {
    person = queue<tri>();
    fire = queue<pii>();
    
    for (int i = 0; i < MAX_BOARD; ++i)
        for (int j = 0; j < MAX_BOARD; ++j)
            board[i][j] = '.';
}

bool isin_border(int x, int y) {
    if (x < 0 || x >= n || y < 0 || y >= m) return false;
    else return true;
}

void spread_fire() {
    int fire_size = fire.size();
    while (fire_size--) {
        int firex = fire.front().first;
        int firey = fire.front().second;
        fire.pop();

        for (int direction = 0; direction < 4; ++direction) {
            int next_firex = firex + ("2110"[direction] - '0' - 1);
            int next_firey = firey + ("1201"[direction] - '0' - 1);

            // 불이 번질 수 없는 곳이거나, 벽이거나, 이미 불인 곳은 진입 불가
            if (isin_border(next_firex, next_firey) == false) continue;
            char &ref = board[next_firex][next_firey];
            if (ref == WALL || ref == FIRE) continue;

            ref = FIRE;
            fire.push({next_firex, next_firey});
        }
    }
}

void print_intervals() {
    cout << "\n========== INFO ==========\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j)
            cout << board[i][j];
        cout << "\n";
    }
    cout << "\n";
}

int BFS(vector<pii> &fires, pii &init_pos) {
    
    // 초기 불의 위치 삽입
    for (pii fire_pos : fires)
        fire.push(fire_pos);

    // 초기 사람의 위치 삽입
    person.push({init_pos.first, init_pos.second, 0});

    int person_size = person.size();
    int pop_cnt = 0;

    while (!person.empty()) {
        int personx = person.front().x;
        int persony = person.front().y;
        int personcnt = person.front().moved;
        person.pop(); ++pop_cnt;

        // 사람이 불에 탄 경우
        if (board[personx][persony] == FIRE) continue;

        // 사람이 탈출에 성공한 경우
        if (personx == 0 || personx == n - 1 || persony == 0 || persony == m - 1) {
            return personcnt + 1;
        }

        // 사람 이동
        for (int direction = 0; direction < 4; ++direction) {
            int next_personx = personx + ("2110"[direction] - '0' - 1);
            int next_persony = persony + ("1201"[direction] - '0' - 1);

            // 벽이거나 불인 곳은 진입 불가 + 이미 방문한 곳은 진입x
            char &ref = board[next_personx][next_persony];
            if (ref == WALL || ref == FIRE || ref == PERSON) continue;

            ref = PERSON;
            person.push({next_personx, next_persony, personcnt + 1});
        }

        // print_intervals();

        // 불 확산
        if (pop_cnt == person_size) {
            spread_fire();
            pop_cnt = 0;
            person_size = person.size();
        }   
    }

    return -1;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int testcase; cin >> testcase;
    while (testcase--) {
        init_global_variables();

        vector<pii> first_fire_position;
        pii person_position;

        cin >> m >> n;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j) {
                char &ref = board[i][j];
                cin >> ref;

                if (ref == FIRE)
                    first_fire_position.emplace_back(i, j);
                else if (ref == PERSON)
                    person_position = {i, j};
            }

        int result = BFS(first_fire_position, person_position);
        if (result == -1) cout << "IMPOSSIBLE\n";
        else cout << result << "\n";
    }
    
    return 0;
}