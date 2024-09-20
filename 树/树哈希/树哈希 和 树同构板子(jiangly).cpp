#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define se second

vector<bool> sym;
map<vector<int>, int> tree;
void solve(){
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

    auto dfs = [&](auto self, int x, int fa) -> int {
        vector<int> a;
        for(auto u : adj[x]){
            if(u == fa) continue;
            a.push_back(self(self, u, x));
        }
        sort(a.begin(), a.end());
        
        if(tree.find(a) == tree.end()){ // 没有当前树型
            tree[a] = sym.size(); //当前sym数组大小即为新的树类型的编号
            int i = 0;
            while(i + 1 < a.size() && a[i] == a[i + 1]){
                i += 2;
            }
            bool ok = true;
            if(i < a.size()){
                if(!sym[a[i]]){
                    ok = false;
                } 
                i += 1;
                while(i + 1 < a.size() && a[i] == a[i + 1]){
                    i += 2;
                }
                if(i != a.size()){
                    ok = false;
                }
            }
            sym.push_back(ok);
        }
        return tree[a];
    };

    int x = dfs(dfs, 0, -1);
    if(sym[x]){
        cout << "YES\n";
    } else {
        cout << "NO\n";
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