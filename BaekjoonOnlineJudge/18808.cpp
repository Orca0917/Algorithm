#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

struct STICKER {
    int height = 0;
    int width = 0;
    int shape[10][10] = {0, };

    void rotate90() {
        // 행렬 A의 90도 회전 = 행렬 A의 Transpose + 좌우대칭
        int transposed[10][10];
        memset(transposed, 0, sizeof(transposed));

        // Step 1. Transpose
        for (int i = 0; i < height; ++i)
            for (int j = 0; j < width; ++j)
                transposed[j][i] = shape[i][j];
        
        swap(height, width);

        // Step 2. 좌우 대칭
        memset(shape, 0, sizeof(shape));
        for (int i = 0; i < height; ++i)
            for (int j = 0; j < width; ++j)
                shape[i][width - j - 1] = transposed[i][j];
    }
};

int notebook_h, notebook_w, k;
int answer = 0;
int notebook[41][41];
vector<STICKER> stickers;

bool find_empty_space(STICKER &sticker) {
    int sticker_h = sticker.height;
    int sticker_w = sticker.width;

    for (int i = 0; i <= notebook_h - sticker_h; ++i) {
        for (int j = 0; j <= notebook_w - sticker_w; ++j) {
            bool does_fit = true;
            for (int ii = 0; ii < sticker_h; ++ii) {
                for (int jj = 0; jj < sticker_w; ++jj) {
                    if (notebook[i + ii][j + jj] == 1 && sticker.shape[ii][jj] == 1) does_fit = false;
                }
            }

            // i, j에 붙이기 불가능 -> 다른 위치 탐색
            if (does_fit == false) continue;

            // i, j에 붙이기 가능 -> 스티커 붙이기
            for (int ii = 0; ii < sticker_h; ++ii) {
                for (int jj = 0; jj < sticker_w; ++jj) {
                    if (sticker.shape[ii][jj] == 1) {
                        ++answer;
                        notebook[i + ii][j + jj] = sticker.shape[ii][jj];
                    }
                }
            }
            return true;
        }
    }

    return false;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    memset(notebook, 0, sizeof(notebook));
    cin >> notebook_h >> notebook_w >> k;

    // 스티커 k개 입력받기
    for (int i = 0; i < k; ++i) {
        // 스티커 변수 생성
        STICKER sticker;
        memset(sticker.shape, 0, sizeof(sticker.shape));

        // 스티커의 높이, 너비 입력
        cin >> sticker.height >> sticker.width;

        // 스티커 모습 입력 받기
        for (int h = 0; h < sticker.height; ++h)
            for (int w = 0; w < sticker.width; ++w)
                cin >> sticker.shape[h][w];

        // 스티커 목록에 현재 만들어진 스티커 추가
        stickers.push_back(sticker);
    }


    for (STICKER &sticker : stickers) {
        for (int rotate = 0; rotate < 4; ++rotate) {
            bool attached = find_empty_space(sticker);  // 스티커가 들어갈 수 있는지 찾기
            if (attached) break;                        // 붙이기 성공!
            if (rotate < 3) sticker.rotate90();         // 못붙였으니 90도 회전
        }
    }

    cout << answer << "\n";
    
    return 0;
}