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
    // 问区间中每个数恰好出现3次的区间个数
    // 每一个数分配一个随机值, 一个数出现一次即 sum = b[x], 两次 sum = 2 * b[i], 三次 sum = 3 * b[i] % 3 = 0
    // 维护每个位置的前缀和 pre
    // 维护每个数(3个一组)出现的位置, 当个数小于三个时 pre[i]加上 ((cnt[a[i]] + 1) % 3 - cnt[a[i]]) * b[a[i]]
    // 当个数大于等于3个时, 使得当前数第一次(组内)出现的位置st前的所有贡献清零, 因为从当前位置i到st前的所有区间必定出现4个a[i]
     
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++ ){
        cin >> a[i];
    }   
    vector<ll> b(n + 1);
    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    for(int i = 0; i <= n; i++ ){
        b[i] = rng();
    }
    hash_t mp;
    mp[0] = 1;
    vector<queue<int>> q(n + 1);
    vector<ll> pre(n + 1);
    vector<int> cnt(n + 1);
    int st = 0;
    ll ans = 0;
    for(int i = 0; i < n; i++ ){
        if(q[a[i]].size() >= 3){
            int ed = q[a[i]].front();
            q[a[i]].pop();
            while(st <= ed){
                mp[pre[st]] -= 1;
                st += 1;
            }
        }
        int before = cnt[a[i]];
        cnt[a[i]] = (cnt[a[i]] + 1) % 3;
        pre[i + 1] = pre[i] + (cnt[a[i]] - before) * b[a[i]];
        ans += mp[pre[i + 1]];
        mp[pre[i + 1]] += 1;
        q[a[i]].push(i);
    }
    cout << ans << "\n";
    return 0;
}