#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define se second
#define mp make_pair
#define pii pair<int, int>
constexpr int mod = 998244353;
ll ksm(ll a, ll b){
    ll ans = 1;
    while(b){
        if(b & 1) ans = ans * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return ans;
}
int main() 
{
    // 题意: 给定一个人的工作表(01串), 要求安排第二个人的工作表, 要求满足可选i | n, t[i] 被选则 t[i + m]被选
    // 最后要满足i ∈ (1, n) s[i] == 1 || t[i] == 1 的不同字符串个数
    // 设dp[j] 为可选i天长度的工作方案数
    // ness[s[i] % j] = 1 (s[i] == 0) 则dp[j]方案总数为不是必选选中的天 pow(2, cnt)
    // 观察到计数存在重复: 任选的过程中, 若存在 k | j 则 dp[k]的方案总能匹配到 dp[j]中某一种任选方案, 因此dp[i] = pow(2, cnt) - Σdp[k] (k | i); 
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    string s;
    cin >> s;
    vector<int> dp(n + 1);
    for(int i = 1; i < n; i++ ){
        if(n % i == 0){
            vector<int> np(i, 1);
            for(int j = 0; j < n; j++ ){
                if(s[j] == '.'){
                    np[j % i] = 0;
                }
            }
            int cnt = accumulate(np.begin(), np.end(), 0);
            dp[i] = ksm(2, cnt);
            // 当前dp[i]为空位任意选的情况下的方案数, 显然对于 k | i的周期k能满足的方案必定能表示出i的方案, 因此减去
            for(int j = 1; j < i; j++ ){
                if(i % j == 0){
                    dp[i] = (dp[i] - dp[j] + mod) % mod;
                }
            }
        }
    }

    int ans = 0;
    for(int i = 1; i < n; i++ ){
        ans = (ans + dp[i]) % mod;
    }
    cout << ans << "\n";
    return 0;
}