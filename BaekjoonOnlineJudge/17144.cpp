#include <iostream>
#include <vector>

using namespace std;

int r, c, t;
int map[51][51];

int movement[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

vector<pair<int, int>> air_purifier;

void air_purifier_up() {

    int x = air_purifier[0].first;
    int y = air_purifier[0].second;

    int nx = x;
    int ny = y;

    // 위에서 아래로 순환
    while (nx - 1 >= 0) {
        map[nx][ny] = map[nx - 1][ny];
        nx = nx - 1;
    }

    // 오른쪽에서 왼쪽으로 순환
    while (ny + 1 < c) {
        map[nx][ny] = map[nx][ny + 1];
        ny = ny + 1;
    }

    // 아래에서 위로 순환
    while (nx + 1 <= x) {
        map[nx][ny] = map[nx + 1][ny];
        nx = nx + 1;
    }

    // 왼쪽에서 오른쪽으로 순환
    while (ny - 1 >= 0) {
        map[nx][ny] = map[nx][ny - 1];
        ny = ny - 1;
    }

    map[nx][ny + 1] = 0;
    map[x][y] = -1;
}

void air_purifier_down() {

    int x = air_purifier[1].first;
    int y = air_purifier[1].second;

    int nx = x;
    int ny = y;

    // 아래에서 위로 순환
    while (nx + 1 < r) {
        map[nx][ny] = map[nx + 1][ny];
        nx = nx + 1;
    }

    // 오른쪽에서 왼쪽으로 순환
    while (ny + 1 < c) {
        map[nx][ny] = map[nx][ny + 1];
        ny = ny + 1;
    }

    // 위에서 아래로 순환
    while (nx - 1 >= x) {
        map[nx][ny] = map[nx - 1][ny];
        nx = nx - 1;
    }

    // 왼쪽에서 오른쪽으로 순환
    while (ny - 1 >= 0) {
        map[nx][ny] = map[nx][ny - 1];
        ny = ny - 1;
    }

    map[nx][ny + 1] = 0;
    map[x][y] = -1;
}

void spread_bfs() {

    int copy_map[51][51];

    // 맵 정보 복사해오기
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
            copy_map[i][j] = 0;

    // 확산 시작.
    for (int xpos = 0; xpos < r; xpos++)
        for (int ypos = 0; ypos < c; ypos++)
            if (map[xpos][ypos] > 0) {

                int x = xpos;
                int y = ypos;

                int spread_amount = map[x][y] / 5;

                int adjacent_count = 0;

                for (int i = 0; i < 4; i++) {
                    int nx = x + movement[i][0];
                    int ny = y + movement[i][1];

                    // 맵의 내부에 존재 + 공기청정기가 아닌 지역
                    if (nx >= 0 && ny >= 0 && nx < r && ny < c &&
                        map[nx][ny] != -1) {
                        copy_map[nx][ny] += spread_amount;
                        adjacent_count++;
                    }
                }

                // 자기 자신의 미세먼지 양 감소.
                map[x][y] = map[x][y] - (adjacent_count * spread_amount);
            }

    // 복사한 맵 정보 덮어 쓰기.
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
            map[i][j] += copy_map[i][j];
}

int main() {

    cin >> r >> c >> t;

    // 지도 정보 입력받아 오기
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++) {
            cin >> map[i][j];
            if (map[i][j] == -1)
                air_purifier.push_back(make_pair(i, j));
        }

    for (int sec = 0; sec < t; sec++) {
        spread_bfs();
        air_purifier_up();
        air_purifier_down();
    }

    int answer = 0;
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
            if (map[i][j] > 0)
                answer += map[i][j];

    cout << answer << "\n";

    return 0;
}