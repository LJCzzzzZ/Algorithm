#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define se second
#define mp make_pair
#define pii pair<int, int>

int main() 
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // 给出一个联通图, 选择一条路径C, 对于剩下的点要么分配给A, 要么分配給B, 且集合A中的点与集合B中的点不连通
    // 任选一个点dfs, 对于没被遍历的点分配给A, 被遍历过且退出了的点分配给B, 当A == B时即为所求
    // dfs遍历保证了A与B的点联通
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n);
    for(int i = 0; i < m; i++ ){
        int x, y;
        cin >> x >> y;
        x--, y--;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    vector<int> vis(n);
    int a = n, b = 0;
    vector<int> path;
    auto dfs = [&](auto self, int x, int fa) -> bool {
        vis[x] = 1;
        a -= 1;
        path.push_back(x);
        if(a == b){
            return true;
        }
        for(auto u : adj[x]){
            if(u == fa || vis[u] != 0){
                continue;
            }
            if(self(self, u, x)){
                return true;
            }
        }
        path.pop_back();
        vis[x] = 2;
        b += 1;
        if(a == b){
            return true;
        }
        return false;
    };
    dfs(dfs, 0, -1);
    cout << path.size() << " " << a << "\n";
    for(auto x : path){
        cout << x + 1 << " ";
    }
    cout << "\n";
    for(int i = 0; i < n; i++ ){
        if(vis[i] == 0){
            cout << i + 1 << " ";
        }
    }
    cout << "\n";
    for(int i = 0; i < n; i++ ){
        if(vis[i] == 2){
            cout << i + 1 << " ";
        }
    }
    cout << "\n";
    return 0;
}