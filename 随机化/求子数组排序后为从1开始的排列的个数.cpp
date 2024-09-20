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
    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++ ){
        cin >> a[i];
    }
    vector<ll> b(n + 1);
    for(int i = 1; i <= n; i++ ){ // 对每个数分配一个随机数
        b[i] = rng();
    }
    vector<ll> pre(n + 1);
    for(int i = 1; i <= n; i++ ){ // 完整排列的前缀异或和
        pre[i] = pre[i - 1] ^ b[i];
    }
    // 随机算法碰撞概率: 异或后每一位相同的概率为1 / 2, 64位全相同的概率为 2 ^(-64)
    auto calc = [&](){
        int res = 0;
        vector<ll> hs(n + 1);
        for(int i = 0; i < n; i++ ){
            hs[i + 1] = hs[i] ^ b[a[i]];
        }
        for(int i = 1, j = 1; i <= n; i++ ){
            if(a[i - 1] == 1){
                j = 1;
            } else {
                j = max(j, a[i - 1]); // 遇到每一个1时, 区间长度应为最后一个1后最大的数, 排列需要连续, 那必定取到最大数
                res += (j <= i && (hs[i] ^ hs[i - j]) == pre[j]);
            }
        }
        return res;
    };
    int ans = 0;
    ans += calc();
    reverse(a.begin(), a.end());
    ans += calc();
    for(int i = 0; i < n; i++ ){
        ans += (a[i] == 1);
    }
    cout << ans << "\n";
    return 0;
}