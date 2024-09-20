#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define se second
#define mp make_pair
#define pii pair<int, int>

int main() 
{
    // 题意: 给定一个数n (n <= 1e16) 一个数p 问有多少个数的最大质因子小于p
    // 题解: 折半搜索
    // 枚举每一个小于p的质因子, 并把其的指数次的值乘原数组的值平均地均分到两个数组
    // 可以发现最后两个数组的个数不超过5e6, 排序后跑双指针即可
    // trick: 当移动指针时, 不用pi * pj <= lim来判断 而是 用 pi <= lim / pj 避免超long long
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<int> p;
    for(int i = 2; i <= 100; i++ ){
        bool ok = true;
        for(int j = 2; j * j <= i; j++ ){
            if(i % j == 0){
                ok = false;
            }
        }
        if(ok){
            p.push_back(i);
        }
    }
    ll n, mx;
    cin >> n >> mx;
    while(p.back() > mx){
        p.pop_back();
    }
    vector<ll> a{1}, b{1};
    auto add = [&](vector<ll> &x, ll pri, ll lim){
        vector<ll> c;
        for(int i = 0; i < (int)x.size(); i++ ){
            ll y = x[i];
            while(true){
                if(y * pri > lim){
                    break;
                }
                y *= pri;
                c.push_back(y);
            }
        }
        x.insert(x.end(), c.begin(), c.end());
    };
    for(auto x : p){
        if(a.size() > b.size()){
            add(b, x, n);
        } else {
            add(a, x, n);
        }
    }

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    int j = b.size() - 1;
    ll ans = 0;
    for(int i = 0; i < (int)a.size(); i++ ){
        ll r = n / a[i];
        while(j >= 0 && b[j] > r){
            j--;
        }
        if(j < 0){
            break;
        }
        ans += (j + 1);
    }
    cout << ans << "\n";
    return 0;
}