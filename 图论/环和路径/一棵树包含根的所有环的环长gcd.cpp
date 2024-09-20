#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define se second
#define mp make_pair
#define pii pair<int, int>

void solve(){
    // 题意: 给定一张有向图, 问走10^100000步后是否能到达1
    // 题解: 因为要走回1, 因此路径肯定由多个含有1的环组成, 因此建新图将不能到达1的去除掉
    //       现在的图为一张含有1的强连通图
    //       多个环走x步等价于 ax + by + cz... = step
    //       根据裴蜀定理有解情况为 gcd(a, b, c, d....) | step
    //       那么现在转化题意, 即求多个环的最大公约数是否整除步数
    //       对于一个环路满足路径上的点距离0的距离依次为 0, 1, 2, ... , x - 1
    //       而 最后一个点x - 1 + 1显然是一个环长
    //       那么答案即为 dep[x] - dep[u] + 1
    //       上述是对于简单环而言的, 对于复杂环来说 gcd(L1, L2) = gcd(L1, L2 - L1)
    //       一条边连接的不同环L1, L2 恰好满足 dep[x] - dep[u] + 1 = L1 - L2
    //       因此答案即为gcd(g, dep[x] - dep[u] + 1) 
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n), e(n);
    for(int i = 0; i < m; i++ ){
        int x, y;
        cin >> x >> y;
        x--, y--;
        adj[x].push_back(y);
        e[y].push_back(x);
    }

    vector<int> dep(n, -1);
    dep[0] = 0;
    auto dfs = [&](auto self, int x) -> void {
        for(auto u : adj[x]){
            if(dep[u] == -1){
                dep[u] = dep[x] + 1;
                self(self, u);
            }
        }
    };
    dfs(dfs, 0);

    vector<int> vis(n);
    auto dfs_R = [&](auto self, int x) -> void {
        vis[x] = 1;
        for(auto u : e[x]){
            if(!vis[u]){
                self(self, u);
            }
        }
    };
    dfs_R(dfs_R, 0);

    for(int i = 0; i < n; i++ ){
        if(!vis[i]){
            dep[i] = -1;
        }
    }

    ll g = 0;
    for(int i = 0; i < n; i++ ){
        if(dep[i] != -1){
            for(auto u : adj[i]){
                if(dep[u] != -1){
                    g = __gcd(g, 1ll * abs(dep[i] - dep[u] + 1));
                }
            }
        }
    }
    if(!g){
        cout << "No\n";
        return;
    }
    while(g % 2 == 0){
        g /= 2;
    }
    while(g % 5 == 0){
        g /= 5;
    }
    cout << (g == 1 ? "Yes" : "No") << "\n";
}
int main() 
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while(T--){
        solve();
    }
    return 0;
}           