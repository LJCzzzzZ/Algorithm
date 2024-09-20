#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define se second
const int N = 5e5 + 10, LOG = 20;
#define ui unsigned int
ui s;
// 深度，部分链长，父节点，重儿子，链头，dfs序，子树最大dfs序，dfs序对应节点
int dep[N], len[N], fa[N], hson[N], top[N], in[N], out[N], node[N], cnt; 
int f[N][LOG];
vector<int> adj[N]; 
void dfs1(int x, int d){
    len[x] = 1, dep[x] = d;
    for(auto u : adj[x]){
        if(dep[u] == 0){
            dfs1(u, d + 1);
            fa[u] = x;
            f[u][0] = x;
            if(len[u] + 1 > len[x]){ // 更新重儿子
                hson[x] = u;
                len[x] = len[u] + 1;
            }
        }
    }
}
void dfs2(int x, int topf){
    in[x] = ++cnt;
    top[x] = topf;
    node[cnt] = x;
    if(hson[x]){
        dfs2(hson[x], topf);
    }
    for(auto u : adj[x]){
        if(!top[u]){
         dfs2(u, u);
        } 
    }
    out[x] = cnt;
}
void cut(int r){
    dfs1(r, 1);
    dfs2(r, r);
}
// 祖先(不包括自己), 儿子(包括自己)
vector<int> anc[N], des[N];
void init(int r, int n){
    cut(r); // 长链剖分
    for(int i = 1; i < LOG; i++ ){
        for(int j = 1; j <= n; j++ ){
            f[j][i] = f[f[j][i - 1]][i - 1];
        }
    }
    for(int i = 1; i <= n; i++ ){
        if(top[i] == i){
            // 往上存祖先
            for(int j = 0, p = i; j < len[i]; j++, p = f[p][0]){
                anc[i].push_back(p);
            }
            // 往下存儿子
            for(int j = 0; j < len[i]; j++ ){
                des[i].push_back(node[in[i] + j]);
            }
        } 
    }
}
int query(int p, int k){
    if(k == 0){ // 特判
        return p;
    }
    int r = __lg(k);
    int q = f[p][r]; // p的2^r级祖先  
    int tp = top[q]; // q的链头结点
    int d = k - (1 << r) + dep[tp] - dep[q];
    if(d > 0){ // 正的在祖先
        return anc[tp][d];
    } else { // 在儿子
        return des[tp][-d];
    }
}
inline ui get(ui x) {
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    return s = x; 
}
int main() 
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q >> s;
    int root = 0;
    for(int i = 1; i <= n; i++ ){
        int x;
        cin >> x;
        if(x == 0){
            root = i;
        } else {
            adj[x].push_back(i);
        }
    }

    init(root, n);
    ll ans = 0;
    int lastans = 0;
    for(int i = 1; i <= q; i++ ){
        int x = (get(s) ^ lastans) % n + 1;
        int k = (get(s) ^ lastans) % dep[x];
        lastans = query(x, k);
        ans ^= 1ll * i * lastans;
    }
    cout << ans << "\n";
    return 0;
}