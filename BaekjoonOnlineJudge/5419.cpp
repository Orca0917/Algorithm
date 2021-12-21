#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long
using namespace std;

int testcase;
int n; // 섬의 수
int treeSize;
int treeHeight;

vector<pii> coords; // 섬의 좌표들
vector<int> tree;

// node가 담고 있는 구간: [left, right]
// 찾고 싶은 정보: [start, end]
int queryTree(int node, int left, int right, int start, int end) {
    if (end < left || right < start) return 0;
    if (start <= left && right <= end) return tree[node];

    int mid = (left + right) / 2;
    return queryTree(node * 2, left, mid, start, end) + queryTree(node * 2 + 1, mid + 1, right, start, end);
}

void updateTree(int node, int left, int right, int height) {
    if (height < left || right < height) return;

    int mid = (left + right) / 2;
    tree[node] += 1;

    if (left != right) {
        updateTree(node * 2, left, mid, height);
        updateTree(node * 2 + 1, mid + 1, right, height);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    treeHeight = ceil(log2(75000));
    treeSize = 1 << (treeHeight + 1);

    cin >> testcase;
    while (testcase--) {
        coords.clear();
        tree.clear();

        cin >> n;
        coords.resize(n);
        tree.resize(treeSize, 0);

        for (auto &e : coords)
            cin >> e.first >> e.second;

        // 좌표를 정렬한다. Y좌표가 작은 순
        sort(coords.begin(), coords.end(), [&](const pii a, const pii b) {
            return a.second < b.second;
        });

        int newY = 0;
        vector<int> coordY(n);
        // 좌표의 범위가 -1억 ~ +1억 이기때문에 좌표 압축을 한다.
        coordY[0] = newY;
        for (int i = 1; i < n; ++i) {
            if (coords[i - 1].second != coords[i].second) ++newY;
            coordY[i] = newY;
        }

        for (int i = 0; i < n; ++i)
            coords[i].second = coordY[i];

        sort(coords.begin(), coords.end(), [&](const pii a, const pii b) {
            if (a.first == b.first) return a.second > b.second;
            return a.first < b.first;
        });

        ll answer = 0;
        for (int i = 0; i < n; ++i) {
            int y = coords[i].second;

            answer += queryTree(1, 0, 75000, y, 75000);
            updateTree(1, 0, 75000, y);
        }

        cout << answer << "\n";
    }

    return 0;
}