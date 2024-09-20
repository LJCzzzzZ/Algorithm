#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define se second

int main() 
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vector<vector<int>> adj(n);
    for(int i = 0; i < n - 1; i++ ){
        int x, y;
        cin >> x >> y;
        x--, y--;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    vector<int> a;
    auto dfs = [&](auto self, int x, int fa) -> int {
        int d = 0; // 当前深度
        for(auto u : adj[x]){
            if(u == fa) continue;

            int y = self(self, u, x); // 当前遍历的子节点的深度
            if(y > d){ // 取最长子链
                swap(d, y);
            }
            a.push_back(y); // 短的子链y一定不是长链, 放进集合中
        }
        return d + 1; // 返回长链
    };
    a.push_back(dfs(dfs, 0, -1));
    sort(a.rbegin(), a.rend());

    
    return 0;
}