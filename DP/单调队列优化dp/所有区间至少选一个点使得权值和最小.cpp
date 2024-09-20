#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define se second
#define mp make_pair
#define pii pair<int, int>

void solve(){
    // 每条线段中至少有一个点被选中, 使得选中的点和最小
    // dp[i] 第i个点必选i以前所有线段均被满足的最小代价
    // dp[i] = min(dp[j]) + a[i] [j, i] 之间不能有一个完整的区间
    // 预处理每个i 最前面能到达的 j 使得 [j, i] 之间不能有一个完整的区间
    // pre[i] 具有不降性, dp转移时单调队列优化到O(n)
    int n;
    cin >> n;
    vector<int> a(n + 2);
    for(int i = 1; i <= n; i++ ){
        cin >> a[i];
    }
    a[n + 1] = 0;
    vector<vector<int>> b(n + 2);
    int m;
    cin >> m;
    for(int i = 0; i < m; i++ ){
        int l, r;
        cin >> l >> r;
        b[r].push_back(l);
        b[l].push_back(-r);
    }
    b[n + 1].push_back(n + 1);
    b[n + 1].push_back(-(n + 1));

    vector<int> pre(n + 2);
    int seg = 0;
    // trick: 以i结尾的最前的的j使得 [j, i]没有一个完整区间
    // 双指针O(n + m) 完成
    for(int i = 1, j = 1; i <= n + 1; i++ ){
        for(auto x : b[i]){ // 以i为右端点的整区间
            if(x > 0 && x >= j){
                seg += 1;
            }
        }
        while(seg > 0 && j <= i){ // 使得整区间变为0
            for(auto x : b[j]){ // 以j为左端点的整区间
                if(x < 0 && -x <= i){
                    seg -= 1;
                }
            }
            j += 1; 
        }
        pre[i] = j - 1;
    }

    vector<ll> dp(n + 3);
    deque<int> h;
    h.push_back(0);
    for(int i = 1; i <= n + 1; i++ ){
        while(!h.empty() && h.front() < pre[i - 1]){
            h.pop_front();
        }
        dp[i] = (h.empty() ? 0 : dp[h.front()]) + a[i];
        while(!h.empty() && dp[h.back()] >= dp[i]){
            h.pop_back();
        }
        h.push_back(i);
    }
    cout << dp[n + 1] << "\n";
}
int main() 
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while(T--){
        solve();
    }
    return 0;
}       