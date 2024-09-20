#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define se second
#define mp make_pair
#define pii pair<int, int>

int main() 
{
    // 题意: 给定m个岛屿, 在r ~ g时间循环里, g结束时必须要在岛屿上, 其他时间可以以当前方向移动, 一个g周期后要停r周期
    //       问到达n的最短时间
    // 题解: 01bfs, 01bfs指的是在最短路问题中每一步有两种代价(代价0, 代价1)要使得到达终点的代价最少, 那么就要先用代价0取更新, 再用
    //      代价1更新, 每次放入可更新点时, 代价0放队首, 代价1放队尾
    //      注意到 g * m = 1e7 可以定义dp(i, j) 到达i, 当轮绿灯用时j时最少循环轮数
    //      那么每次只向左右两个位置转移 有状态转移方程  dp(i - 1, j + d[i] - d[i - 1]) =  dp(i, j) + (d[i] - d[i - 1] + j == g)
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<int> d(m);
    for(int i = 0; i < m; i++ ){
        cin >> d[i];
    }
    int g, r;
    cin >> g >> r;
    sort(d.begin(), d.end());
    vector<vector<int>> dp(m, vector<int> (g + 1, -1));
    deque<pair<int, int>> q;
    q.emplace_back(0, 0);
    dp[0][0] = 0;
    while(!q.empty()){
        auto [x, cur] = q.front();
        q.pop_front();
        if(x - 1 >= 0){
            if(cur + d[x] - d[x - 1] < g){
                if(dp[x - 1][cur + d[x] - d[x - 1]] == -1){
                    dp[x - 1][cur + d[x] - d[x - 1]] = dp[x][cur];
                    q.emplace_front(x - 1, cur + d[x] - d[x - 1]);
                }
            } else if(cur + d[x] - d[x - 1] == g){
                if(dp[x - 1][0] == -1){
                    dp[x - 1][0] = dp[x][cur] + 1;
                    q.emplace_back(x - 1, 0);
                }
            }
        }
        if(x + 1 < m){
            if(cur + d[x + 1] - d[x] < g){
                if(dp[x + 1][cur + d[x + 1] - d[x]] == -1){
                    dp[x + 1][cur + d[x + 1] - d[x]] = dp[x][cur];
                    q.emplace_front(x + 1, cur + d[x + 1] - d[x]);
                }
            } else if(cur + d[x + 1] - d[x] == g){
                if(dp[x + 1][0] == -1){
                    dp[x + 1][0] = dp[x][cur] + 1;
                    q.emplace_back(x + 1, 0);
                }
            }
        }
    }
    ll ans = 2e18;
    for(int i = 0; i < m; i++ ){
        for(int j = 0; j < g; j++ ){
            if(dp[i][j] != -1 && n - d[i] <= g - j){
                ans = min(ans, 1ll * dp[i][j] * (g + r) + n - d[i] + j);
            }
        }
    }
    cout << (ans == 2e18 ? -1 : ans) << "\n";
    return 0;
}