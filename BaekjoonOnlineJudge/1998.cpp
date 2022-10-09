#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int n, m, w;
char board[129][129];
string word[129][129][129];
bool is_all_same[129][129][129];

int result1 = 1, result2 = 0; // result1 은 초기 노드 1을 위해 설정
map<string, int> node_db;

string decompose(int x1, int y1, int x2, int y2) {

    int cell_width = (x2 - x1 + 1);
    int cell_half_width = cell_width / 2;

    // 범위내에 모든 값들이 모두 동일한지 확인
    char c = board[x1][y1];
    for (int i = x1;  i <= x2; ++i)
        for (int j = y1; j <= y2; ++j)
            if (c != board[i][j]) goto NOT_EQUAL;

    // 범위내의 값이 모두 동일함
    is_all_same[x1][y1][cell_width] = true;
    return word[x1][y1][cell_width] = string(1, c);


NOT_EQUAL:
    // 범위 내의 값이 모두 동일하지 않음
    string image = "";
    for (int i = x1; i <= x2; i += cell_half_width)
        for (int j = y1; j <= y2; j += cell_half_width) {
            ++result1;
            image += "<" + decompose(i, j, i + cell_half_width - 1, j + cell_half_width - 1) + ">";
        }

    return word[x1][y1][cell_width] = image;
}


int compress(int x1, int y1, int x2, int y2) {
    int len = (x2 - x1 + 1);
    int half = len / 2;
    int ret = 1;

    string image = word[x1][y1][len];

    // 이미 해당 노드가 등장한 적이 있는 경우 -> 그냥 이어주기
    if (node_db.find(image) != node_db.end()) return 0;

    // 해당 노드가 리프노드인 경우 : W 또는 B 노드 만들어주기
    if (is_all_same[x1][y1][len]) return 1;

    // 해당 노드에서 더 안으로 들어가야함
    else if (node_db.find(image) == node_db.end()) {
        for (int i = x1; i <= x2; i += half)
            for (int j = y1; j <= y2; j += half)
                ret += compress(i, j, i + half - 1, j + half - 1);
    }

    node_db[image] = 1;
    return ret;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    memset(board, '0', sizeof(board));
    memset(is_all_same, false, sizeof(is_all_same));

    cin >> n >> m;

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            cin >> board[i][j];

    int w = pow(2, (int)ceil(log2(max(n, m))));

    decompose(0, 0, w - 1, w - 1);              // 쿼드트리의 정점의 개수
    result2 = compress(0, 0, w - 1, w - 1);     // 가장 효율적인 압축된 쿼드트리의 정점의 개수

    cout << result1 << " " << result2 << "\n";

    return 0;
}