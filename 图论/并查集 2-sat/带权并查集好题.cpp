#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define se second
#define mp make_pair
#define pii pair<int, int>

int main() 
{
    // 题意: 给定 k个子集, 任意3个子集没有交集, 一个操作可以使子集中所有状态反转问让前i个灯亮起来的最少操作次数
    // 题解: 按顺序考虑每一个位置, 由题意可知任意一个位置顶多属于两个子集, 因此考虑分类讨论
    //       (1). 当属于一个子集时: 判断该位置是否是必选, 维护一个必选集合
    //       (2). 当属于两个子集时: 合并并查集, 连边为两并查集祖先, 边权为是否需要选其中一个
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    vector<vector<int>> at(n);
    for(int i = 0; i < k; i++ ){
        int m;
        cin >> m;
        for(int j = 0; j < m; j++ ){
            int x;
            cin >> x;
            x--;
            at[x].push_back(i);
        }
    }

    vector<int> f(k), d(k), eq(k, 1), neq(k), must(k, -1);
    iota(f.begin(), f.end(), 0);
    function<int(int)> find = [&](int x){
        if(x == f[x]){
            return x;
        }
        int rt = find(f[x]);
        d[x] ^= d[f[x]];
        f[x] = rt;
        return f[x];
    };

    auto merge = [&](int x, int y, int z){
        x = find(x);
        y = find(y);
        if(x == y){
            return false;
        }
        f[y] = x;
        d[y] = z;
        if(z == 0){
            eq[x] += eq[y];
            neq[x] += neq[y];
        } else {
            eq[x] += neq[y];
            neq[x] += eq[y];
        }

        if(must[y] != -1){
            int val = must[y] ^ d[y];
            must[x] = val;
        }
        return true;
    };

    auto calc = [&](int x){
        if(must[x] == 1){
            return eq[x];
        }
        if(must[x] == 0){
            return neq[x];
        }
        return min(eq[x], neq[x]);
    };
    int ans = 0;
    for(int i = 0; i < n; i++ ){
        if(at[i].size() == 1){
            int x = at[i][0];
            int r = find(x);
            ans -= calc(r);
            int val;
            if((s[i] == '0' && d[x] == 1) || (s[i] == '1' && d[x] == 0)){
                val = 0;
            } else {
                val = 1;
            }
            must[r] = val;
            ans += calc(r);
        } else if(at[i].size() == 2){
            int x = at[i][0];
            int y = at[i][1];
            int u = find(x);
            int v = find(y);
            if(u != v){
                ans -= calc(u) + calc(v);
                merge(u, v, (s[i] == '0') ^ d[x] ^ d[y]);
                ans += calc(u);
            }
        }
        cout << ans << "\n";
    }
    return 0;
}