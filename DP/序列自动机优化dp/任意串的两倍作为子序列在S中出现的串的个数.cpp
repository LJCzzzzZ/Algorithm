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
    // 题意: 给定一个字符串S, 问有多少个任意子串T -> TT在S中作为子序列出现
    // 难点: 一个子序列可能被枚举了多次, 去重
    // 建立序列自动机, 枚举T2 的 T[2][1] 的位置 q, 定义 dp[i][j] 为T[1][n]的位置为i, T[2][n]的位置为j 且 i < q and j <= n
    // 显然当枚举的T1 和 T2足够紧密时(即nxt[T[1][n]][Tn] == T[2][1]) 时 中间不会出现重复的T1
    // 因此有状态转移方程 dp[nxt[i][k]][nxt[j][k]] += dp[i][j], 统计答案时要求满足 nxt[T[1][n]][Tn] == T[2][1]
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    cin >> s;
    int n = s.size();
    s = "#" + s;
    vector<vector<int>> nxt(n + 1, vector<int> (26, n + 1));
    for(int i = n - 1; i >= 0; i-- ){
        nxt[i] = nxt[i + 1];
        nxt[i][s[i + 1] - 'a'] = i + 1;
    }   
    int ans = 0;
    for(int q = 2; q <= n; q++ ){
        int p = nxt[0][s[q] - 'a'];
        if(p >= q){
            continue;
        }
        vector<vector<int>> dp(n + 1, vector<int> (n + 1));
        dp[p][q] = 1;
        for(int i = 1; i <= n; i++ ){
            for(int j = 1; j <= n; j++ ){
                for(int k = 0; k < 26; k++ ){
                    int nxti = nxt[i][k], nxtj = nxt[j][k];
                    if(nxti >= q || nxtj > n){
                        continue;
                    }
                    dp[nxti][nxtj] = (dp[nxti][nxtj] + dp[i][j]) % mod;
                }
            }
        }
        for(int i = 1; i <= n; i++ ){
            for(int j = 1; j <= n; j++ ){
                if(nxt[i][s[q] - 'a'] == q){
                    ans = (ans + dp[i][j]) % mod;
                }
            }
        }
    }
    cout << ans << "\n";
    return 0;
}