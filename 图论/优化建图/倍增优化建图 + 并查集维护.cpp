#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define se second
#define mp make_pair
#define pii pair<int, int>
const int mod = 1e9 + 7;
struct DSU {
    std::vector<int> f, siz;
    DSU(int n) : f(n), siz(n, 1) { std::iota(f.begin(), f.end(), 0); }
    int find(int x) {
        while (x != f[x]) x = f[x] = f[f[x]];
        return x;
    }
    bool same(int x, int y) { return find(x) == find(y); }
    bool merge(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) return false;
        siz[x] += siz[y];
        f[y] = x;
        return true;
    }
    int size(int x) { return siz[find(x)]; }
};
int main() 
{
    // 题解: 给定一个只含有01?的字符串, 给出m个区间[L, R], 这m个区间是回文, ?可随意
    // 问能构造出多少个不同的字符串?
    // 题解: 并查集 + 倍增
    // 将串反转拼接到原串后面, 那么就变成前半串 和 后半串对应位置字符相等的问题
    // 用adj[B][l].push_back(2 * n - l) 表示l 和 2 * n - l处有一段长度为 1 << B的串相同
    // 然后从20 -> 0将 每一层的i 推向 i-1
    // 即adj[B - 1][l].push_back(2 * n - l)
    //   adj[B - 1][l + (1 << (B - 1))].push_back(2 * n - l + (1 << (B - 1)))
    // 最后将 第0层所有点有并查集维护即可, 并将原串和反串相应位置维护
    // 最后检查是否有矛盾并统计答案即可
    // 复杂度O(nlognlogn)
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    string s;
    cin >> s;
    auto t = s;
    reverse(t.begin(), t.end());
    s = s + t;

    int d = s.size();
    const int B = 20;
    vector<vector<vector<int>>> adj(d + 1, vector<vector<int>> (B));
    for(int i = 0; i < m; i++ ){
        int l, r;
        cin >> l >> r;
        l--, r--;
        int D = r - l + 1;
        int nl = 2 * n - 1 - r;
        for(int j = B - 1; j >= 0; j-- ){
            if(D >= 1 << j){
                adj[l][j].push_back(nl);
                adj[nl][j].push_back(l);
                l += (1 << j);
                nl += (1 << j);
                D -= (1 << j);
            }
        }
    }

    for(int i = B - 1; i >= 1; i-- ){
        DSU dsu(d + 1);
        for(int j = 0; j < d; j++ ){
            for(auto x : adj[j][i]){
                if(dsu.same(j, x)){
                    continue;
                }
                dsu.merge(x, j);
                adj[j][i - 1].push_back(x);
                adj[j + (1 << (i - 1))][i - 1].push_back(x + (1 << (i - 1)));
            }
        }
    }

    DSU dsu(d + 1);
    for(int i = 0; i < d; i++ ){
        for(auto x : adj[i][0]){
            dsu.merge(x, i);
        }
    }
    for(int i = 0; i < n; i++ ){
        dsu.merge(i, 2 * n - 1 - i);
    }

    ll ans = 1;
    vector<int> c(d, -1);
    for(int i = 0; i < d; i++ ){
        if(s[i] == '?'){
            continue;
        }
        int u = dsu.find(i);
        if(c[u] == -1){
            c[u] = s[i] - '0';
        } else {
            if(c[u] != s[i] - '0'){
                cout << "0\n";
                return 0;
            }
        }
    }
    for(int i = 0; i < d; i++ ){
        if(dsu.find(i) == i && c[i] == -1){
            ans = ans * 2 % mod;
        }
    }
    cout << ans << "\n";
    return 0;
}