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
    int n, m, t, act;
    cin >> n >> m >> t >> act;
    vector<string> s(n);
    for(int i = 0; i < n; i++ ){
        cin >> s[i];
    }
    
    int cnt = n * m + 1;
    vector<vector<vector<ll>>> mat(60, vector<vector<ll>> (cnt + 1, vector<ll> (cnt + 1)));
    for(int z = 0; z < act; z++ ){
        string t;
        cin >> t;
        int d = t.size();
        for(int i = 0; i < n; i++ ){
            for(int j = 0; j < m; j++ ){
                if(s[i][j] - '0' == z){
                    for(int k = 0; k < 60; k++ ){
                        if(i && t[k % d] == 'N'){
                            mat[k][i * m + j + 1][(i - 1) * m + j + 1] = 1;
                        }
                        if(j < m - 1 && t[k % d] == 'E'){
                            mat[k][i * m + j + 1][i * m + j + 1 + 1] = 1;
                        }
                        if(i < n - 1 && t[k % d] == 'S'){
                            mat[k][i * m + j + 1][(i + 1) * m + j + 1] = 1;
                        }
                        if(j && t[k % d] == 'W'){
                            mat[k][i * m + j + 1][i * m + j - 1 + 1] = 1;
                        }
                        if(t[k % d] <= '9' && t[k % d] >= '0'){
                            mat[k][0][i * m + j + 1] = t[k % d] - '0';
                            mat[k][i * m + j + 1][i * m + j + 1] = 1;
                        }
                    }
                }
            }
        }
    }
    for(int i = 0; i < 60; i++ ){
        mat[i][0][0] = 1;
    }
    auto matmul = [&](vector<vector<ll>> &A, vector<vector<ll>> &B){
        vector<vector<ll>> C(cnt, vector<ll> (cnt));
        for(int i = 0; i < cnt; i++ ){
            for(int j = 0; j < cnt; j++ ){
                for(int k = 0; k < cnt; k++ ){
                    C[i][k] += A[i][j] * B[j][k];
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
                ans = matmul(ans, A);
            }
            A = matmul(A, A);
            k >>= 1;
        }
        return ans;
    };
    auto A = mat[0];
    for(int i = 1; i < 60; i++ ){
        A = matmul(A, mat[i]);
    }

    int k = t / 60; // 处理周期
    auto ans = matpow(A, k);
    for(int i = 0; i < t % 60; i++ ){ // 处理余数
        ans = matmul(ans, mat[i]);
    }
    ll res = 0;
    for(int i = 0; i < cnt; i++ ){
        res = max(res, ans[0][i]);
    }
    cout << res << "\n";
    return 0;
}