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
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n);
    for(int i = 0; i < m; i++ ){
    	int x, y;
    	cin >> x >> y;
    	x--, y--;
    	if(x == y) continue;
    	adj[x].push_back(y);
    	adj[y].push_back(x);
    }

    vector<int> dfn(n), low(n), ins(n), cut(n);
    vector<int> stk;
    vector<vector<int>> scc(n); 
    int cnt = 0, ctt = 0;
    auto dfs = [&](auto self, int x, int rt) -> void {
    	dfn[x] = low[x] = ++cnt;
    	stk.push_back(x);
    	int flag = 0;
    	if(x == rt && adj[x].empty()){
    		ctt += 1;
    		scc[ctt].push_back(x);
    		return;
    	}
    	for(auto u : adj[x]){
    		if(!dfn[u]){
    			self(self, u, rt);
    			low[x] = min(low[x], low[u]);
    			if(dfn[x] <= low[u]){
    				flag += 1;
    				if(x != rt || flag > 1){
    					cut[x] = 1;
    				}
    				ctt += 1;
    				int z;
    				do{
    					z = stk.back();
    					stk.pop_back();
    					scc[ctt].push_back(z);
    				}while(z != u);
    				scc[ctt].push_back(x);
    			}
    		} else {
    			low[x] = min(low[x], dfn[u]);
    		}
    	}
    };
    for(int i = 0; i < n; i++ ){
    	if(!dfn[i]){
    		dfs(dfs, i, i);
    	}
    }

    cout << ctt << "\n";
    for(int i = 1; i <= ctt; i++ ){
    	cout << (int)scc[i].size() << " ";
    	for(auto x : scc[i]){
    		cout << x + 1 << " ";
    	}
    	cout << "\n";
    }
    return 0;
}