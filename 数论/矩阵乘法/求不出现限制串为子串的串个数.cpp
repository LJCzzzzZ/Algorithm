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
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll n, m;
    cin >> n >> m;
    vector<string> s(m);
    for(int i = 0; i < m; i++ ){
        cin >> s[i];
    }
    vector<string> t;
    for(int i = 0; i < 6; i++ ){
        for(int j = 0; j < 1 << i; j++ ){
            string x = "";
            for(int k = 0; k < i; k++ ){
                if(j >> k & 1){
                    x += 'a';
                } else {
                    x += 'b';
                }
            }
            t.push_back(x);
        }
    }
    int cnt = t.size();
    vector<vector<int>> next(cnt, vector<int> (cnt));
    vector<vector<int>> ok(cnt, vector<int> (cnt, 1));
    for(int i = 0; i < cnt; i++ ){
        for(int j = 0; j < 2; j++ ){
            string T = t[i] + char('a' + j);
            for(int k = 0; k < m; k++ ){
                if(T.size() >= s[k].size()){
                    if(T.substr(T.size() - s[k].size()) == s[k]){
                        ok[i][j] = 0;
                    }
                }
            }
            if(ok[i][j]){
                if(T.size() == 6){
                    T.erase(T.begin());
                }
                for(int k = 0; k < cnt; k++ ){
                    if(T == t[k]){
                        next[i][j] = k;
                    }
                }
            }
        }
    }
    vector<vector<ll>> mat(cnt, vector<ll> (cnt));
    for(int i = 0; i < cnt; i++ ){
        for(int j = 0; j < 2; j++ ){
            if(ok[i][j]){
                mat[i][next[i][j]] = 1;
            }
        }
    }

    auto mul = [&](vector<vector<ll>> &A, vector<vector<ll>> &B){
        vector<vector<ll>> C(cnt, vector<ll> (cnt));
        for(int i = 0; i < cnt; i++ ){
            for(int j = 0; j < cnt; j++ ){
                for(int k = 0; k < cnt; k++ ){
                    C[i][k] += A[i][j] * B[j][k] % mod;
                    C[i][k] %= mod;
                }
            }
        }
        return C;
    };

    auto matpow = [&](vector<vector<ll>> &A, ll k){
        vector<vector<ll>> ans(cnt, vector<ll> (cnt));
        for(int i = 0; i < cnt; i++ ){
            ans[i][i] = 1;
        }
        while(k > 0){
            if(k & 1){
                ans = mul(ans, A);
            }
            A = mul(A, A);
            k >>= 1;
        }
        return ans;
    };

    mat = matpow(mat, n);
    ll ans = 0;
    for(int i = 0; i < cnt; i++ ){
        ans = (ans + mat[0][i]) % mod;
    }
    cout << ans << "\n";
    return 0;
}