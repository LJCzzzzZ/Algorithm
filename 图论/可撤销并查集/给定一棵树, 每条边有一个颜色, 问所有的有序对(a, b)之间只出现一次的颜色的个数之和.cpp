#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define se second
#define mp make_pair
#define pii pair<int, int>

int main() 
{
    // 题意: 给定一棵树, 每条边有一个颜色, 问所有的有序对<a, b>之间只出现一次的颜色的个数之和
    // 这一类问题考虑对颜色单独考虑或者在lca处考虑
    // 现考虑颜色, 答案总和 = 各颜色贡献相加, 因此快速算出单独一种颜色贡献即可
    // 题解: 值域分治 + 可撤销并查集
    // 对[1, L - 1] 和 [L + 1, R] 所有颜色的边连进并查集后, 整棵树被颜色L的边分成若干块, 答案即为被边相连的块之间的乘积
    // 复杂度为 遍历到每一个点为 nlogn 每条边会被加一次, 撤销一次,和可撤销并查集的logn 所有总复杂度为O(n*logn*logn + m)
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<vector<pair<int, int>>> adj(n);
    for(int i = 0; i < n - 1; i++ ){
        int x, y, w;
        cin >> x >> y >> w;
        x--, y--;
        w--;
        adj[w].emplace_back(x, y);
    }
    vector<int> fa(n), siz(n, 1);
    iota(fa.begin(), fa.end(), 0);
    auto find = [&](int x){
        while(x != fa[x]){
            x = fa[x];
        }
        return x;
    };
    vector<pair<int &, int>> a;
    auto change = [&](int &u, int v){
        a.emplace_back(u, u);
        u = v;
    };
    auto merge = [&](int x, int y){
        x = find(x);
        y = find(y);
        if(x == y){
            return false;
        }
        if(siz[x] < siz[y]){
            swap(x, y);
        }
        change(siz[x], siz[x] + siz[y]);
        change(fa[y], x);
        return true;
    };
    auto Rollback = [&](int cur){
        while(a.size() > cur){
            auto [x, y] = a.back();
            a.pop_back();
            x = y;
        }
    };
    ll ans = 0;
    auto dfs = [&](auto self, int L, int R) -> void {
        if(L == R){
            for(auto [i, j] : adj[L]){
                ans += 1ll * siz[find(i)] * siz[find(j)];
            }
            return;
        }
        int mid = L + R >> 1;
        {
            int cur = a.size();
            for(int i = mid + 1; i <= R; i++ ){
                for(auto [x, y] : adj[i]){
                    merge(x, y);
                }
            }
            self(self, L, mid);
            Rollback(cur);
        }
        {
            int cur = a.size();
            for(int i = L; i <= mid; i++ ){
                for(auto [x, y] : adj[i]){
                    merge(x, y);
                }
            }
            self(self, mid + 1, R);
            Rollback(cur);
        }
    };
    dfs(dfs, 0, n - 1);
    cout << ans << "\n";
    return 0;
}