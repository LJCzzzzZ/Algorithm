#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define se second
#define mp make_pair
#define pii pair<int, int>

int main() 
{
    // 题意: 给定一棵树, 树上每一条边都有一个字母, 树以1为根, 问该树中所有子树的路径中任意排序边后最长回文长度
    // 考虑回文串是由 所有字符出现次数为偶数, 可以有一种字符出现奇数次
    // 总的字符有22种, 考虑映射到二进制位上, 1为奇数, 0为偶数
    // 答案组成: (1)子树的答案 或 (2)以自己为根的路径
    // (1) 直接继承
    // (2) 树上启发式合并: 为什么要用? 在当前遍历子树时要快速知道需要用到的其他子树的信息
    //     树上启发式合并多用桶的思想, 而该题又刚好需要知道 0 - (1 << 22)的各种二进制串的信息
    //     奇数回文串允许有一位不同, 那么可以枚举22个位置异或后的答案是否出现过, 并取最大
    // 更新: 先统计答案再更新子树, 防止子树影响自己
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<vector<pair<int, int>>> adj(n);
    for(int i = 1; i < n; i++ ){
        int p;
        char c;
        cin >> p >> c;
        p--;
        adj[p].emplace_back(i, 1 << (c - 'a'));
    }

    vector<int> siz(n, 1), in(n), out(n), son(n, -1), dep(n), id(n), dp(n);
    int cnt = 0;
    auto dfs0 = [&](auto self, int x) -> void {
        in[x] = cnt++;
        id[in[x]] = x;
        for(auto [u, w] : adj[x]){
            dep[u] = dep[x] + 1;
            dp[u] = dp[x] ^ w;
            self(self, u);
            siz[x] += siz[u];
            if(son[x] == -1 || siz[u] > siz[son[x]]){
                son[x] = u;
            }
        }
        out[x] = cnt;
    };
    dfs0(dfs0, 0);

    vector<int> f(1 << 22, -1), ans(n);
    auto dfs1 = [&](auto self, int x, int del) -> void {
        for(auto [u, w] : adj[x]){
            if(u == son[x]){
                continue;
            }
            self(self, u, 1);
            ans[x] = max(ans[x], ans[u]);
        }
        if(son[x] != -1){
            self(self, son[x], 0);
            ans[x] = max(ans[x], ans[son[x]]);
        }
        auto calc = [&](int z){
            if(f[dp[z]] != -1){
                ans[x] = max(ans[x], dep[f[dp[z]]] + dep[z] - dep[x] * 2);
            }
            for(int i = 0; i < 22; i++ ){
                int s = dp[z] ^ (1 << i);
                if(f[s] != -1){
                    ans[x] = max(ans[x], dep[f[s]] + dep[z] - dep[x] * 2);
                }
            }
        };
        auto update = [&](int z){
            if(f[dp[z]] == -1 || dep[f[dp[z]]] < dep[z]){
                f[dp[z]] = z;
            }
        };
        for(auto [u, w] : adj[x]){
            if(son[x] == u){
                continue;
            }
            for(int i = in[u]; i < out[u]; i++ ){
                calc(id[i]);
            }
            for(int i = in[u]; i < out[u]; i++ ){
                update(id[i]);
            }
        }
        calc(x);
        update(x);
        if(del){
            for(int i = in[x]; i < out[x]; i++ ){
                f[dp[id[i]]] = -1;
            }
        }
    };
    dfs1(dfs1, 0, 1);
    for(int i = 0; i < n; i++ ){
        cout << ans[i] << " \n"[i == n - 1];
    }
    return 0;
}           