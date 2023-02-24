#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define sin first
#define ssun second

using namespace std;

vector<pii> v;
int answer = 1e9;

void back_track(int food, int sinmat, int ssunmat) {
    if (food == v.size()) {
        if (sinmat == 1 && ssunmat == 0) return;
        answer = min(answer, abs(sinmat - ssunmat));
        return;
    }

    back_track(food + 1, sinmat, ssunmat);
    sinmat *= v[food].sin;
    ssunmat += v[food].ssun;
    back_track(food + 1, sinmat, ssunmat);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n; cin >> n;
    v.resize(n);

    for (int i = 0; i < n; ++i) {   
        cin >> v[i].sin >> v[i].ssun;
    }

    back_track(0, 1, 0);

    cout << answer << "\n";

    return 0;
}