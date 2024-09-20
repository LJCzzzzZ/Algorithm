#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define se second
#define mp make_pair
#define pii pair<int, int>
const int N = 1e6 + 10;
ll fac[N], ifac[N];
const int mod = 998244353;
ll ksm(ll a, ll b){
    ll ans = 1;
    while(b){
        if(b & 1) ans = ans * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return ans;
}
int main() 
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    fac[0] = 1;
    for(int i = 1; i < N; i++ ){
        fac[i] = fac[i - 1] * i % mod;
    }
    ifac[N - 1] = ksm(fac[N - 1], mod - 2);
    for(int i = N - 2; i >= 0; i-- ){
        ifac[i] = ifac[i + 1] * (i + 1) % mod;
    } 

    auto C = [&](int a, int b){
        if(a < b) return 0ll;
        return fac[a] * ifac[a - b] % mod * ifac[b] % mod;
    };
    
    ll n, m, k;
    cin >> n >> m >> k;
    if(k == 1){
        cout << 1 << "\n";
        return 0;
    }
    ll ans = 0;
    for(int i = 1; i <= n; i++ ){
        for(int j = 1; j <= m; j++ ){
            ll way = 0;
            for(int x = 0; x <= 2; x++ ){
                for(int y = 0; y <= 2; y++ ){
                    ll t = C((i - x) * (j - y), k) * (x == 1 ? -2 : 1) % mod * (y == 1 ? -2 : 1) % mod;
                    way = ((way + t) % mod + mod) % mod;
                }
            }
            /*
            for(int s = 0; s < 16; s++ ){
                int u = __builtin_popcount(s & 3);
                int v = __builtin_popcount(s & 12);
                way += ((u + v) & ? -1 : 1) * C((i - u) * (j - v), k);        
            }
            */
            ans += 1ll * i * j % mod * (n - i + 1) % mod * (m - j + 1) % mod * way % mod;
            ans %= mod;
        }
    }

    cout << ans * ksm(C(n * m, k), mod - 2) % mod << "\n";

    return 0;
}