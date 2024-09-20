// ax + by = gcd(a, b) // a, b已知, 求x, y未知,
ll exgcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) { x = 1; y = 0; return a; }
    ll ret = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return ret;
}
// r 为余数数组, mod 为模数数组
ll CRT(vector<ll>& r, vector<ll>& mod) {
    ll n = 1, ans = 0;
    int k = r.size();
    for (int i = 0; i < k; i++) n = n * mod[i];
    for (int i = 0; i < k; i++) {
        ll m = n / mod[i], b, y;
        exgcd(m, mod[i], b, y);  
        ans = (ans + r[i] * m * b % n) % n;
    }
    return (ans % n + n) % n;
}