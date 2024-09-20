#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define se second
#define mp make_pair
#define pii pair<int, int>
const int N = 1e5 + 10;
const int M = 1e5 + 5;
struct node{
    int l, r, sum, add;
}tr[N << 2];
void pushup(int u){
    tr[u].sum = min(tr[u << 1].sum, tr[u << 1 | 1].sum);
}
void pushdown(int u){
    if(tr[u].add){
        tr[u << 1].sum += tr[u].add;
        tr[u << 1 | 1].sum += tr[u].add;

        tr[u << 1].add += tr[u].add;
        tr[u << 1 | 1].add += tr[u].add;

        tr[u].add = 0;
    }
}
void build(int u, int l, int r){
    tr[u].l = l, tr[u].r = r, tr[u].sum = 0, tr[u].add = 0;
    if(l == r){
        tr[u].sum = 0;
    } else {
        int mid = l + r >> 1;
        build(u << 1, l, mid);
        build(u << 1 | 1, mid + 1, r);
    }
}
void modify(int u, int l, int r, int w){
    if(tr[u].l >= l && tr[u].r <= r){
        tr[u].add += w;
        tr[u].sum += w;
    } else {
        pushdown(u);
        int mid = tr[u].l + tr[u].r >> 1;
        if(l <= mid) modify(u << 1, l, r, w);
        if(r > mid) modify(u << 1 | 1, l, r, w);
        pushup(u);
    }
}
int query(int u, int l, int r){
    if(tr[u].l >= l && tr[u].r <= r){
        return tr[u].sum;
    } else {
        pushdown(u);
        int mid = tr[u].l + tr[u].r >> 1;
        if(r <= mid) return query(u << 1, l, r);
        if(l > mid) return query(u << 1 | 1, l, r);
        return min(query(u << 1, l, r), query(u << 1 | 1, l, r));
    }
}
void solve(){
    int n, m;
    cin >> n >> m;
    vector<int> p(n);
    for(int i = 0; i < n; i++ ){
        cin >> p[i];
        modify(1, 1, p[i], 1);
    }

    vector<ll> sum(m);
    vector<int> at(m), k(m);
    vector<vector<int>> a(m);
    for(int i = 0; i < m; i++ ){
        cin >> k[i];
        a[i].resize(k[i]);
        for(int j = 0; j < k[i]; j++ ){
            cin >> a[i][j];
            sum[i] += a[i][j];
        }
        at[i] = (sum[i] + k[i] - 1) / k[i];
        modify(1, 1, at[i], -1);
    }
    for(int i = 0; i < m; i++ ){
        modify(1, 1, at[i], 1);
        for(int j = 0; j < k[i]; j++ ){
            ll new_at = (sum[i] - a[i][j] + k[i] - 2) / (k[i] - 1);
            modify(1, 1, new_at, -1);
            // cout << new_at << " " << at[i] <<  "\n";
            cout << (query(1, 1, M) >= 0 ? '1' : '0');
            modify(1, 1, new_at, 1);
        }
        modify(1, 1, at[i], -1);
    }
    cout << "\n";
    for(int i = 0; i < n; i++ ){
        modify(1, 1, p[i], -1);
    }
    for(int i = 0; i < m; i++ ){
        modify(1, 1, at[i], 1);
    }
}
int main() 
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    build(1, 1, N);
    int T;
    cin >> T;
    while(T--){
        solve();
    }
    return 0;
}           