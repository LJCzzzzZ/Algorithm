#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define se second
#define mp make_pair
#define pii pair<int, int>

void solve(){
    // 题意: (1). 在一个有向无环图中判断是否存在一个大小为k的团, 团: k个点之间都有一条边相连的完全图 
    //       (2). 是否存在一个集合, 使得集合内的每个点都至少有k个点出现在集合中
    // 题解: (1). 从队列中每次取出当前度数小于k的点, 度数小于 k - 1的点必定不是团中的点, 把该点的影响全部消除, 一直模拟
    //       当前点的度数为 k - 1说明可能是团上的点, 两层循环遍历这k个点用二分看在这k个点中其他k-1个点之间是否连边
    //       若全部之间连边则是团。
    //       (2). 将所有 度数小于k的点去除, 并消除影响, 一直模拟下去, 若最后集合中还剩下有点说明存在, 即剩下所有点组成一个集合
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<int>> adj(n);
    for(int i = 0; i < m; i++ ){
        int x, y;
        cin >> x >> y;
        x--, y--;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    vector<int> deg(n);
    vector<int> vis(n);
    queue<int> q;
    for(int i = 0; i < n; i++ ){
        sort(adj[i].begin(), adj[i].end());
        deg[i] = adj[i].size();
        if(deg[i] < k){
            vis[i] = 1;
            q.push(i);
        }
    }

    vector<int> clique;
    while(!q.empty()){
        auto x = q.front();
        q.pop();
        vis[x] = 2;
        if(deg[x] == k - 1 && clique.empty() && 1ll * k * (k - 1) / 2 <= m){
            clique.push_back(x);
            for(auto u : adj[x]){
                if(vis[u] <= 1){
                    clique.push_back(u);
                }
            }
            bool ok = true;
            for(auto u : clique){
                for(auto v : clique){
                    if(u == v){
                        break;
                    }
                    if(!binary_search(adj[u].begin(), adj[u].end(), v)){
                        ok = false;
                    }
                }
            }
            if(!ok){
                clique.clear();
            }
        }
        for(auto u : adj[x]){
            deg[u] -= 1;
            if(!vis[u] && deg[u] < k){
                vis[u] = 1;
                q.push(u);
            }
        }
    }

    if(count(vis.begin(), vis.end(), 0) > 0){
        vector<int> ans;
        for(int i = 0; i < n; i++ ){
            if(!vis[i]){
                ans.push_back(i);
            }
        }
        cout << 1 << " " << (int)ans.size() << "\n";
        for(auto x : ans){
            cout << x + 1 << " ";
        }
        cout << "\n";
    } else if(!clique.empty()){
        cout << 2 << "\n";
        for(auto x : clique){
            cout << x + 1 << " ";
        }
        cout << "\n";
    } else {
        cout << "-1\n";
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