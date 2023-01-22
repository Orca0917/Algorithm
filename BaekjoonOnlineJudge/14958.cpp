#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define cpx complex<double>

using namespace std;

void FFT(vector<cpx> &f, bool do_inv) {
    int n = (int)f.size();

    for (int i = 1, j = 0; i < n; ++i) {
        int bit = n >> 1;
        while (!((j ^= bit) & bit)) bit >>= 1;
        if (i < j) swap(f[i], f[j]);
    }

    for (int i = 1; i < n; i <<= 1) {
        double x = (do_inv ? M_PI / i : -M_PI / i);
        cpx w = cpx(cos(x), sin(x));
        for (int j = 0; j < n; j += i << 1) {
            cpx p = cpx(1, 0);
            for (int k = 0; k < i; ++k) {
                cpx temp = f[i + j + k] * p;
                f[i + j + k] = f[j + k] - temp;
                f[j + k] += temp;
                p *= w;
            }
        }
    }

    if (do_inv)
        for (int i = 0; i < n; ++i)
            f[i] /= n;
}

vector<cpx> multiply(vector<int> v1, vector<int> v2) {
    vector<cpx> a(v1.begin(), v1.end());
    vector<cpx> b(v2.begin(), v2.end());

    int sz = 1;
    while (sz <= a.size() || sz <= b.size()) sz <<= 1;
    sz <<= 1;

    a.resize(sz);
    b.resize(sz);
    vector<cpx> ret(sz);

    FFT(a, false);
    FFT(b, false);
    for (int i = 0; i < sz; ++i) ret[i] = a[i] * b[i];
    FFT(ret, true);

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n, m; cin >> n >> m;
    string s1, s2; cin >> s1 >> s2;

    vector<pair<char, char>> possib;
    possib.push_back({'R', 'P'});
    possib.push_back({'P', 'S'});
    possib.push_back({'S', 'R'});

    vector<cpx> ret[3];
    for (int i = 0; i < 3; ++i) {
        vector<int> v1, v2;
        for (char c : s1) v1.push_back(c == possib[i].first ? 1 : 0);
        for (char c : s2) v2.push_back(c == possib[i].second ? 1 : 0);
        reverse(v2.begin(), v2.end());
        ret[i] = multiply(v1, v2);
    }

    int answer = 0;
    for (int i = m - 1; i <= n + m - 2; ++i)
        answer = max(answer, (int)(round(ret[0][i].real()) + round(ret[1][i].real()) + round(ret[2][i].real())));
    
    cout << answer << "\n";

    return 0;
}