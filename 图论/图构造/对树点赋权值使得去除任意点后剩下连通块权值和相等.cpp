#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define se second
#define mp make_pair
#define pii pair<int, int>

void solve(){
    // 问: 对树上点任意赋值使得删除任意一点后剩余连通块权值和相等
    // 对树上点权赋值使得整体权值和为0, 二分图染色, 对黑点赋值为度数正值, 对白点赋值为度数负值
    // 简单证明: 相邻两点异色, 分别贡献+1 和 -1 且分别对应每一条边, 因此总和为0
    // 而去除一点相当于去除该点所有的边, 对于剩余块恰好为0
    int n;
    cin >> n;
    vector<vector<int>> adj(n);
    for(int i = 0; i < n - 1; i++ ){
        int x, y;
        cin >> x >> y;
        x--, y--;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    vector<int> ans(n);
    auto dfs = [&](auto self, int x, int fa, int col) -> void {
        if(col & 1){
            ans[x] = (int)adj[x].size();
        } else {
            ans[x] = -(int)adj[x].size();
        }
        for(auto u : adj[x]){
            if(u == fa){
                continue;
            }
            self(self, u, x, 1 - col);
        }
    };
    dfs(dfs, 0, -1, 0);
    for(int i = 0; i < n; i++ ){
        cout << ans[i] << " \n"[i == n - 1];
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