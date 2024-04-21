#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    double x, y, d, t;
    cin >> x >> y >> d >> t;

    double distance = hypot(x, y);
    double answer = distance;  // 그냥 걸어가는 경우

    int full_jumps = floor(distance / d);
    int extra_jumps = ceil(distance / d);

    // 2. 딱 1 번 점프해서 바로 닿는 경우
    if (distance == d) answer = min(answer, t);

    // 3. 2 번 점프해서 닿을 수 있는 경우
    else if (distance < d) answer = min(answer, t * 2);

    else {
        answer = min(answer, extra_jumps * t);
        answer = min(answer, full_jumps * t + (distance - full_jumps * d));
    }

    // 6. 좀 더 점프하고 걷는 경우
    int jumps = extra_jumps;
    double result6 = jumps * t + abs(distance - jumps * d);
    answer = min(answer, result6);

    cout.precision(10);
    cout << fixed << answer << "\n";

    
    return 0;
}