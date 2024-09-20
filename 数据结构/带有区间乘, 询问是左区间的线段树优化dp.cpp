#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define se second
#define mp make_pair
#define pii pair<int, int>
const int mod = 998244353, N = 1e5 + 10;
struct node{
    int l, r;
    ll sum, add;
}tr[2][N << 2];

void pushup(int c, int u){
    tr[c][u].sum = (tr[c][u << 1].sum + tr[c][u << 1 | 1].sum) % mod;
}

void pushdown(int c, int u){
    if(tr[c][u].add != 1){
        ll p = tr[c][u].add;
        tr[c][u << 1].sum = tr[c][u << 1].sum * p % mod;
        tr[c][u << 1 | 1].sum = tr[c][u << 1 | 1].sum * p % mod;

        tr[c][u << 1].add = tr[c][u << 1].add * p % mod;
        tr[c][u << 1 | 1].add = tr[c][u << 1 | 1].add * p % mod;
        tr[c][u].add = 1;
    }
}
void build(int c, int u, int l, int r){
    tr[c][u].l = l, tr[c][u].r = r;
    if(l == r){
        tr[c][u].sum = 0;
        tr[c][u].add = 1;
    } else {
        int mid = l + r >> 1;
        build(c, u << 1, l, mid);
        build(c, u << 1 | 1, mid + 1, r);
        pushup(c, u);
    }
}

void modify_add(int c, int u, int pos, ll w){
    if(tr[c][u].l == tr[c][u].r){
        tr[c][u].sum = (tr[c][u].sum + w) % mod;
    } else {
        pushdown(c, u);
        int mid = tr[c][u].l + tr[c][u].r >> 1;
        if(pos <= mid) modify_add(c, u << 1, pos, w);
        else modify_add(c, u << 1 | 1, pos, w);
        pushup(c, u);
    }
}

void modify_mul(int c, int u, int pos){
    if(tr[c][u].r <= pos){
        tr[c][u].sum = tr[c][u].sum * 2 % mod;
        tr[c][u].add = tr[c][u].add * 2 % mod;
    } else {
        pushdown(c, u);
        int mid = tr[c][u].l + tr[c][u].r >> 1;
        modify_mul(c, u << 1, pos);
        if(pos > mid) modify_mul(c, u << 1 | 1, pos);
        pushup(c, u);
    }
}

ll query(int c, int u, int pos){
    if(tr[c][u].r <= pos){
        return tr[c][u].sum;
    } else {
        pushdown(c, u);
        int mid = tr[c][u].l + tr[c][u].r >> 1;
        return (query(c, u << 1, pos) + (pos > mid ? query(c, u << 1 | 1, pos) : 0)) % mod;
    }
}
void solve(){
    // 题意: 给n条线段[L, R, c] 求取任意条线段使得任意两条不同色线段之间不相交的方案数
    // 题解: 定义dp(i, j, k) 为前i条线段中, 第i条必须取, 当前颜色为k, 上一次与自己颜色不同的的最右线段为j的方案数
    // dp(i, j, k) = Σf(j, k ^ 1)
    // 当前线段颜色为c, 左边界为L, 那么之后的线段对于颜色c^1来说 若以L为边界 当前线段可取可不取, 给 0 ~ L 之前所有颜色c^1的线段答案乘2
    int n;
    cin >> n;
    vector<tuple<int, int, int>> seg(n + 1);
    for(int i = 1; i <= n; i++ ){
        int l, r, c;
        cin >> l >> r >> c;
        seg[i] = make_tuple(l, r, c);
    }
    sort(seg.begin() + 1, seg.end(), [&](tuple<int, int, int> a, tuple<int, int, int> b){
        return get<1>(a) < get<1>(b);
    });

    for(int i = 0; i < 2; i++ ){
        build(i, 1, 0, n);
        modify_add(i, 1, 0, 1);
    }
    ll ans = 1;
    for(int i = 1; i <= n; i++ ){
        auto [L, R, c] = seg[i]; 
        int low = 0, high = i - 1;
        while(low < high){
            int mid = low + high + 1 >> 1;
            if(get<1>(seg[mid]) < L) low = mid;
            else high = mid - 1;
        }
        ll val = query(c ^ 1, 1, low);
        modify_add(c, 1, i, val);
        modify_mul(c ^ 1, 1, low);
        ans = (ans + val) % mod;
    }
    cout << ans << "\n";
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