#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define se second
#define mp make_pair
#define pii pair<int, int>

void solve(){
    // https://codeforces.com/contest/1841/problem/E
    int n;
    cin >> n;
    vector<int> a(n + 2);
    for(int i = 1; i <= n; i++ ){
        cin >> a[i];
    }
    a[0] = n;
    a[i + 1] = n;
    ll m;
    cin >> m;
    vector<pair<int, int>> stk;
    vector<int> cnt(n + 1);
    for(int i = 1; i <= n + 1; i++ ){
        if(a[i] < a[i - 1]){
            stk.emplace_back(a[i - 1] - a[i], i);
        } else {
            int d = a[i] - a[i - 1];
            while(d > 0){
                int add = min(stk.back().fi, d);
                cnt[j - stk.back().se] += add;
                stk.back().fi -= add;
                if(stk.back().fi == 0){
                    stk.pop_back();
                }
            }
        }
    }
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