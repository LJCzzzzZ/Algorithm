#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define se second
#define mp make_pair
#define pii pair<int, int>
const int N = 5e6 + 10, M = 5e6 + 100;
const int INF = 1e9;
int dep[M], in[M], seq[M], fa[M];
int a[M];
set<int> adj[M];
bool isPrime[N];
int primes[N], cnt;
int phi[N];
void init(){
    phi[1] = 1;
    for(int i = 2; i < N; i++){
        if (!isPrime[i]) primes[++cnt] = i, phi[i] = i - 1;
        for(int j = 1; i * primes[j] < N; j++){
            isPrime[i * primes[j]] = 1;
            if (i % primes[j] == 0){
                phi[i * primes[j]] = phi[i] * primes[j];
                break;
            }
            phi[i * primes[j]] = phi[i] * (primes[j] - 1);
        }
    }
}

struct node{
    int l, r, mxdfn, midfn;
    ll sum; 
}tr[100010 * 4];

void pushup(node &a, node &b, node &c){
    a.mxdfn = max(b.mxdfn, c.mxdfn);
    a.midfn = min(b.midfn, c.midfn);
    a.sum = b.sum + c.sum;
}
void pushup(int u){
    pushup(tr[u], tr[u << 1], tr[u << 1 | 1]);
}
void build(int u, int l, int r){
    tr[u].l = l, tr[u].r = r;
    tr[u].mxdfn = 0, tr[u].midfn = INF;
    if(l == r){
        tr[u].mxdfn = tr[u].midfn = in[a[l]];
        tr[u].sum = dep[a[l]];
    } else {
        int mid = l + r >> 1;
        build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
        pushup(u);
    }
}

void modify(int u, int l, int r){
    if(tr[u].l >= l && tr[u].r <= r){
        if(tr[u].mxdfn == 1){
            return;
        }
        if(tr[u].l == tr[u].r){
            int d = tr[u].l;
            a[d] = phi[a[d]];
            tr[u].mxdfn = tr[u].midfn = in[a[d]];
            tr[u].sum = dep[a[d]];
            return;
        }
    }
    int mid = tr[u].l + tr[u].r >> 1;
    if(l <= mid) modify(u << 1, l, r);
    if(r > mid) modify(u << 1 | 1, l, r);
    pushup(u);
}

node query(int u, int l, int r){

    if(tr[u].l >= l && tr[u].r <= r){
        return tr[u];
    } else {
        int mid = tr[u].l + tr[u].r >> 1;
        if(r <= mid) return query(u << 1, l, r);
        else if(l > mid) return query(u << 1 | 1, l, r);
        else {
            node left = query(u << 1, l, r);
            node right = query(u << 1 | 1, l, r);
            node res;
            pushup(res, left, right);
            return res;
        }
    }
}
int main() 
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    init();
    int n, m;
    cin >> n >> m;
    for(int i = 1; i <= n; i++ ){
        cin >> a[i];
        int t = a[i];
        while(t > 1){
            adj[phi[t]].insert(t);
            t = phi[t];
        }
    }
    int ctt = 0;
    auto dfs = [&](auto self, int x) -> void {
        in[x] = ++ctt;
        seq[ctt] = x;
        for(auto u : adj[x]){
            dep[u] = dep[x] + 1;
            fa[u] = x;
            self(self, u);
        }
    };
    dfs(dfs, 1);


    build(1, 1, n);
    while(m--){
        int op, l, r;
        cin >> op >> l >> r;
        if(op == 1){
            modify(1, l, r);
        }

        if(op == 2){
            node tmp = query(1, l, r);
            int a = seq[tmp.mxdfn], b = seq[tmp.midfn];
            while(a != b){
                if(dep[a] > dep[b]){
                    a = fa[a];
                } else {
                    b = fa[b];
                }
            }
            cout << tmp.sum - 1ll * (r - l + 1) * dep[a] << "\n";
        }
    }
    return 0;
}