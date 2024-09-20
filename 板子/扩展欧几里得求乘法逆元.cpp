// ax + by = gcd(a, b) // a, b已知, 求x, y未知,
ll exgcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) { x = 1; y = 0; return a; }
    ll ret = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return ret;

    // b1 = b / __gcd(a, b);
    // 最小非负整数解 x = (x % b1 + b1) % b1;
    // y = (__gcd - a * x) / b;
}

// 找到 n 在模 p 下的乘法逆元
ll inv(ll n, ll p){
    ll x, y;
    if(exgcd(n, p, x, y) == 1){
        x = x % p;
        return x >= 0 ? x : x + p;
    } else {
        // 无解 
        return -1;
    }
}