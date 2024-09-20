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
    int n, m, q;
    cin >> n >> m >> q;
    vector<int> in(n), x(m), y(m);
    for(int i = 0; i < m; i++ ){
        cin >> x[i] >> y[i];
        x[i]--, y[i]--;
        in[x[i]]++;
        in[y[i]]++;
    }

    vector<vector<int>> adj(n);
    for(int i = 0; i < m; i++ ){
        int u = x[i], v = y[i];
        if(in[u] > in[v]){
            swap(u, v);
        } else if(in[u] == in[v] && u > v){
            swap(u, v);
        }
        adj[u].push_back(v);
    }

    vector<int> was(n);
    while(q--){
        int k;
        cin >> k;
        vector<int> a(k);
        for(int i = 0; i < k; i++ ){    
            cin >> a[i];
            a[i]--;
            was[a[i]] = 1;
        }
        int ans = 0;
        for(int i = 0; i < k; i++ ){
            for(auto u : adj[a[i]]){
                if(was[u] == 1){
                    ans++;
                }
            }
        }
        cout << ans << "\n";
        for(int i = 0; i < k; i++ ){
            was[a[i]] = 0;
        }
    }
    return 0;
}