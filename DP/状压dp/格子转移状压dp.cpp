#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define se second
#define mp make_pair
#define pii pair<int, int>
const int mod = 998244353;
int main() 
{
    // 题意: 给定一个矩阵, 有?, 0, 1, 有两种操作, 将一列从上到下染色成1, 将一行从左到右染成1, 将？替换
    //       问有多少种矩阵满足是用以上操作得到的矩阵
    // 题解: 先看范围, 考虑是状压dp
    // 定义dp[0 / 1][1 << m] 为 该行到目前位置是否全是 1 -> dp[0], 改行以上各列组成的列状态 (s >> j & 1) 说明被 0打断过
    // 先考虑一个格子一个格子转移, 平时都是dp[j][1 << s]表示一行的状态, 本题省空间就格子转移, 本质是一样的
    // 当s[i][j] == '0' 说明到目前位置后左边和上面都不能连成连续的1 np[1][s | 1 << j] += dp[k][s]
    // 当s[i][j] == '1' 说明到目前位置前左边和上面至少有一种连成连续的1 np[k][s] += dp[k][s];
    // 当s[i][j] == '?' 上面两种情况叠加
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<string> t(n);
    for(int i = 0; i < n; i++ ){
        cin >> t[i];
    }
    vector<vector<ll>> dp(2, vector<ll> (1 << m));
    dp[0][0] = 1;
    for(int i = 0; i < n; i++ ){
        for(int j = 0; j < m; j++ ){
            vector<vector<ll>> np(2, vector<ll> (1 << m));
            for(int k = 0; k < 2; k++ ){
                for(int s = 0; s < 1 << m; s++ ){
                    if(t[i][j] == '0' || t[i][j] == '?'){
                        if(j == m - 1){
                            np[0][s | 1 << j] += dp[k][s];
                            np[0][s | 1 << j] %= mod;
                        } else {
                            np[1][s | 1 << j] += dp[k][s];
                            np[1][s | 1 << j] %= mod; 
                        }
                    }

                    if(t[i][j] == '1' || t[i][j] == '?'){
                        if(k == 0 || !(s >> j & 1)){
                            if(j == m - 1){
                                np[0][s] += dp[k][s];
                                np[0][s] %= mod;
                            } else {
                                np[k][s] += dp[k][s];
                                np[k][s] %= mod;
                            }
                        }
                    }
                }
            }
            swap(np, dp);
        }
    }

    ll ans = 0;
    for(int i = 0; i < 2; i++ ){
        for(int j = 0; j < 1 << m; j++ ){
            ans = (ans + dp[i][j]) % mod;
        }
    }
    cout << ans << "\n";
    return 0;
}