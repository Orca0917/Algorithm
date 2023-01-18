#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define cpx complex<double>
#define PI acos(-1)

using namespace std;

void FFT(vector<cpx> &f, cpx w) {
    int n = (int)f.size();
    if (n == 1) return;

    vector<cpx> even(n / 2), odd(n / 2);
    for (int i = 0; i < n; ++i) {
        if (i % 2) odd[i / 2] = f[i];
        else even[i / 2] = f[i];
    }

    FFT(even, w * w);
    FFT(odd, w * w);

    cpx wp(1, 0);
    for (int i = 0; i < n / 2; ++i) {
        f[i] = even[i] + wp * odd[i];
        f[i + n / 2] = even[i] - wp * odd[i];
        wp *= w;
    }
}

vector<cpx> multiply(vector<cpx> a, vector<cpx> b) {
    int n = 1;
    while (n <= (int)a.size() || n <= (int)b.size()) n *= 2;
    n *= 2;

    a.resize(n);
    b.resize(n);
    vector<cpx> c(n);

    cpx w(cos(2 * PI / n), sin(2 * PI / n));

    FFT(a, w);
    FFT(b, w);

    for (int i = 0; i < n; ++i)
        c[i] = a[i] * b[i];

    FFT(c, cpx(1, 0) / w);
    for (int i = 0; i < n; ++i) {
        c[i] /= cpx(n, 0);
        c[i] = cpx(round(c[i].real()), round(c[i].imag()));
    }
    return c;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n; cin >> n;
    vector<cpx> a(200001, cpx(0, 0));
    for (int i = 0; i < n; ++i) {
        int k; cin >> k;
        a[k] = cpx(1, 0);
    }
    a[0] = cpx(1, 0);

    vector<cpx> ret = multiply(a, a);
    int answer = 0;

    int m; cin >> m;
    while (m--) {
        int k; cin >> k;
        if (round(ret[k].real()) > 0) ++answer;
    }

    cout << answer << "\n";

    return 0;
}