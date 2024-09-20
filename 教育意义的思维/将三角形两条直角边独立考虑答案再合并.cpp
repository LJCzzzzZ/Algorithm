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
    // 有教育意义的思维方式: 连续一段可填区间中, 对左右边界特判后, n个格子有 n + 1条竖边, 答案乘 (n + 1)
    // 一个三角形有两条直角边, 分别对应着竖直方向和水平方向, 两者放置相互独立, 那么可以分开讨论, 答案相乘即可(因为属于同一个三角形)
    // 所以总体思路即分别考虑两个方向, 然后统计答案时进行分类讨论
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<string> s(n);
    for(int i = 0; i < n; i++ ){
        cin >> s[i];
    }
    ll ans = 1;
    for(int i = 0; i < n; i++ ){
        for(int j = 0; j < n; j++ ){
            if(s[i][j] == '?'){
                int k = j;
                while(k + 1 < n && s[i][k + 1] == '?'){
                    k += 1;
                }
                int cnt = 0;
                cnt += (j - 1 >= 0 ? s[i][j - 1] == '#' : 0);
                cnt += (k + 1 < n ? s[i][k + 1] == '#' : 0);
                if(cnt == 2){
                    ans = 0;
                } else if(cnt == 0){
                    ans = ans * (k - j + 2) % mod;
                }
                j = k;
            }            
        }
    }

    for(int i = 0; i < n; i++ ){
        for(int j = 0; j < n; j++ ){
            if(s[j][i] == '?'){
                int k = j;
                while(k + 1 < n && s[k + 1][i] == '?'){
                    k += 1;
                }
                int cnt = 0;
                cnt += (j - 1 >= 0 ? s[j - 1][i] == '#' : 0);
                cnt += (k + 1 < n ? s[k + 1][i] == '#' : 0);
                if(cnt == 2){
                    ans = 0;
                } else if(cnt == 0){
                    ans = ans * (k - j + 2) % mod;
                }
                j = k;
            }            
        }
    }
    cout << ans << "\n";
    return 0;
}