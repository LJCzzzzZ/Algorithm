#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define se second
#define mp make_pair
#define pii pair<int, int>

int main() 
{
    // 题意: 给定n个点的有根树m和k个序列: 从一棵有根树任意结点开始的中序遍历序列
    // 问原来的树长什么样
    // 因为是中序遍历, 考虑枚举根, 树的根将树划分为左右两棵子树, 若枚举到的是根对于任意序列左右子树元素相同(可左右对调)
    // 对于判断子树元素相同可用哈希： 哈希构造: k次方和(log), 和, 平方和, 异或和
    // 或判断左右子树只有两种类型
    // 复杂度枚举根O(n), 轮数(n + n - 1 + n - 2 + ... + 1) = O(n * n) -> 合法继续推进 期望次数n + k, 单次检查合法O(nk) 总复杂度O(n * n * k)
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k;
    cin >> n >> k;
    vector<vector<int>> dat(k, vector<int> (n));
    for(int i = 0; i < k; i++ ){
        for(int j = 0; j < n; j++ ){
            cin >> dat[i][j];
            dat[i][j]--;
        }
    }
    // return 0;
    vector<int> ans(n);
    auto dfs = [&](auto self, vector<vector<int>> a, int fa) -> void {
        int m = a[0].size();
        if(m == 1){
            ans[a[0][0]] = fa;
            return;
        }
        vector<vector<int>> pos(k, vector<int> (n + 1));
        for(int i = 0; i < k; i++ ){
            for(int j = 0; j < m; j++ ){
                pos[i][a[i][j]] = j;
            }
        }
        auto spilt = [&](vector<int> s, int u, vector<int> &L, vector<int> &R){
            bool find = false;
            for(auto x : s){
                if(x == u){
                    find = true;
                } else if(!find){
                    L.push_back(x);
                } else {
                    R.push_back(x);
                }
            }
        };
        auto check = [&](int u){
            int x = -1, y = -1;
            for(int i = 0; i < k; i++ ){
                int sz = pos[i][u];
                if(!sz){
                    return false;
                }
                if(x == -1 || x == sz){
                    x = sz;
                } else if(y == -1 || y == sz){
                    y = sz;
                } else {
                    return false;
                }
                sz = m - pos[i][u] - 1;
                if(!sz){
                    return false;
                }
                if(x == -1 || x == sz){
                    x = sz;
                } else if(y == -1 || y == sz){
                    y = sz;
                } else {
                    return false;
                }
            }

            vector<int> c, d;
            for(int i = 0; i < k; i++ ){
                vector<int> f, g;
                spilt(a[i], u, f, g);
                sort(f.begin(), f.end());
                sort(g.begin(), g.end());
                if(c.empty() || c == f){
                    c = f;
                } else if(d.empty() || d == g){
                    d = g;
                } else {
                    return false;
                }

                if(d.empty() || d == f){
                    d = f;
                } else if(c.empty() || c == g){
                    c = g;
                } else {
                    return false;
                }
            }
            return true;
        };
        for(auto i : a[0]){
            if(!check(i)){
                continue;
            }
            ans[i] = fa;
            vector<vector<int>> dL, dR;
            int beg = a[0][0];
            for(int j = 0; j < k; j++ ){
                vector<int> L, R;
                spilt(a[j], i, L, R);
                if(find(L.begin(), L.end(), beg) == L.end()){
                    swap(L, R);
                }
                dL.push_back(L);
                dR.push_back(R);
            }
            self(self, dL, i);
            self(self, dR, i);
        }
    };
    dfs(dfs, dat, -2);
    for(int i = 0; i < n; i++ ){
        cout << ans[i] + 1 << " \n"[i == n - 1];
    }
    return 0;
}