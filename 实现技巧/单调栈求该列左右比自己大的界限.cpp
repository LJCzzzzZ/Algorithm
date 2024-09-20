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
    int n, m;
    cin >> n >> m;
    vector<vector<int>> a(n, vector<int> (m));
    for(int i = 0; i < n; i++ ){
        for(int j = 0; j < m; j++ ){
            cin >> a[i][j];
        }
    }

    ll ans = 0;
    for(int i = 0; i < n; i++ ){
        vector<int> s(m), mi(m, 1e9);
        for(int j = i; j < n; j++ ){
            for(int k = 0; k < m; k++ ){
                s[k] += a[j][k];
                mi[k] = min(mi[k], a[j][k]);
            }
            vector<int> L(m, -1), R(m, m);
            vector<int> stk;
            for(int k = 0; k < m; k++ ){
                while(!stk.empty() && mi[k] < mi[stk.back()]){
                    R[stk.back()] = k;
                    stk.pop_back();
                }
                if(!stk.empty()){
                    L[k] = stk.back();
                }
                stk.push_back(k);
            }
            vector<int> pre(m + 1);
            for(int k = 0; k < m; k++ ){
                pre[k + 1] = pre[k] + s[k];
            }
            for(int k = 0; k < m; k++ ){
                ans = max(ans, 1ll * mi[k] * (pre[R[k]] - pre[L[k] + 1]));
            }
        }
    }
    cout << ans << "\n";
    return 0;
}