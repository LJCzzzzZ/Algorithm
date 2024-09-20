#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define se second
#define mp make_pair
#define pii pair<int, int>
const int N = 4040, mod = 998244353;
ll fac[N], ifac[N];
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
    // 题意: 给定一张完全图, 并去掉一个子图(满足是一棵树), 问在剩下的边中任选n-1条满足任意两条边没有公共点的方案数
    // 题解: 容斥 + 树形dp
    // 先求出树上以0为根选了x条边的方案数dp(0,x,0/1), 那么x条边的总方案数为dp * (剩下的点两两配对的方案数)
    // 一堆点分为两两配对的方案数 = C(a * 2, a) * a! / 2^a   即先分为两边, 然后第一个点有a中连接方式 第二个有b种...
    // 每两条边可以调换会重复, 除2^a
    // 那么根据容斥可得 总方案数 = (-1)^i * 选i条树边的方案数 * 两两配对方案数
    
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
        return fac[a] * ifac[a - b] % mod * ifac[b] % mod;
    };

    int n;
    cin >> n;
    n *= 2;
    vector<vector<int>> adj(n);
    for(int i = 0; i < n - 1; i++ ){
        int x, y;
        cin >> x >> y;
        x--, y--;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    vector<int> siz(n, 1);
    vector<vector<vector<ll>>> dp(n, vector<vector<ll>> (n / 2 + 2, vector<ll> (2)));
    // dp[i][j][k] 以i为根的子树还有j个子节点没选 [0/1]是否选自己的方案数
    auto dfs = [&](auto self, int x, int fa) -> void {
        dp[x][0][0] = 1;
        for(auto u : adj[x]){
            if(u == fa){
                continue;
            }
            self(self, u, x);
            vector<vector<ll>> np(siz[x] / 2 + siz[u] / 2 + 2, vector<ll> (2));
            for(int i = 0; i <= siz[x] / 2; i++ ){
                for(int j = 0; j <= siz[u] / 2; j++ ){
                    // 不选自己
                    np[i + j][0] += dp[x][i][0] * (dp[u][j][0] + dp[u][j][1]) % mod;
                    np[i + j][0] %= mod;

                    // 选自己 不合并
                    np[i + j][1] += dp[x][i][1] * (dp[u][j][0] + dp[u][j][1]) % mod;
                    np[i + j][1] %= mod;

                    // 选自己 合并
                    np[i + j + 1][1] += dp[x][i][0] * dp[u][j][0];
                    np[i + j + 1][1] %= mod;
                }
            }
            for(int i = 0; i <= siz[x] / 2 + siz[u] / 2 + 1; i++ ){
                for(int j = 0; j < 2; j++ ){
                    dp[x][i][j] = np[i][j];
                }   
            }
            siz[x] += siz[u];
        }
    };
    dfs(dfs, 0, -1);
    
    ll ans = 0;
    for(int i = 0; i <= n / 2; i++ ){
        int x = i * 2, y = n - x;
        ll res = C(y, y / 2) * fac[y / 2] % mod * ksm(ksm(2, y / 2), mod - 2) % mod;
        ll cur = (dp[0][i][0] + dp[0][i][1]) % mod;
        if(i % 2 == 0){
            ans = (ans + cur * res % mod) % mod;
        } else {
            ans = ((ans - cur * res % mod + mod) % mod + mod) % mod;
        }
    }
    cout << ans << "\n";
    return 0;
}