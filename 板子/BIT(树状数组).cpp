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