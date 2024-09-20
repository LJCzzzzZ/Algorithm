#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define se second
#define mp make_pair
#define pii pair<int, int>
const double eps = 1e-8;
int main() 
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // 给出m个位置出现的时间, 通过的概率, 强行通过消耗的时间, 不能过要重开, 求破纪录的期望
    // dp[i][j] 当前在位置i, 消耗了j个剩余时间的 破纪录期望时间
    // 当 j + d <= lim dp[i][j] = (dp[i + 1][j] + t[i + 1] - t[i]) * p[i](成功过) 
    //                            + min(dp[i + 1][j + d] + t[i + 1] - t[i] + d[i](硬过), dp[0][0](重开)) * (1 - p[i]) 
    // 当 j + d > lim dp[i][j] = (dp[i + 1][j] + t[i + 1] - t[i]) * p[i](成功过) + dp[0][0](重开) * (1 - p[i]) 
    // dp[0][0] 的含义是 从头开始经过若干次重开到达终点的期望时间
    // 二分dp[0][0] 代入若求出来的dp[0][0] 比二分的小则加大, 否则减小
    int n, c, m;
    cin >> n >> c >> m;
    vector<int> t(n + 2), d(n + 2);
    vector<long double> p(n + 2);
    for(int i = 1; i <= m; i++ ){
        cin >> t[i] >> p[i] >> d[i];
    }

    t[0] = 0, p[0] = 1;
    t[m + 1] = n, p[m + 1] = 1;

    auto check = [&](long double x){
        int lim = c - n - 1;
        vector<vector<long double>> dp(m + 3, vector<long double> (lim + 1));
        for(int i = m; i >= 0; i-- ){
            for(int j = 0; j <= lim; j++ ){
                if(j + d[i] <= lim){
                    dp[i][j] += (dp[i + 1][j] + t[i + 1] - t[i]) * p[i] + min(x, dp[i + 1][j + d[i]] + d[i] + t[i + 1] - t[i]) * (1 - p[i]);
                } else {
                    dp[i][j] += (dp[i + 1][j] + t[i + 1] - t[i]) * p[i] + x * (1 - p[i]);
                }
            }
        }
        return dp[0][0];
    };
    long double l = 0, r = 2e18;
    for(int i = 0; i < 300; i++ ){
        long double mid = (l + r) / 2;
        if(check(mid) > mid) l = mid;
        else r = mid - eps;
    } 
    cout << fixed << setprecision(8) << l << "\n";
    return 0;
}