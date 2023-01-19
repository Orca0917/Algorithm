#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long
#define cpx complex<double>

using namespace std;

bool is_prime[1000001];

void FFT(vector<cpx> &f, bool do_inv) {
    int n = f.size();
    
    for (int i = 1, j = 0; i < n; ++i) {
        int bit = n >> 1;
        while (!((j ^= bit) & bit)) bit >>= 1;
        if (i < j) swap(f[i], f[j]);
    }

    for (int i = 1; i < n; i *= 2) {
        double x = (do_inv ? M_PI / i : -M_PI / i);
        cpx w = cpx(cos(x), sin(x));
        for (int j = 0; j < n; j += i << 1) {
            cpx p = cpx(1, 0);
            for (int k = 0; k < i; ++k) {
                cpx tmp = f[i + j + k] * p;
                f[i + j + k] = f[j + k] - tmp;
                f[j + k] += tmp;
                p *= w;
            }
        }
    }

    if (do_inv)
        for (int i = 0; i < n; ++i) f[i] /= n;
}


vector<cpx> multiply(vector<cpx> a, vector<cpx> b) {
    int n = 1;
    while (n <= a.size() || n <= b.size()) n <<= 1;
    n <<= 1;

    a.resize(n);
    b.resize(n);
    vector<cpx> c(n);

    FFT(a, false);
    FFT(b, false);

    for (int i = 0; i < n; ++i) c[i] = a[i] * b[i];

    FFT(c, true);
    for (int i = 0; i < n; ++i) {
        c[i] = cpx(round(c[i].real()), round(c[i].imag()));
    }

    return c;
}

void eratos() {
    memset(is_prime, true, sizeof(is_prime));
    is_prime[0] = is_prime[1] = false;

    for (int i = 2; i <= 1000000; ++i) {
        for (int j = 2; i * j <= 1000000 && is_prime[i]; ++j)
            is_prime[i * j] = false;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    vector<cpx> a(1000001), b(1000001);
    eratos();
    for (int i = 0; i <= 1'000'000; ++i) {
        if (is_prime[i]) {
            a[i] = cpx(1, 0);
            if (i * 2 <= 1000000) b[i * 2] = cpx(1, 0);
        }
    }

    vector<cpx> c = multiply(a, b);
    int testcase; cin >> testcase;
    while (testcase--) {
        int k; cin >> k;
        cout << (int)round(c[k].real()) << "\n";
    }
    
    return 0;
}