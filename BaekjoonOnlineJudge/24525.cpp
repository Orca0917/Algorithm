#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

vector<int> arr;
int psum[100'001];
pii skpsum[100'001];

map<int, int> m;
string s;


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    memset(psum, 0, sizeof(psum));
    m.clear();
    arr.clear();

    cin >> s;

    for (char c : s) {
        if (c == 'S') arr.push_back(-2);
        else if (c == 'K') arr.push_back(1);
        else arr.push_back(0);
    }

    skpsum[0] = {s[0] == 'S', s[0] == 'K'};
    for (int i = 1; i < s.length(); ++i) {
        skpsum[i].first = skpsum[i - 1].first + (s[i] == 'S' ? 1 : 0);
        skpsum[i].second = skpsum[i - 1].second + (s[i] == 'K' ? 1 : 0);
    }

    psum[0] = arr[0];
    m[psum[0]] = 0;
    m[0] = -1;

    for (int i = 1; i < s.length(); ++i) {
        psum[i] = psum[i - 1] + arr[i];
        if (m.find(psum[i]) == m.end()) m[psum[i]] = i;
    }

    int answer = -1;
    for (int i = 2; i < s.length(); ++i) {
        int A = psum[i];
        if (m.find(A) != m.end()) {
            int j = m[A];
            int S = skpsum[i].first - (j == -1 ? 0 : skpsum[j].first);
            int K = skpsum[i].second - (j == -1 ? 0 : skpsum[j].second);
            if (S >= 1 && S * 2 == K)
                answer = max(answer, i - j);
        }
    }

    cout << answer << "\n";

    
    return 0;
}