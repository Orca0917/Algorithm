#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define cpx complex<double>

using namespace std;

bool is_prime[1'000'001];

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

vector<cpx> multiply(vector<int> v) {
    vector<cpx> a(v.begin(), v.end());
    vector<cpx> ret(1 << 20);

    FFT(a, false);
    for (int i = 0; i < (1 << 20); ++i) ret[i] = a[i] * a[i];
    FFT(ret, true);

    return ret;
}

void eratos() {
    memset(is_prime, true, sizeof(is_prime));
    is_prime[0] = is_prime[1] = false;

    for (int i = 2; i <= 1'000'000; ++i) {
        for (int j = 2; i * j <= 1'000'000 && is_prime[i]; ++j)
            is_prime[i * j] = false;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    eratos();
    is_prime[2] = 0;

    vector<int> a(1 << 20, 0);
    for (int i = 0; i <= 1'000'000; ++i)
        if (is_prime[i]) a[(i - 1) / 2] = 1;

    vector<cpx> ret = multiply(a);

    int testcase; cin >> testcase;
    while (testcase--) {
        int k; cin >> k;
        if (k == 4) cout << "1\n";
        else cout << ceil(round(ret[k / 2 - 1].real()) / 2) << "\n";
    }

    
    return 0;
}