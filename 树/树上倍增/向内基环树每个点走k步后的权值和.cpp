#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define se second
#define mp make_pair
#define pii pair<int, int>
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
    //题意: 给定一个序列的置换, 每个回合, 将当前数累加, 问k个回合 每个 i的和是多少
    //题解: 可以将连续的置换序列看成一张有向图, 当回合进行到一定时, 所有点要么进入循环当中, 要么结束(为0)
    //      最终整张图将是一颗向内基环树(所有边指向环)
    //性质1: 向内基环树支持倍增
    //性质2: 一个位置k级祖先, 显然可以走(k + 1)步到达(k + 1)级祖先, 又因为二进制赋值显然不会超过限制
    //       那么自己可以获得(k + 1)级祖先的贡献, 而k级祖先也能获得(k + 1)级祖先的贡献
    // 那么从高层到低层更新贡献倍增数组即可
    // 答案为f[0][i] * inv(k)
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    ll k;
    cin >> n >> k;
    vector<int> a(n);
    for(int i = 0; i < n; i++ ){
        cin >> a[i];
        a[i]--;
    }
    vector<ll> b(n);
    for(int i = 0; i < n; i++ ){
        cin >> b[i];
    }

    vector<vector<int>> p(60, vector<int> (n));
    vector<vector<ll>> f(60, vector<ll> (n));
    p[0] = a;
    for(int i = 0; i < 59; i++ ){
        for(int j = 0; j < n; j++ ){
            p[i + 1][j] = p[i][p[i][j]];
        }
    }

    for(int i = 0; i < n; i++ ){
        int x = a[i];
        for(int j = 0; j < 60; j++ ){
            if(k >> j & 1){
                f[j][x] = (f[j][x] + b[i]) % mod;
                x = p[j][x];
            }
        }
    }
    for(int i = 58; i >= 0; i-- ){
        for(int j = 0; j < n; j++ ){
            f[i][j] = (f[i][j] + f[i + 1][j]) % mod;
            f[i][p[i][j]] = (f[i][p[i][j]] + f[i + 1][j]) % mod;
        }
    }

    ll inv = ksm(k % mod, mod - 2) % mod;
    for(int i = 0; i < n; i++ ){
        cout << f[0][i] * inv % mod << " \n"[i == n - 1];
    }
    return 0;
}