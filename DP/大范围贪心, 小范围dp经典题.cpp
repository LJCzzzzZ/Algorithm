#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define se second
#define mp make_pair
#define pii pair<int, int>

int main() 
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // https://codeforces.com/gym/103049/problem/A
    // 大范围贪心, 小范围dp
    // 对大范围的取性价比最高的 a[i] / i最小的
    // 最后一次可分裂为 i + j
    // 则剩下的设为 b : n - i - j, 性价比最优的为m
    // b = z * m + Σxi(1,2,3...N)
    // 当N > m时 则 x1, x2, x3, ... xN的前缀和, pre1, pre2, pre3, .... preN 
    // 在mod m意义下由鸽巢原理得必定有至少一对 prei = prej 使得prej - prei = xi + ... + xj = 0 mod (m)
    // 说明N <= m 预处理dp(n + 1 ~ n * (n + 1))  对 大于 n * (n + 1) 的部分上取整作为z 对 b - z * best取dp值
    int n, q;
    cin >> n >> q;
    vector<ll> a(n + 1);
    for(int i = 1; i <= n; i++ ){
        cin >> a[i];
    }
    int best = -1;
    pair<int, int> cur{-1, -1};
    for(int i = 1; i <= n; i++ ){
        if(cur == make_pair(-1, -1)){
            cur = {i, a[i]};
            best = i;
        } else {
            if(1ll * a[i] * cur.fi < 1ll * cur.se * i){
                cur = {i, a[i]};
                best = i;
            }
        }
    }
    vector<ll> dp(n * (n + 1) + 1, 2e18);
    for(int i = n + 1; i <= 2 * n; i++ ){
        for(int j = 1; j <= n; j++ ){
            if(i - j <= n){
                dp[i] = min(dp[i], a[i - j] + a[j]);
            }
        }
    }

    for(int i = n + 1; i <= n * (n + 1); i++ ){
        for(int j = 1; j <= n; j++ ){
            dp[i] = min(dp[i], dp[i - j] + a[j]);
        }
    }
    while(q--){
        int k;
        cin >> k;
        if(k <= n){
            cout << a[k] << "\n";
        } else {
            if(k > n * (best + 1)){
                ll r = (k - n * (best + 1) + best - 1) / best;
                cout << r * a[best] + dp[k - r * best] << "\n";
            } else {
                cout << dp[k] << "\n";
            }
        }
    }
    return 0;
}