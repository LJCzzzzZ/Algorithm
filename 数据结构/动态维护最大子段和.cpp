#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define se second
#define mp make_pair
#define pii pair<int, int>
const int N = 1e6 + 10;
struct node{
    int l, r, suml, sumr, sum, mx;
}tr[N << 2];

void build(int u, int l, int r){
    tr[u].l = l, tr[u].r = r;
    tr[u].sum = tr[u].suml = tr[u].sumr = tr[u].mx = 0;
    if(l == r){
        return;
    } else {
        int mid = l + r >> 1;
        build(u << 1, l, mid);
        build(u << 1 | 1, mid + 1, r);
    }
}

void pushup(int u){
    tr[u].sum = tr[u << 1].sum + tr[u << 1 | 1].sum;
    if(tr[u << 1].sum == tr[u << 1].r - tr[u << 1].l + 1){
        tr[u].suml = tr[u << 1].sum + tr[u << 1 | 1].suml;
    } else {
        tr[u].suml = tr[u << 1].suml;
    }

    if(tr[u << 1 | 1].sum == tr[u << 1 | 1].r - tr[u << 1 | 1].l + 1){
        tr[u].sumr = tr[u << 1 | 1].sum + tr[u << 1].sumr;
    } else {
        tr[u].sumr = tr[u << 1 | 1].sumr;
    }

    tr[u].mx = max({tr[u << 1].mx, tr[u << 1 | 1].mx, tr[u << 1].sumr + tr[u << 1 | 1].suml});
}

void modify(int u, int x, int w){
    if(tr[u].l == tr[u].r){
        tr[u].sum = tr[u].suml = tr[u].sumr = tr[u].mx = w;
    } else {
        int mid = tr[u].l + tr[u].r >> 1;
        if(x <= mid) modify(u << 1, x, w);
        else modify(u << 1 | 1, x, w);
        pushup(u);
    }
}


void solve(){
    // 题意: 给定n个题目的解决时间(满足升序), 一个周期为m, 一个题解决的天为 t[i] / m, 问可以使每个题解决时间同时 +x
    //       最长连续解决题天数为多少 x, x + 1, x + 2, x + 3
    // 题解: 每个题天数顶多加一天, 加两天等于 mod m, 那么只要考虑加 [0, m - 1]
    //       建立解决天数的权值线段树, 线段树维护最长连续子段, 然后按每道题天数加1需要天数排序进行遍历
    //       并用桶维护这一天解决题数, 根据是否有解决题数对线段树进行更新, 每次询问tr[1].mx 即可
    // trick: 在线段树中要用的点位前后多开几个点位, 能极大方便转移或者维护 
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    vector<int> st;
    for(int i = 0; i < n; i++ ){
        cin >> a[i];
        st.push_back(a[i] / m - 1);
        st.push_back(a[i] / m);
        st.push_back(a[i] / m + 1);
        st.push_back(a[i] / m + 2);
    }
    sort(st.begin(), st.end());
    st.erase(unique(st.begin(), st.end()), st.end());
    auto find = [&](int x){
        return lower_bound(st.begin(), st.end(), x) - st.begin();
    };

    int sz = st.size() + 3;
    build(1, 0, sz);
    map<int, vector<int>> event;
    for(int i = 0; i < n; i++ ){
        if(a[i] % m == 0){
            continue;
        }
        int x = (a[i] / m + 1) * m;
        event[x - a[i]].push_back(find(a[i] / m + 1));
    }
    vector<int> cnt(sz + 1);
    for(int i = 0; i < n; i++ ){
        int x = find(a[i] / m);
        if(cnt[x] == 0){
            modify(1, x, 1);
        }
        cnt[x] += 1;
    }

    int ans = tr[1].mx, time = 0;
    for(auto [_, v] : event){
        for(auto u : v){
            cnt[u - 1] -= 1;
            if(cnt[u - 1] == 0){
                modify(1, u - 1, 0);
            }
            if(cnt[u] == 0){
                modify(1, u, 1);
            }
            cnt[u] += 1;
        }
        if(tr[1].mx > ans){
            ans = tr[1].mx;
            time = _;
        }
    }
    cout << ans << " " << time << "\n";
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