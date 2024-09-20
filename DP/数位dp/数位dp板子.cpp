#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define se second
const int N = 25;
ll dp[N][N][N][2];
void solve(){
    memset(dp, -1, sizeof dp);
    string s;
    ll L, R;   
    cin >> s >> L >> R;
    int n = s.size();
    s = " " + s;
    vector<int> kmp(n + 1);
    for(int i = 2, j = 0; i <= n; i++ ){
        while(j && s[j + 1] != s[i]) j = kmp[j];
        if(s[j + 1] == s[i]) j++;
        kmp[i] = j; 
    }

    vector<int> num;
    // pos -> 遍历到第几位  limit ->  之前是否为最高位  d -> 与S匹配多少位  v -> 这种方案一共出现多少个S, 是否有前导0(初始默认有)
    auto dfs = [&](auto self, int pos, int limit, int d, int v, int lead) -> ll {
        if(pos == -1) return v;
        // 前面所有都为最高位且已经遍历过, 则该状态确定
        if(!limit && ~dp[pos][d][v][lead]) return dp[pos][d][v][lead];
        ll ans = 0;
        int top = limit ? num[pos] : 9;
        for(int i = 0; i <= top; i++ ){
            int ne = d, V = v;
            if(!(lead && i == 0)){ // 不能存在前导零
                while(ne && s[ne + 1] != i + '0') ne = kmp[ne];
                if(s[ne + 1] == i + '0') ne++;
                if(ne == n) {
                    V++;
                    ne = kmp[ne];
                }
            }
            ans += self(self, pos - 1, i == top && limit, ne, V, lead && i == 0);
        }
        if(!limit){
            dp[pos][d][v][lead] = ans;
        }
        return ans;
    };

    auto calc = [&](ll x){
        num.clear();
        while(x > 0){
            num.push_back(x % 10);
            x /= 10;
        }
        return dfs(dfs, num.size() - 1, 1, 0, 0, 1);
    };
    cout << calc(R) - calc(L - 1) << "\n";

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