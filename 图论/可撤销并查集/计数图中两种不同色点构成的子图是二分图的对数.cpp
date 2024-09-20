#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define se second
#define mp make_pair
#define pii pair<int, int>

int main() 
{
    // 题意: 给定一个图, 每个点有一个颜色, 问有多少不同颜色的pair(a, b)使得在这两种颜色的点构成的子图中相邻点的颜色不同
    // 题解: 当一个颜色内部本身不是二分图时, 与其他颜色一起时也一定不是二分图, 因此先用带权并查集判断同色的连通块是否是二分图
    //       当去除完内部本身不是二分图的颜色后, 可以根据边连的不同颜色进行排序, 这样能枚举连续一段连接两个颜色的边,
    //       对于这些边在带权并查集中构建可撤销并查集, 模拟连边看是否构成二分图, 退出时撤销
    //       复杂度O(nlogn)
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> c(n);
    for(int i = 0; i < n; i++ ){
        cin >> c[i];
        c[i]--;
    }

    vector<int> good(k, 1);
    vector<int> f(n);
    vector<int> d(n);
    iota(f.begin(), f.end(), 0);
    auto find = [&](int x){
        int a = x, b = 0;
        while(a != f[a]){   
            b ^= d[a];
            a = f[a];
        }
        return make_pair(a, b);
    };
    vector<pair<int &, int>> his;
    vector<int> siz(n, 1);
    auto merge = [&](int a, int b, bool rec = false){
        auto [x, u] = find(a);
        auto [y, v] = find(b);
        if(x == y){
            if(u == v){
                return false;
            }
            return true;
        } else {
            if(siz[x] < siz[y]){
                swap(x, y);
                swap(u, v);
            }
            if(rec) his.emplace_back(siz[x], siz[x]);
            siz[x] += siz[y];
            if(rec) his.emplace_back(f[y], f[y]);
            f[y] = x;
            if(rec) his.emplace_back(d[y], d[y]);
            d[y] = u ^ v ^ 1;
            return true;
        }
    };
    vector<int> x(m), y(m);
    for(int i = 0; i < m; i++ ){
        cin >> x[i] >> y[i];
        x[i]--, y[i]--;
        if(c[x[i]] > c[y[i]]){ // 左小右大, 用于边排序
            swap(x[i], y[i]);
        }
        if(c[x[i]] == c[y[i]] && !merge(x[i], y[i], false)){
            good[c[x[i]]] = 0;
        }
    }
    vector<int> order(m);
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&](int a, int b){
        return make_pair(c[x[a]], c[y[a]]) < make_pair(c[x[b]], c[y[b]]);
    });
    int cnt = accumulate(good.begin(), good.end(), 0);
    ll ans = 1ll * cnt * (cnt - 1) / 2;
    for(int i = 0; i < m; i++ ){
        int j = order[i];
        int z = i;
        while(z + 1 < m && c[x[order[z + 1]]] == c[x[j]] && c[y[order[z + 1]]] == c[y[j]]){
            z += 1;
        }
        if(c[x[j]] != c[y[j]] && good[c[x[j]]] && good[c[y[j]]]){
            for(int s = i; s <= z; s++ ){
                if(!merge(x[order[s]], y[order[s]], true)){
                    ans -= 1;
                    break;
                }
            }
            while(!his.empty()){
                auto [x, y] = his.back();
                his.pop_back();
                x = y;
            }
        }
        i = z;
    }
    cout << ans * 2 << "\n";
    return 0;
}           