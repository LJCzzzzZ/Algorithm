#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define se second
#define mp make_pair
#define pii pair<int, int>

int main() 
{
    // 题意: 给定q个询问, Q1：每次告知一个区间的异或值, Q2：每次问一个区间的异或值, 强制在线
    // 题解: 带权并查集, 首先拆位, 到每一位上去考虑, 显然二进制位上非0即1, 满足带权并查集形式
    //       离散化区间端点, 设s[x]为 0 ~ x的前缀异或值, 如果 区间异或值为1, 显然 s[r] ^ s[l - 1] == 1
    //       然后将l, r并进并查集里查询即可
    //        因为每次都是对相同位置操作, 显然拆位是不需要的, 直接维护该位置的和即可
    // trick: 带权并查集合并时, 先查询两点的祖先, 然后将一个祖先并到另一个祖先上, 被并的异或值为 x[u] = x[l] ^ x[r] ^ (l和r之间的关系)
    //        注意不是  x[u] = x[u] ^ x[v] ^ (l和r之间的关系)
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int q;
    cin >> q;
    map<int, int> mp;
    vector<int> f;
    vector<int> xr;
    int n = 0;
    auto get_id = [&](int x){
        if(mp.find(x) != mp.end()){
            return mp[x];
        }
        mp[x] = n;
        f.push_back(n);
        xr.push_back(0);
        n += 1;
        return n - 1;
    };

    function<int(int)> find = [&](int x){
        if(x == f[x]){
            return x;
        }
        int rt = find(f[x]);
        xr[x] ^= xr[f[x]];
        f[x] = rt;
        return f[x];
    };
    int ans = 0;
    while(q--){
        int o;
        cin >> o;
        if(o == 1){
            int l, r, x;
            cin >> l >> r >> x;
            l ^= ans;
            r ^= ans;
            x ^= ans;
            if(l > r){
                swap(l, r);
            }
            l -= 1;
            l = get_id(l);
            r = get_id(r);
            int u = find(l);
            int v = find(r);
            if(u != v){
                xr[u] = xr[l] ^ xr[r] ^ x;
                f[u] = v;
            }
        } else {
            int l, r;
            cin >> l >> r;
            l ^= ans;
            r ^= ans;
            if(l > r){
                swap(l, r);
            }
            l -= 1;
            l = get_id(l);
            r = get_id(r);
            int u = find(l);
            int v = find(r);
            if(u == v){
                ans = xr[l] ^ xr[r];
            } else {
                ans = -1;
            }
            cout << ans << "\n";
            ans = abs(ans);
        }
    }
    return 0;
}