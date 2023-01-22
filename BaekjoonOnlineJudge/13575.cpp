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
        for (int i = 0; i < n; ++i) {
            f[i] /= n;
            f[i] = cpx(round(f[i].real()), round(f[i].imag()));
        }
}

vector<int> multiply(vector<int> &v1, vector<int> &v2) {
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

    vector<int> ret(sz);
    for (int i = 0; i < sz; ++i) {
        ret[i] = (int)round(a[i].real());
        if (ret[i] > 0) ret[i] = 1;
    }
    return ret;
}


vector<int> solve(vector<int> f, int exp) {
    vector<int> ret(f.begin(), f.end());
    while (exp) {
        if (exp & 1) ret = multiply(ret, f);
        f = multiply(f, f);
        exp /= 2;
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n, k; cin >> n >> k;

    vector<int> v(1024, 0);
    while (n--) {
        int a; cin >> a;
        v[a] = 1;
    }

    vector<int> result = solve(v, k - 1);
    for (int i = 0; i < result.size(); ++i) {
        if (result[i] > 0) cout << i << " ";
    }
    
    return 0;
}