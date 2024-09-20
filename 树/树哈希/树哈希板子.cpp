#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define se second
const long long M30 = ((long long) 1 << 30) - 1;
const long long M31 = ((long long) 1 << 31) - 1;
const long long MOD = ((long long) 1 << 61) - 1;
unsigned long long modulo(unsigned long long x){
  unsigned long long xu = x >> 61;
  unsigned long long xd = x & MOD;
  unsigned long long res = xu + xd;
  if (res >= MOD){
    res -= MOD;
  }
  return res;
}
unsigned long long mul(unsigned long long a, unsigned long long b){
  unsigned long long au = a >> 31;
  unsigned long long ad = a & M31;
  unsigned long long bu = b >> 31;
  unsigned long long bd = b & M31;
  unsigned long long mid = au * bd + ad * bu;
  unsigned long long midu = mid >> 30;
  unsigned long long midd = mid & M30;
  return modulo(au * bu * 2 + midu + (midd << 31) + ad * bd);
}
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
void solve(){
    int n;
    cin >> n;
    vector<vector<int>> adj(n);
    for(int i = 0; i < n - 1; i++ ){
        int x, y;
        cin >> x >> y;
        x--;
        y--;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    vector<int> bfs, d(n, -1);
    vector<vector<int>> c(n);
    queue<int> q;
    d[0] = 0;
    q.push(0);
    while(!q.empty()){
        auto x = q.front();
        q.pop();
        bfs.push_back(x);
        for(auto u : adj[x]){
            if(d[u] == -1){
                d[u] = d[x] + 1;
                c[x].push_back(u);
                q.push(u); 
            }
        }
    }
    reverse(bfs.begin(), bfs.end());

    vector<ll> R(n);
    for(int i = 0; i < n; i++ ){ // 对每个深度赋予一个哈希值
        R[i] = modulo(rnd());
    }

    vector<ll> dp(n, 1);
    // 不用排序也能判同构
    for(auto x : bfs){
        for(auto y : c[x]){// 根结点哈希 = 根结点哈希 * (深度哈希 + 子节点哈希) 
            dp[x] = mul(dp[x], modulo(dp[y] + R[d[y]])); 
        }
    }

    vector<int> dp2(n, 1);
    for(auto x : bfs){
        map<ll, vector<int>> mp;
        for(auto y : c[x]){
            mp[dp[y]].push_back(y);
        }

        if(c[x].size() % 2 == 0){
            for(auto [u, v] : mp){
                if(v.size() % 2 == 1){
                    dp2[x] = 0;
                }
            }
        } else {
            vector<int> tmp;
            for(auto p : mp){
                if(p.se.size() % 2 == 1){
                    if(tmp.empty()){
                        tmp = p.se;
                    } else {
                        dp2[x] = 0;
                    }
                } 
            }

            if(dp2[x]){
                dp2[x] = 0;
                if(dp2[tmp[0]]){
                    dp2[x] = 1;
                }
            }
        }
    }

    if(dp2[0]){
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