#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define se second
#define mp make_pair
#define pii pair<int, int>
template <typename T>
struct Bit {
    int n;
    vector<T> a;
    Bit(int n) : n(n), a(n) {}
    void update(int x, T v) {
        for (int i = x + 1; i <= n; i += i & -i) {
            a[i - 1] += v;
        }
    }
    
    // 下标从1开始
    // [1, x]
    T query(int x) {
        T ans = 0;
        for (int i = x; i > 0; i -= i & -i) {
            ans += a[i - 1];
        }
        return ans;
    }
    // 下标从1开始
    // (l, r]
    T rangeQuery(int l, int r) {  
        return query(r) - query(l);
    }
};
int main() 
{
    // 题意: 可多次修改单点的值, 多次询问区间 L, R, K -> [L, R]中所有元素的个数是否是k的倍数
    // 题解: 树状数组上维护哈希
    // 一个区间元素个数是k的倍数,那么权值和也一定的k的倍数,反之却不一定成立
    // 若区间[L, R]的映射哈希后的和是k的倍数可能成立, 如果不是则一定不成立
    // 当k越大当次本来就正确的概率越大
    // 当k等于2时, 哈希映射后使得集合中既有偶数又有奇数, 那么和mod2 ≡ 0的概率为 1 / 2
    // 进行多次(30次以上)哈希映射后如果都正确, 概率为 2^(-32) 那么我们认为这就是对的 
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    vector<int> st;
    vector<int> c(n);
    for(int i = 0; i < n; i++ ){
        cin >> c[i];
        st.push_back(c[i]);
    }
    vector<tuple<int, int, int, int>> que;
    for(int i = 0; i < q; i++ ){
        int o, l, r, x;
        cin >> o;
        if(o == 1){
            cin >> l >> x;
            st.push_back(x);
            que.emplace_back(o, l, x, 0);
        } else {
            cin >> l >> r >> x;
            que.emplace_back(o, l, r, x);
        }
    }
    sort(st.begin(), st.end());
    st.erase(unique(st.begin(), st.end()), st.end());
    int m = st.size();
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    vector<int> ans(q, -1);
    for(int i = 0; i < n; i++ ){
        c[i] = lower_bound(st.begin(), st.end(), c[i]) - st.begin() + 1;
    }
    for(int i = 0; i < q; i++ ){
        if(get<0>(que[i]) == 1){
            get<2>(que[i]) = lower_bound(st.begin(), st.end(), get<2>(que[i])) - st.begin() + 1;
        }
    }
    for(int t = 0; t < 30; t++ ){
        auto a = c;
        vector<ll> b(m + 1);
        for(int i = 0; i <= m; i++ ){
            b[i] = rng();
        }
        Bit<ll> bit(n);
        for(int i = 0; i < n; i++ ){
            bit.update(i, b[a[i]]);
        }
        for(int i = 0; i < q; i++ ){
            if(get<0>(que[i]) == 1){
                auto [o, j, x, _] = que[i];
                j--;
                bit.update(j, -b[a[j]] + b[x]);
                a[j] = x;
            } else {
                auto [o, l, r, k] = que[i];
                if(ans[i] == 0){
                    continue;
                }
                if(bit.rangeQuery(l - 1, r) % k == 0){
                    ans[i] = 1;
                } else {
                    ans[i] = 0;
                }
            }
        }
    }
    for(int i = 0; i < q; i++ ){
        if(get<0>(que[i]) == 2){
            cout << (ans[i] == 0 ? "NO" : "YES") << "\n";
        }
    }
    return 0;
}