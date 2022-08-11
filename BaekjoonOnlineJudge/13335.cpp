#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int n;      // 다리를 건너는 트럭의 수
int w;      // 다리의 길이
int L;      // 다리의 최대 하중

vector<int> truck;  // 트럭의 하중 정보
queue<pii> q;  // 다리를 건너는 트럭

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n >> w >> L;

    truck.resize(n);
    for (int &e : truck) cin >> e;

    int elapsed = 0;
    int weight_sum = 0;
    int truck_idx = 0;

    while (true) {
        if (q.empty() && truck_idx == n) break;

        if (!q.empty() && q.front().second == elapsed) {
            weight_sum -= q.front().first;
            q.pop();
        }

        if (truck_idx < n && weight_sum + truck[truck_idx] <= L) {
            q.push({truck[truck_idx], elapsed + w});
            weight_sum += truck[truck_idx];
            ++truck_idx;
        }

        ++elapsed;
    }

    cout << elapsed << "\n";

    return 0;
}