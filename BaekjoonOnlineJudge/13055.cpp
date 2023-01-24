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

    a.resize(sz);
    b.resize(sz);

    FFT(a, false);
    FFT(b, false);
    for (int i = 0; i < sz; ++i) a[i] *= b[i];
    FFT(a, true);

    return a;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    string s; cin >> s;
    vector<int> v1(1 << 20), v2(1 << 20);
    int len = s.length();
    for (int i = 0; i < len; ++i) {
        v1[i] = (s[i] == 'B');
        v2[len - i - 1] = (s[i] == 'A');
    }

    vector<cpx> ret = multiply(v1, v2);
    for (int i = len - 2; i >= 0; --i)
        cout << (int)round(ret[i].real()) << "\n";
    
    return 0;
}