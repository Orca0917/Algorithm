#include <bits/stdc++.h>
#define pii pair<ll, ll>
#define ll long long
#define cpx complex<long double>
using namespace std;

void FFT(vector<cpx> &f, bool do_inv) {
    int n = (int)f.size();
    for (int i=1,j=0;i<n;i++){
        int bit = n >> 1;
        for (;j>=bit;bit>>=1) j -= bit;
        j += bit;
        if (i < j) swap(f[i],f[j]);
    }
    for (int len=2;len<=n;len<<=1){
        double ang = 2*M_PI/len*(do_inv?-1:1);
        cpx wlen(cos(ang),sin(ang));
        for (int i=0;i<n;i+=len){
            cpx w(1);
            for (int j=0;j<len/2;j++){
                cpx u = f[i+j], v = f[i+j+len/2]*w;
                f[i+j] = u+v;
                f[i+j+len/2] = u-v;
                w *= wlen;
            }
        }
    }
    if (do_inv){
        for (int i=0;i<n;i++) f[i] /= n;
    }
}

ll n;

void multiply(vector<ll> cnt, vector<ll> &ret) {
    vector<cpx> a(cnt.begin(), cnt.end());

    FFT(a, false);
    for (ll i = 0; i < (1 << 20); ++i) a[i] *= a[i];
    FFT(a, true);

    for (ll i = 0; i < a.size(); ++i)
        ret[i % n] += (ll)(a[i].real() + (a[i].real() > 0 ? 0.5 : -0.5));
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n;
    vector<ll> cnt(1 << 20, 0);
    vector<ll> diag(1 << 20, 0);
    for (ll i = 1; i < n; ++i) {
        cnt[(i * i) % n] += 1;
        diag[(2 * i * i) % n] += 1;
    }

    vector<ll> ret(1 << 20);
    multiply(cnt, ret);

    ll answer = 0;
    for (ll i = 0; i < (int)ret.size(); ++i) {
        ll counter = ret[i];
        if (counter == 0 || cnt[i % n] == 0) continue;

        // a^2 + b^2 을 만드는 경우의 수 * c^2을 만들 수 있는 경우의 수
        assert(counter >= diag[i % n]);
        answer += 1LL * ((counter - diag[i % n]) / 2 + diag[i % n]) * cnt[i % n];
    }

    cout << answer << "\n";

    return 0;
}