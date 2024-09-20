#define mp make_pair
typedef pair<int, int> hashv;
const ll mod1 = 1e9 + 7;
const ll mod2 = 1e9 + 9;

hashv operator + (hashv a, hashv b) {
    int c1 = a.fi + b.fi,c2 = a.se + b.se;
    if (c1 >= mod1) c1 -= mod1;
    if (c2 >= mod2) c2 -= mod2;
    return mp(c1, c2);
}

hashv operator - (hashv a, hashv b) {
    int c1 = a.fi - b.fi,c2 = a.se - b.se;
    if (c1 < 0) c1 += mod1;
    if (c2 < 0) c2 += mod2;
    return mp(c1, c2);
}

hashv operator * (hashv a, hashv b) {
    return mp(1ll * a.fi * b.fi % mod1, 1ll * a.se * b.se % mod2);
}
