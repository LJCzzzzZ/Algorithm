#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define se second
const ll INF = 2e18;
int main() 
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, k;
    cin >> n >> m >> k;
    map<int, vector<int>> mp1, mp2;
    vector<ll> X(k), Y(k); 
    for(int i = 0; i < k; i++ ){
        cin >> X[i] >> Y[i];
        // 分类
        mp1[X[i] - Y[i]].push_back(i);
        mp2[X[i] + Y[i]].push_back(i);
    }

    vector<ll> ans(k, INF);
    int x = 0, y = 0, dx = 1, dy = 1;
    ll cur = 0;
    while(true){
        if(dx == dy){
            for(auto id : mp1[x - y]){
                ll t = cur + (X[id] - x) / dx;
                ans[id] = min(ans[id], t);
            }
            if(dx == 1 && dy == 1){
                if(n - x < m - y){
                    int dif = n - x;
                    cur += dif;
                    x += dif;
                    y += dif;
                    dx = -1;
                    dy = 1;
                } else if(n - x >  m - y){
                    int dif = m - y;
                    cur += dif;
                    x += dif;
                    y += dif;
                    dx = 1;
                    dy = -1;
                } else {
                    break;
                }
            } else {
                if(x < y){
                    int dif = x;
                    cur += dif;
                    x -= dif;
                    y -= dif;
                    dx = 1;
                    dy = -1;
                } else if(x > y){
                    int dif = y;
                    cur += dif;
                    x -= dif;
                    y -= dif;
                    dx = -1;
                    dy = 1;
                } else {
                    break;
                }
            }
        } else {
            for(auto id : mp2[x + y]){
                ll t = cur + (X[id] - x) / dx;
                ans[id] = min(ans[id], t);
            }
            if(dx == 1 && dy == -1){
                if(n - x < y){
                    int dif = n - x;
                    cur += dif;
                    x += dif;
                    y -= dif;
                    dx = -1;
                    dy = -1;
                } else if(n - x > y){
                    int dif = y;
                    cur += dif;
                    x += dif;
                    y -= dif;
                    dx = 1;
                    dy = 1;
                } else {
                    break;
                }
            } else {
                if(x < m - y){
                    int dif = x;
                    cur += dif;
                    x -= dif;
                    y += dif;
                    dx = 1;
                    dy = 1;
                } else if(x > m - y){
                    int dif = m - y;
                    cur += dif;
                    x -= dif;
                    y += dif;
                    dy = -1;
                    dy = -1;
                } else {
                    break;
                }
            }
        }
    }
    for(int i = 0; i < k; i++ ){
        cout << (ans[i] == INF ? -1 : ans[i]) << "\n";
    }
    return 0;
}