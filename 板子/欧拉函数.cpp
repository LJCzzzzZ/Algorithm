ll phi(ll x){
    ll ans = x;
    // phi[x] = x / p1 * (p1 - 1) / p2 * (p2 - 1) ....
    for(int i = 2; i <= x / i; i++ ){
        if(x % i == 0){
            ans = ans / i * (i - 1);
            while(x % i == 0) x /= i;
        }
    }
    if(x > 1){
        ans = ans / x * (x - 1);
    }
    return ans;
}