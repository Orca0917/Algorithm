#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int n, c;
int cost[9][9];
vector<int> permu;
vector<pii> v;
vector<pii> roads;

int ccw(pii p1, pii p2, pii p3) {
    int s = p1.first * p2.second + p2.first * p3.second + p3.first * p1.second;
    s -= (p1.second * p2.first + p2.second * p3.first + p3.second * p1.first);

    if (s > 0) return 1;
    else if (s == 0) return 0;
    else return -1;
}

bool is_equal(pii x, pii y) {
    return x.first == y.first && x.second == y.second;
}

bool is_intersect(int idx1, int idx2, int idx3, int idx4) {


    pii p1 = v[idx1], p2 = v[idx2], p3 = v[idx3], p4 = v[idx4];

    // 특정 도시에서 접하는 경우는 교차에서 제외
    if (is_equal(p1, p3) || is_equal(p1, p4) || is_equal(p2, p3) || is_equal(p2, p4)) return false;
    
    int p1p2 = ccw(p1, p2, p3) * ccw(p1, p2, p4); // l1 기준
    int p3p4 = ccw(p3, p4, p1) * ccw(p3, p4, p2); // l2 기준

    // 두 직선이 일직선 상에 존재
    if (p1p2 == 0 && p3p4 == 0) {
        // 비교를 일반화하기 위한 점 위치 변경
        if (p1 > p2) swap(p2, p1);
        if (p3 > p4) swap(p3, p4);
        
        return p3 <= p2 && p1 <= p4;
    }
    
    return p1p2 <= 0 && p3p4 <= 0;    
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int tc = 1;
    while (true) {
        cin >> n >> c;
        if (n == 0 && c == 0) break;

        // 전역변수 초기화
        memset(cost, 0, sizeof(cost));
        v.clear();
        permu.clear();
        roads.clear();

        // n개의 도시의 위치 입력 받기
        v.resize(n);
        for (pii &e : v) cin >> e.first >> e.second;

        // 각 도시 사이를 잇는 다리를 건설하는데 필요한 비용
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                cin >> cost[i][j];

        // 도시를 잇는 다리를 사이클의 형태로 생성
        // 도시를 정렬할 수 있는 경우의 수 최대 : 8! = 40320
        for (int i = 0; i < n; ++i) permu.push_back(i);
        
        int answer = 1e9;
        
        do {
            int cur_cost = 0;
            roads.clear(); // 현재 건설된 다리의 목록 초기화

            for (int i = 0; i < n; ++i) {
                int here = permu[i];
                int there = permu[(i + 1) % n];

                cur_cost += cost[here][there];
                roads.push_back({here, there});

                here = there;
            }

            for (int i = 0; i < n; ++i)
                for (int j = i + 1; j < n; ++j)
                    if (is_intersect(roads[i].first, roads[i].second, roads[j].first, roads[j].second))
                        cur_cost += c;

            answer = min(answer, cur_cost);

        } while (next_permutation(permu.begin(), permu.end()));

        cout << tc++ << ". " << answer << "\n";
    }
    
    return 0;
}