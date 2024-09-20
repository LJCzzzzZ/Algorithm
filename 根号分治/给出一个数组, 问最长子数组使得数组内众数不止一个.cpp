#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define se second
#define mp make_pair
#define pii pair<int, int>

int main() 
{
    // 题意: 给出一个数组, 问最长子数组使得数组内众数不止一个
    // 性质题 + 值域根号分治
    // 性质: 对于最终答案来说, 如果原数组众数有2个, 那么答案为n, 如果众数只有一个D
    // 假设最终区间为 [a, b] 且不包含D, 那么区间向两边扩展, 区间内众数可能会变大, 但必定不超过D, 当与D个数相等时区间长度显然大于原来的
    // 对于出现次数 >= sqrt(n) 的 数只有根号个, 那么枚举(V, D)为答案中的两个众数
    // trick: 原数组中 V -> 1  D -> -1 其他 -> 0, 那么根据前缀和求出最长区间和为0的子段就是该对最长长度
    // 实现: 用两倍数组来表示正负数可以避免使用map, 正常跑前缀和就行
    // 对于出现次数 < sqrt(n) 的情况, 枚举D出现次数 i, 用桶存出现次数(不超过i)跑双指针即可
    // 总复杂度 O(n * sqrt(n))
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> a(n);
    vector<int> cnt(n);
    for(int i = 0; i < n; i++ ){
        cin >> a[i];
        a[i]--;
        cnt[a[i]] += 1;
    }

    int mx = *max_element(cnt.begin(), cnt.end());
    if(count(cnt.begin(), cnt.end(), mx) >= 2){
        cout << n << "\n";
        return 0;
    }
    if(count(cnt.begin(), cnt.end(), 0) == n - 1){
        cout << "0\n";
        return 0;
    }
    int p = -1;
    for(int i = 0; i < n; i++ ){
        if(cnt[i] == mx){
            p = i;
        }
    }
    int B = 450;
    int ans = 0;
    for(int i = 0; i < n; i++ ){
        if(i == p){
            continue;
        }
        if(cnt[i] > B){                 
            vector<int> has(n * 2 + 2, -2);
            int cur = 0;
            has[0 + n] = -1;
            for(int j = 0; j < n; j++ ){
                if(a[j] == p){
                    cur += 1;
                } else if(a[j] == i){
                    cur -= 1;
                }
                if(has[cur + n] == -2){
                    has[cur + n] = j;
                } else {
                    ans = max(ans, j - has[cur + n]);
                }
            }
        }
    }

    for(int i = 1; i <= B; i++ ){
        vector<int> has(n);
        int res = 0;
        for(int j = 0, k = 0; j < n; j++ ){
            if(has[a[j]] == i - 1){
                res += 1;
            }
            has[a[j]] += 1;
            while(has[a[j]] > i){
                if(has[a[k]] == i){
                    res -= 1;
                }
                has[a[k]] -= 1;
                k += 1;
            }
            if(res >= 2){
                ans = max(ans, j - k + 1);
            }
        }
    }
    cout << ans << "\n";
    return 0;
}           