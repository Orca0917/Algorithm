#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

struct quad{
    int x;
    int y;
    int dir;
    int count;
};

int n, m;
int board[105][105];
int visits[105][105][5];
int next_direction[2][5] = {{0, 4, 3, 1, 2}, {0, 3, 4, 2, 1}};
quad start, finish;
int answer = 1e9;

int get_nextDir(int now_dir, int option) {
    return next_direction[option][now_dir];
}

pii get_nextPos(int x, int y, int dir, int moves) {
    int mul = 1;
    if (dir % 2 == 0) mul = -1;

    if (dir == 1 || dir == 2)
        y = y + mul * moves;
    else 
        x = x + mul * moves;

    return {x, y};
}

bool get_validPos(pii pos) {
    int x = pos.first;
    int y = pos.second;
    
    // 맵 밖으로 벗어나는 경우
    if (x < 0 || x >= n || y < 0 || y >= m) return false;

    // 로봇이 이동할 수 없는 지형인 경우
    if (board[x][y] == 1) return false;

    return true;
}

void bfs() {
    queue<quad> q;
    q.push(start);
    visits[start.x][start.y][start.dir] = 0;

    while (!q.empty()) {
        quad here = q.front();
        q.pop();

        int herex = here.x;
        int herey = here.y;
        int hereDir = here.dir;
        int hereCount = here.count;

        if (herex == finish.x && herey == finish.y && hereDir == finish.dir) {
            answer = min(answer, hereCount);
            continue;
        }

        // 방향 틀기 -> 좌, 우
        for (int dirOpt = 0; dirOpt < 2; ++dirOpt) {
            int nextDir = get_nextDir(hereDir, dirOpt);
            int nextCount = hereCount + 1;
            
            int &ref = visits[herex][herey][nextDir];
            if (ref != -1 && ref <= nextCount) continue;
            ref = nextCount;
            q.push({herex, herey, nextDir, nextCount});
        }

        // 현재 방향으로 1, 2, 3칸 전진
        for (int moves = 1; moves <= 3; ++moves) {
            pii nextPos = get_nextPos(herex, herey, hereDir, moves);
            bool isValid_Pos = get_validPos(nextPos);
            if (!isValid_Pos) break; // 더이상의 전진은 불가능하기 때문에 break

            int &ref = visits[nextPos.first][nextPos.second][hereDir];
            int nextCount = hereCount + 1;
            if (ref != -1 && ref <= nextCount) continue;
            ref = nextCount;
            q.push({nextPos.first, nextPos.second, hereDir, nextCount});
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n >> m;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            cin >> board[i][j];

    memset(visits, -1, sizeof(visits));

    cin >> start.x >> start.y >> start.dir;
    cin >> finish.x >> finish.y >> finish.dir;
    start.count = 0;

    // 좌표는 0, 0 부터 시작이지;
    --start.x;
    --start.y;
    --finish.x;
    --finish.y;

    bfs();
    
    cout << answer << "\n";

    return 0;
}