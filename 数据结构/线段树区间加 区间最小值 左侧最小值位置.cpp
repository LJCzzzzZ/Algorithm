const int N = 2e5 + 10;
struct node{
    int l, r;
    ll mi;
    ll add;
}tr[N << 2];
int a[N];
void pushup(int u){
    tr[u].mi = min(tr[u << 1].mi, tr[u << 1 | 1].mi);
}
void pushdown(int u){
    if(tr[u].add){
        tr[u << 1].mi += tr[u].add;
        tr[u << 1 | 1].mi += tr[u].add;
 
        tr[u << 1].add += tr[u].add;
        tr[u << 1 | 1].add += tr[u].add;
 
        tr[u].add = 0;
    }
}
void build(int u, int l, int r){
    tr[u].l = l, tr[u].r = r;
    tr[u].add = 0;
    if(l == r){
        tr[u].mi = a[l];
    } else {
        int mid = l + r >> 1;
        build(u << 1, l, mid);
        build(u << 1 | 1, mid + 1, r);
        pushup(u);
    }
}
void modify(int u, int x){
    if(tr[u].l == tr[u].r){
        tr[u].mi = 2e17;
    } else {
        pushdown(u);
        int mid = tr[u].l + tr[u].r >> 1;
        if(x <= mid) modify(u << 1, x);
        else modify(u << 1 | 1, x);
        pushup(u);
    }
}
 
void modify1(int u, int l, int r, int w){
    if(tr[u].l >= l && tr[u].r <= r){
        tr[u].mi += w;
        tr[u].add += w;
    } else {
        pushdown(u);
        int mid = tr[u].l + tr[u].r >> 1;
        if(l <= mid) modify1(u << 1, l, r, w);
        if(r > mid) modify1(u << 1 | 1, l, r, w);
        pushup(u);
    }
}
 
ll query1(int u, int l, int r){
    if(tr[u].l >= l && tr[u].r <= r){
        return tr[u].mi;
    } else {
        pushdown(u);
        int mid = tr[u].l + tr[u].r >> 1;
        if(r <= mid) return query1(u << 1, l, r);
        if(l > mid) return query1(u << 1 | 1, l, r);
        return min(query1(u << 1, l, r), query1(u << 1 | 1, l, r));
    }
}
 
int query2(int u, ll w){
    if(tr[u].l == tr[u].r){
        return tr[u].l;
    }
    pushdown(u);
    if(tr[u << 1].mi <= w){
        return query2(u << 1, w);
    } else {
        return query2(u << 1 | 1, w);
    }
}