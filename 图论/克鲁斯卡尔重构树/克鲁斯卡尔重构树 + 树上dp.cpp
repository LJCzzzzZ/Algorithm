#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define se second
#define mp make_pair
#define pii pair<int, int>
struct DSU {
    std::vector<int> f, siz;
    DSU(int n) : f(n), siz(n, 1) { std::iota(f.begin(), f.end(), 0); }
    int find(int x) {
        while (x != f[x]) x = f[x] = f[f[x]];
        return x;
    }
    bool same(int x, int y) { return find(x) == find(y); }
    bool merge(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) return false;
        siz[x] += siz[y];
        f[y] = x;
        return true;
    }
    int size(int x) { return siz[find(x)]; }
};
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
    // 题意: 给定 n - 1个集合的合并顺序, <x, y> 合并x所在集合A和y所在集合B, 每次合并给 A集合里所有元素加上 A / (A + B) B同理
    //       问最后每个元素的值
    // 题解: 克鲁斯卡尔重构树 + 树上dp
    // 该过程和最小生成树合并过程相同, 每次叠加贡献需要知道两集合大小, 那么可以构建克鲁斯卡尔重构树, 在每次合并创建的虚点保存
    // 合并后的集合大小, 然后自顶向下跑树形dp即可  
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> x(n), y(n);
    for(int i = 0; i < n - 1; i++ ){
        cin >> x[i] >> y[i];
        x[i]--, y[i]--;
    }

    DSU dsu(2 * n);
    vector<int> w(2 * n, 1);
    vector<vector<int>> adj(2 * n);
    int cnt = n - 1;
    for(int i = 0; i < n; i++ ){
        int a = dsu.find(x[i]);
        int b = dsu.find(y[i]);
        if(!dsu.same(a, b)){
            cnt += 1;
            w[cnt] = w[a] + w[b]; 
            dsu.f[a] = dsu.f[b] = dsu.f[cnt] = cnt;
            adj[cnt].push_back(a);
            adj[cnt].push_back(b);
        }
    }

    vector<ll> dp(2 * n);
    auto dfs = [&](auto self, int x) -> void{
        for(auto u : adj[x]){
            dp[u] = dp[x] + w[u] * ksm(w[x], mod - 2) % mod;
            dp[u] %= mod; 
            self(self, u);
        }
    };
    dfs(dfs, cnt);

    for(int i = 0; i < n; i++ ){
        cout << dp[i] << " \n"[i == n - 1];
    }
    return 0;
}