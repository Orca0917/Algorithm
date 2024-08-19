#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

struct square {
    int x, y;
    int p, q;
};

bool overlap_square(square s1, square s2) {
    // 두 사각형이 겹치거나 경계에서 만나는 경우를 포함
    return !(s1.p < s2.x || s1.x > s2.p || s1.q < s2.y || s1.y > s2.q);
}

bool overlap_line(square s1, square s2) {
    // 사각형의 경계선이 정확히 일치하는지 확인
    return (
        (s1.p == s2.x && (s1.y <= s2.q && s1.q >= s2.y)) ||
        (s1.x == s2.p && (s1.y <= s2.q && s1.q >= s2.y)) ||
        (s1.q == s2.y && (s1.x <= s2.p && s1.p >= s2.x)) ||
        (s1.y == s2.q && (s1.x <= s2.p && s1.p >= s2.x))
    );
}

bool overlap_point(square s1, square s2) {
    // 사각형의 꼭짓점이 겹치는지 확인
    return (
        (s1.p == s2.x && s1.q == s2.y) ||
        (s1.x == s2.p && s1.q == s2.y) ||
        (s1.p == s2.x && s1.y == s2.q) ||
        (s1.x == s2.p && s1.y == s2.q)
    );
}

char solve(square s1, square s2) {
    if (overlap_point(s1, s2)) return 'c';
    if (overlap_line(s1, s2)) return 'b';
    if (overlap_square(s1, s2)) return 'a';
    return 'd';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    for (int i = 0; i < 4; ++i) {
        square sq1, sq2;
        cin >> sq1.x >> sq1.y >> sq1.p >> sq1.q;
        cin >> sq2.x >> sq2.y >> sq2.p >> sq2.q;

        cout << solve(sq1, sq2) << "\n";
    }

    return 0;
}
