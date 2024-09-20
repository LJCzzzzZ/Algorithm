#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define se second
#define mp make_pair
#define pii pair<int, int>

vector<int> fa, height, in, seq, stk, dep, ans, f, k;
vector<vector<int>> adj, que;
int main() 
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    fa.resize(n);
    height.resize(n);
    in.resize(n);
    dep.resize(n);
    adj.resize(n);
    que.resize(n);
    f.resize(n);
    for(int i = 0; i < n; i++ ){
        cin >> fa[i];
        fa[i]--;
        if(fa[i] != -1){
            adj[fa[i]].push_back(i);
        }
    }

    int m;
    cin >> m;
    ans.resize(m);
    k.resize(m);
    for(int i = 0; i < m; i++ ){
        int x;
        cin >> x >> k[i];
        x--;
        que[x].push_back(i);
    }

    // 离线求树上结点的k级祖先时, 直接用vector 存根结点到该结点的所有祖先可以快速找到
    auto dfs1 = [&](auto self, int x) -> void {
        stk.push_back(x);
        for(auto i : que[x]){
            if(dep[x] >= k[i]){
                ans[i] = stk[dep[x] - k[i]];
            } else {
                ans[i] = -1;
            }
        }

        height[x] = 1;
        for(auto &u : adj[x]){
            dep[u] = dep[x] + 1;
            self(self, u);
            height[x] = max(height[x], height[u] + 1);
            if(height[u] > height[adj[x][0]]){
                swap(u, adj[x][0]);
            }
        }
        stk.pop_back();
    };
    for(int i = 0; i < n; i++ ){
        if(fa[i] == -1){
            dfs1(dfs1, i);
        }
    }

    for(int i = 0; i < n; i++ ){
        que[i].clear();
    }
    for(int i = 0; i < m; i++ ){
        if(ans[i] == -1){
            ans[i] = 0;
        } else {
            que[ans[i]].push_back(i);
        }
    }

    int cnt = 0;
    auto dfs2 = [&](auto self, int x) -> void {
        in[x] = cnt++;
        f[in[x]] = 1;

        for(auto u : adj[x]){
            self(self, u);
            if(u != adj[x][0]){ // 合并轻边的
                for(int i = 0; i < height[u]; i++ ){
                    f[in[x] + i + 1] += f[in[u] + i];
                }
            }
        }
        for(int i : que[x]){
            ans[i] = f[in[x] + k[i]] - 1;
        }
    };
    for(int i = 0; i < n; i++ ){
        if(fa[i] == -1){
            dfs2(dfs2, i);
        }
    }

    for(int i = 0; i < m; i++ ){
        cout << ans[i] << " \n"[i == m - 1];
    }
    return 0;
}