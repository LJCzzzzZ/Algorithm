#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define se second
#define mp make_pair
#define pii pair<int, int>

void solve(){
    // 题意： 给定一棵树, 每个结点有权值, 删一个结点要么用魔法, 要么用自己结点权值 + 儿子结点权值之和为代价, 问最多用0 ~ m次魔法最小代价
    // 题解: 树形背包 + 枚举优化
    // dp[i][j][0 / 1] 以i为根的子树, 用了j次魔法, 根是否是用魔法删的最小代价
    // dp[i][j][0] = min(dp[i][j][0], dp[u][j - k][0] + a[u]);
    // dp[i][j][0] = min(dp[i][j][0], dp[u][j - k][1]);
    // dp[i][j][1] = min(dp[i][j][1], dp[u][j - k][0]);
    // dp[i][j][1] = min(dp[i][j][1], dp[u][j - k][1]);
    int n;
    cin >> n;
    vector<vector<int>> adj(n);
    for(int i = 1; i < n; i++ ){
        int x;
        cin >> x;
        x--;
        adj[x].push_back(i);
    }

    vector<int> a(n);
    for(int i = 0; i < n; i++ ){
        cin >> a[i];
    }

    vector<int> siz(n, 1);
    vector<vector<vector<ll>>> dp(n + 1, vector<vector<ll>> (n + 1, vector<ll> (2, 2e18)));
    auto dfs = [&](auto self, int x, int fa) -> void {
        dp[x][0][0] = a[x];
        dp[x][1][1] = 0;
        int m = adj[x].size();
        int sum = 1;
        for(int i = 0; i < m; i++ ){
            int u = adj[x][i];
            if(u == fa){
                continue;
            }
            self(self, u, x);
            siz[x] += siz[u]; // 当前子树已经枚举的最大值
            vector<vector<ll>> np(siz[x] + 1, vector<ll> (2, 2e18));
            // 正确做法: 先枚举x整棵子树还没加入u之前的大小, 然后枚举u子树大小 用dp[j]和dp[k]更新dp[x][j + k] 复杂度O(siz[x] * siz[u])
            // 错误做法: 先枚举x整棵子树加入u之后大小, 然后枚举u子树大小, 复杂度O((siz[x] + siz[u]) * siz[u]), 有很多枚举没有实际用到
            for(int j = sum; j >= 0; j-- ){ // 加入前大小
                for(int k = siz[u]; k >= 0; k-- ){ // 儿子子树大小
                    int z = j + k;
                    np[z][0] = min(np[z][0], dp[x][j][0] + dp[u][k][0] + a[u]);
                    np[z][0] = min(np[z][0], dp[x][j][0] + dp[u][k][1]);
                    np[z][1] = min(np[z][1], dp[x][j][1] + dp[u][k][0]);
                    np[z][1] = min(np[z][1], dp[x][j][1] + dp[u][k][1]);
                }
            }
            sum += siz[u];
            for(int j = 0; j <= siz[x]; j++ ){
                dp[x][j][0] = np[j][0];
                dp[x][j][1] = np[j][1];
            }
        }
    };
    dfs(dfs, 0, -1);
    for(int i = 0; i <= n; i++ ){
        cout << min(dp[0][i][0], dp[0][i][1]) << " \n"[i == n];
    }
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

/*
1
5
1 2 3 4
1 2 3 4 5
*/