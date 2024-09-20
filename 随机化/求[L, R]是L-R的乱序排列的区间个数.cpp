#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define se second
#define mp make_pair
#define pii pair<int, int>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
const int RANDOM = chrono::high_resolution_clock::now().time_since_epoch().count();
struct chash {
    int operator()(int x) const { return x ^ RANDOM; }
};
typedef gp_hash_table<ll, ll, chash> hash_t;
int main() 
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<ll> a(n);
    for(int i = 0; i < n; i++ ){
        cin >> a[i];
    }
    vector<ll> b(n + 1);
    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    for(int i = 1; i <= n; i++ ){
        b[i] = rng();
    }

    vector<ll> pre(n + 1);
    for(int i = 1; i <= n; i++ ){
        // b[a[i]], b[a[i + 1]], b[a[i + 2]]... 
        // b[j],    b[j + 1],    b[j + 2]...
        // 区间[L, R] 为 从L到R的任意排列, 说明每个数出现一次, 位置为乱序
        // 当[L, R]为合法排列, 当且仅当 b[a[i]].. b[a[i + x]] 也是[L, R]的任意排列,
        // 此时b[a[i]] ^ b[a[i + 1]] ^ ... ^ b[a[i + x]] ^ b[L] ^ b[L + 1] ^ ... ^ b[R] = 0
        // 维护前缀和统计贡献即可
        pre[i] = pre[i - 1] ^ b[a[i - 1]] ^ b[i];
    }

    hash_t mp;
    mp[0] = 1;
    ll ans = 0;
    for(int i = 0; i < n; i++ ){
        ans += mp[pre[i + 1]];
        mp[pre[i + 1]] += 1;
    }
    cout << ans << "\n";
    return 0;
}