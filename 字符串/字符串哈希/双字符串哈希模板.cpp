#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define fi first
#define se second

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

const int N = 2010000;
hashv pw[N], s[N], t[N];
char tt[N];

hashv get1(int l, int r){
    return s[r] - s[l - 1] * pw[r - l + 1];
}

hashv get2(int l, int r){
    return t[l] - t[r + 1] * pw[r - l + 1];
}
int main() 
{
    //ios::sync_with_stdio(false);
    //cin.tie(nullptr); 
    int n;
    scanf("%d", &n);
    n = n * 2;
    scanf("%s", tt + 1);
    hashv base = mp(13331, 23333);
    pw[0] = mp(1, 1);
    for(int i = 1; i <= n; i++ ){
        pw[i] = pw[i - 1] * base;
        s[i] = s[i - 1] * base + mp(tt[i], tt[i]);
    }

    for(int i = n; i >= 1; i-- ){
        t[i] = t[i + 1] * base + mp(tt[i], tt[i]);
    }

    for(int i = 0; i <= n / 2; i++ ){
        hashv s1 = s[i] * pw[n / 2 - i] + (s[n] - s[i + n / 2] * pw[n / 2 - i]);
        hashv s2 = t[i + 1] - t[i + 1 + n / 2] * pw[n/2];
        if(s1 == s2){
            for(int j = 0; j < n / 2; j++ ){
                printf("%c", tt[i + n / 2 - j]);
            }
            printf("\n");
            printf("%d\n", i);
            return 0;
        }
    }
    cout << "-1\n";
    return 0;
}