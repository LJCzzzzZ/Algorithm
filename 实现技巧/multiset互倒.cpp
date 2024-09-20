#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define se second
#define mp make_pair
#define pii pair<int, int>

int main() 
{
    // https://atcoder.jp/contests/abc314/tasks/abc314_g
    // 题意: 依次对抗n个怪物, 若有和怪物同类型的符文则不扣血, 否则扣hi的血, 问可以持有0 ~ m张符文能打到最多多少怪物
    // 题解: multiset + 模拟
    // 用两个multiset 分别存 选了该符文的该类型总和 以及 没选用的总和
    // 显然答案有不减性, 符文越多扣血不增 
    // 然后模拟前i个数选完, 血量大于0最少需要的符文数, 两个mutiset互相倒来使sum最小
    // trick: multiset中用 int 而不是 pair<int, int> 我们不需要知道该选出的数是否是该类型, 而只需要知道是否有这个数
    //        因为可以假设两种数的相反过来, 就可以认为实际上被选了
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, H;
    cin >> n >> m >> H;
    vector<int> A(n), B(n);
    for(int i = 0; i < n; i++ ){
        cin >> A[i] >> B[i];
        B[i]--;
    }   
    vector<ll> hp(m), ans(m + 1);
    multiset<ll> s1, s2;
    for(int i = 0; i < m; i++ ){
        s2.insert(0);
    }
    ll sum = 0;
    int j = 0;
    for(int i = 0; i < n; i++ ){
        ll cur = hp[B[i]];
        hp[B[i]] += A[i];
        ll res = hp[B[i]];
        if(s1.find(cur) != s1.end()){
            s1.erase(s1.find(cur));
            s1.insert(res);
        } else {
            s2.erase(s2.find(cur));
            s2.insert(res);
            sum -= cur - res;
        }

        while(!s1.empty() && !s2.empty() && *s1.begin() < *s2.rbegin()){
            auto x = *s1.begin();
            auto y = *s2.rbegin();
            s1.erase(s1.find(x));
            s2.erase(s2.find(y));
            s1.insert(y);
            s2.insert(x);
            sum += x - y;
        }

        while(!s2.empty() && sum >= H){
            auto x = *s2.rbegin();
            sum -= x;
            s2.erase(s2.find(x));
            s1.insert(x);            
        }
        if(sum < H){
            while(j < s1.size()){
                ans[j] = i;
                j += 1;
            }
        }
    }
    while(j <= m){
        ans[j] = n;
        j += 1;
    }
    for(int i = 0; i <= m; i++ ){
        cout << ans[i] << " \n"[i == m];
    }
    return 0;
}