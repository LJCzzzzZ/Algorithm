#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define se second
#define mp make_pair
#define pii pair<int, int>

int main() 
{
    // 题意: 给定一张图, 每次可以选两条有公共点的边删去, 并获得其权值, 问最终权值和最大为多少
    // 题解: tarjan + 思维
    // 对于一个连通块来说, 如果边的数量为偶数, 那么一定可以两两成对消去, 答案为边权之和
    // 如果边数量为奇数, 优先考虑是否有桥, 且该桥要把其余两个分成边数为偶数的块, 若变成
    // 奇数答案只会更差. 选桥最小代价即可, 如果没有, 则任意选一条最小边
    // 复杂度O(n)
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<int> in(n);
    vector<vector<tuple<int, int, int>>> adj(n);
    ll sum = 0;
    for(int i = 0; i < m; i++ ){
        int x, y, w;
        cin >> x >> y >> w;
        x--, y--;
        adj[x].emplace_back(y, w, i);
        adj[y].emplace_back(x, w, i);
        in[x] += 1;
        in[y] += 1;
        sum += w;
    }
    if(m % 2 == 0){
        cout << sum << "\n";
        return 0;
    }
    int cnt = 0;
    vector<int> dfn(n), low(n), siz(n);
    int mi = 1e9, res = 0;
    auto tarjan = [&](auto self, int x, int fa, int type) -> void {
        dfn[x] = low[x] = ++cnt;
        siz[x] = in[x];
        for(auto [u, w, id] : adj[x]){
            if(!dfn[u]){
                self(self, u, x, id);
                siz[x] += siz[u];
                low[x] = min(low[x], low[u]);
                if(dfn[x] < low[u]){
                    if(((siz[u] - 1) / 2) % 2 == 0){
                        mi = min(mi, w);
                    }
                } else {
                    mi = min(mi, w);
                }
            } else if(type != id){
                low[x] = min(low[x], dfn[u]);
                mi = min(mi, w);
            }
            if(dfn[x] < dfn[u]){
                res += 1;
            }
        }
    };
    for(int i = 0; i < n; i++ ){
        if(!dfn[i]){
            mi = 1e9, res = 0;
            tarjan(tarjan, i, i, -1);
            if(res & 1){
                sum -= mi;
            }
        }
    }
    cout << sum << "\n";
    return 0;
}