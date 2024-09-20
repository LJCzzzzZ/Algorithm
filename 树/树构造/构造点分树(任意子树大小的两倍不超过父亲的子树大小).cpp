#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define se second
#define mp make_pair
#define pii pair<int, int>

int main() 
{
    // 题意: 给定一棵树T, 构造一棵树R满足 R上任意两点的lca出现在T中的简单路径中, 且R中任意儿子的两倍小于等于父亲
    // 题解: 构造点分树
    // 步骤: (1). 以任意点为根, 遍历整棵子树, 求出每棵子树的大小, 然后找到最小一点满足 siz[u] * 2 >= 整棵子树大小的点 x 作为当前子树的根
    //       (2). 遍历x的儿子 -> 重复步骤(1) 得到子联通子树的质点v 让v向x连边 即 fa[v] = x;
    // 遍历完即可得到要求的树, 因为每次以质点为根遍历, 子树大小减小一半, 树高为 logn, 至多遍历logn层, 总复杂度O(nlogn) 
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
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

    vector<int> p(n, -2), siz(n);
    vector<bool> vis(n);
    auto dfs = [&](auto self, int x, int fa) -> void {
        siz[x] = 1;
        for(auto u : adj[x]){
            if(vis[u] || u == fa){
                continue;
            }
            self(self, u, x);
            siz[x] += siz[u];
        }
    };
    auto find = [&](auto self, int x, int fa, int s) -> int {
        for(auto u : adj[x]){
            if(u == fa || vis[u] || siz[u] * 2 <= s){
                continue;
            }
            return self(self, u, x, s);
        }
        return x;
    };
    auto solve = [&](auto self, int x) -> int{
        dfs(dfs, x, -1);
        x = find(find, x, -1, siz[x]);
        vis[x] = true;
        for(auto u : adj[x]){
            if(!vis[u]){
                int v = self(self, u);
                p[v] = x;
            }
        }
        return x;
    };
    solve(solve, 0);
    for(int i = 0; i < n; i++ ){
        cout << p[i] + 1 << " \n"[i == n - 1];
    }
    return 0;
}           