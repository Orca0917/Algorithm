/**
 * @file problemSolving.cpp
 * @author 0917jong / dbwhdans / killerWhale0917.github.io
 * @brief 
 * @version 0.1
 * @date 2021-12-19
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <bits/stdc++.h>
#define pll pair<ll, ll>
#define ll long long
using namespace std;

int n; // 수열의 크기
int m; // 쿼리의 개수

int treeHeight; // 세그먼트 트리의 높이
int treeSize; // 세그먼트 트리의 크기
vector<pll> tree; // 세그먼트 트리

// 현재 node가 담고 있는 정보는 [left, right]의 구간이며, 우리가 원하는 구간은 [start, end]이다.
void updateTree(int node, int left, int right, int start, int end, int diff) {
    // 현재 node에 lazy값이 있는 경우
    if (tree[node].second % 2 == 1) {
        tree[node].first = (right - left + 1) - tree[node].first;

        // 자식에게도 lazy를 전파한다.
        if (left != right) {
            tree[node * 2].second += tree[node].second;
            tree[node * 2 + 1].second += tree[node].second;
        }
        tree[node].second = 0;
    }

    // 현재 노드가 담고있는 정보가 원하는 구간을 전혀 포함하고 있지 않는 경우
    if (end < left || right < start) return;

    // 현재 노드가 담고있는 정보가 원하는 구간내에 완전히 포함되어 있는 경우.
    if (start <= left && right <= end) {
        // 현재 node가 담고있는 구간의 합을 diff만큼 추가된 정보로 업데이트 한다.
        tree[node].first = (right - left + 1) - tree[node].first;

        // 자식들에게도 update를 시켜주되 바로 업데이트를 하지 않고, lazy를 붙인다.
        if (left != right) {
            tree[node * 2].second += diff;
            tree[node * 2 + 1].second += diff;
        }
        return;
    }

    int mid = (left + right) / 2;
    updateTree(node * 2, left, mid, start, end, diff);
    updateTree(node * 2 + 1, mid + 1, right, start, end, diff);
    tree[node].first = tree[node * 2].first + tree[node * 2 + 1].first;
}

// 현재 node가 담고 있는 정보는 [left, right]의 구간이며, 우리가 원하는 값의 출력은 index이다.
ll queryTree(int node, int left, int right, int start, int end) {
    // 현재 노드에 lazy값이 남아 있는 경우
    if (tree[node].second % 2 == 1) {
        tree[node].first = (right - left + 1) - tree[node].first;
        
        // 자식이 있는 경우, lazy를 다시 전파한다.
        if (left != right) {
            tree[node * 2].second += tree[node].second;
            tree[node * 2 + 1].second += tree[node].second;
        }

        // 현재 node에 대한 lazy는 처리가 완료되었기 때문에 lazy값을 지운다.
        tree[node].second = 0;
    }

    if (end < left || right < start) return 0;

    if (start <= left && right <= end) return tree[node].first;

    int mid = (left + right) / 2;
    return queryTree(node * 2, left, mid, start, end) + queryTree(node * 2 + 1, mid + 1, right, start, end);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    treeHeight = ceil(log2(n));
    treeSize = 1 << (treeHeight + 1);

    // 처음에 모든 세그먼트 트리의 lazy는 0.
    // 초기에 모든 스위치의 상태는 꺼져있는 상태이므로 모든 값 0으로 설정한다.
    tree.resize(treeSize, {0, 0});

    while (m--) {
        int option; cin >> option;
        
        // a[i], a[i + 1], ... , a[j]번째 스위치의 상태를 반전시킨다.
        if (option == 0) {
            int i, j; cin >> i >> j;
            updateTree(1, 0, n - 1, i - 1, j - 1, 1);
        }

        // a[x]를 출력한다.
        else {
            int x, y; cin >> x >> y;
            cout << queryTree(1, 0, n - 1, x - 1, y - 1) << "\n";
        }
    }

    return 0;
}