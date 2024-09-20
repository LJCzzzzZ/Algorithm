#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define se second
#define mp make_pair
#define pii pair<int, int>
const int INF = 2e9;
int main() 
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, k;
    cin >> n >> m >> k;
    int s, e;
    cin >> s >> e;
    vector<vector<pair<int, int>>> adj(n);
    for(int i = 0; i < m; i++ ){
        int x, y, w;
        cin >> x >> y >> w;
        adj[x].emplace_back(y, w);
        adj[y].emplace_back(x, w);
    }

    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> q;
    vector<vector<int>> dis(n, vector<int> (k + 1, INF));
    vector<vector<int>> vis(n, vector<int> (k + 1));
    q.emplace(0, 0, s);
    dis[s][0] = 0;
    while(!q.empty()){
        auto [d, t, x] = q.top();
        q.pop();
        if(vis[x][t]) continue;
        vis[x][t] = 1;
        for(auto [u, w] : adj[x]){
            if(dis[u][t] > dis[x][t] + w){
                dis[u][t] = dis[x][t] + w;
                q.emplace(dis[u][t], t, u);
            }
            if(t + 1 <= k && dis[u][t + 1] > dis[x][t]){
                dis[u][t + 1] = dis[x][t];
                q.emplace(dis[u][t + 1], t + 1, u);
            }
        }
    }

    cout << *min_element(dis[e].begin(), dis[e].end()) << "\n";
    return 0;
}