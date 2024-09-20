#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define se second
#define mp make_pair
#define pii pair<int, int>
const int mod = 998244353;
const int N = 1e6 + 10, M = 1e6; 
int st[N], p[N], cnt;
void init(){
    for(int i = 2; i <= M; i++ ){
        if(!st[i]) p[++cnt] = i;
        for(int j = 1; p[j] <= M / i; j++ ){
            st[p[j] * i] = 1;
            if(i % p[j] == 0) break;
        }
    }
}
void solve(){
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for(int i = 0; i < n; i++ ){
        cin >> a[i];
    }

    auto calc = [&](int x, int R){
        vector<int> primes;
        for(int i = 1; p[i] <= x / p[i] && i <= cnt; i++ ){
            if(x % p[i] == 0){
                while(x % p[i] == 0){
                    x /= p[i];
                }
                primes.emplace_back(p[i]);
            }
        }
        if(x > 1){
            primes.emplace_back(x);
        }

        int s = primes.size();
        ll res = 0;
        for(int i = 1; i < 1 << s; i++ ){  //从1开始
            int cnt = 0;
            ll mul = 1;
            for(int j = 0; j < s; j++ ){
                if(i >> j & 1){
                    if(mul * primes[j] > R){
                        mul = -1;
                        break;
                    }
                    mul = mul * primes[j];
                    cnt += 1;
                }
            }
            if(mul != -1){
                if(cnt & 1) res += R / mul;
                else res -= R / mul;       
            }
        }
        return R - res;
    };
}
int main() 
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    int T;
    cin >> T;
    while(T--){
        solve();
    }
    return 0;
}