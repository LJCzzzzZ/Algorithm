#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define se second
#define mp make_pair
#define pii pair<int, int>

int main() 
{
    // 题意: 给定n个转盘, 每个转盘有m个数 0 ~ x, 转一次i花费ci, 问转一直转到值为m最少需要多少花费
    // 题解: 期望dp + 式子
    // 递推式期望dp 先把 dp式子写下来, 然后对于能移项化简的先化简, 然后再对式子进行下一步优化
    // 如: dp[i] = cost + p * dp[i] + p * dp[i + x] + p * dp[i + y]....
    // 则: dp[i] = cost / (1 - p) + p / (1 - p) * dp[i + x] ...
    // 一般这种是包含有转移是只加花费不加贡献的转移, 然后对该dp取min即可
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<int> c(n), p(n);
    vector<vector<int>> s(n);
    for(int i = 0; i < n; i++ ){
        cin >> c[i] >> p[i];
        s[i].resize(p[i]);
        for(int j = 0; j < p[i]; j++ ){
            cin >> s[i][j];
        }
    }

    vector<double> dp(m + 1, 2e9);
    dp[m] = 0;
    for(int i = m - 1; i >= 0; i-- ){
        for(int j = 0; j < n; j++ ){
            double sum = 0;
            int zero = 0;
            for(auto x : s[j]){
                if(x != 0){
                    sum += dp[min(i + x, m)];
                } else {
                    zero += 1;
                }
            }
            dp[i] = min(dp[i], 1.0 * c[j] * p[j] / (p[j] - zero) + sum / (p[j] - zero));
        }
    }
    cout << fixed << setprecision(12) << dp[0] << "\n";
    return 0;
}