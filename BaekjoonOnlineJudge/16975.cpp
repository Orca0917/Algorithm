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
vector<int> arr; // 수열


int treeHeight; // 세그먼트 트리의 높이
int treeSize; // 세그먼트 트리의 크기
vector<pll> tree; // 세그먼트 트리

ll initTree(int node, int left, int right) {
    if (left == right)
        return tree[node].first = arr[left];
    
    else {
        int mid = (left + right) / 2;
        return tree[node].first = initTree(node * 2, left, mid) + initTree(node * 2 + 1, mid + 1, right);
    }
}

// 현재 node가 담고 있는 정보는 [left, right]의 구간이며, 우리가 원하는 구간은 [start, end]이다.
void updateTree(int node, int left, int right, int start, int end, int diff) {
    // 현재 node에 lazy값이 있는 경우
    if (tree[node].second != 0) {
        tree[node].first += (right - left + 1) * tree[node].second;

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
        tree[node].first += (right - left + 1) * diff;

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
ll queryTree(int node, int left, int right, int index) {
    // 현재 노드에 lazy값이 남아 있는 경우
    if (tree[node].second != 0) {
        tree[node].first += (right - left + 1) * tree[node].second;
        
        // 자식이 있는 경우, lazy를 다시 전파한다.
        if (left != right) {
            tree[node * 2].second += tree[node].second;
            tree[node * 2 + 1].second += tree[node].second;
        }

        // 현재 node에 대한 lazy는 처리가 완료되었기 때문에 lazy값을 지운다.
        tree[node].second = 0;
    }

    if (index < left || right < index) return 0;

    if (index <= left && right <= index) return tree[node].first;

    int mid = (left + right) / 2;
    return queryTree(node * 2, left, mid, index) + queryTree(node * 2 + 1, mid + 1, right, index);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    treeHeight = ceil(log2(n));
    treeSize = 1 << (treeHeight + 1);
    tree.resize(treeSize);

    arr.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    // 입력받은 수열을 이용하여 세그먼트 트리를 생성한다.
    initTree(1, 0, n - 1);

    cin >> m;
    while (m--) {
        int option; cin >> option;
        
        // a[i], a[i + 1], ... a[j]에 k를 더한다.
        if (option == 1) {
            int i, j, k; cin >> i >> j >> k;
            updateTree(1, 0, n - 1, i - 1, j - 1, k);
        }

        // a[x]를 출력한다.
        else {
            int x; cin >> x;
            cout << queryTree(1, 0, n - 1, x - 1) << "\n";
        }
    }

    return 0;
}