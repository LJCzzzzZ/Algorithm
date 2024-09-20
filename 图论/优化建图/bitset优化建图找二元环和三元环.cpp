#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define se second
#define mp make_pair
#define pii pair<int, int>
const int N = 300;
bitset<N> in[N], out[N];
int n, m;
int f[N];
int find(int x){
    return f[x] == x ? x : f[x] = find(f[x]);
}

bool merge(int u, int v){
    u = find(u), v = find(v);
    if(u == v){
        return false;
    }
    if(u > v){
        swap(u, v);
    }
    f[v] = u;
    in[u] |= in[v];
    out[u] |= out[v];
    return false;
}

void rebuild(){
    for(int i = 0; i < n; i++ ){
        if(find(i) == i){
            for(int j = 0; j < n; j++ ){
                if(find(j) != j){
                    if(in[i][j]){
                        in[i][find(j)] = 1;
                        in[i][j] = 0;
                    }     
                    if(out[i][j]){
                        out[i][find(j)] = 1;
                        out[i][j] = 0;
                    }
                }
            }
            in[i][i] = out[i][i] = 0;
        }
    }
}
bool work(){
    for(int i = 0; i < n; i++ ){
        if(find(i) == i){
            auto bit = in[i] & out[i];
            if(bit.count() != 0){
                int x = bit._Find_first();
                merge(i, x);
                return true;
            }
        }
    }

    for(int i = 0; i < n; i++ ){
        if(find(i) == i){
            for(int j = out[i]._Find_first(); j < n; j = out[i]._Find_next(j) ){
                auto bit = in[i] & out[j];
                if(bit.count() != 0){
                    int p = bit._Find_first();
                    merge(i, j);
                    merge(i, p);
                    return true;
                }
            }
        }
    }
    return false;
}
int main() 
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // 一直合并所有大小小于等于3的环 问到每个缩点的最短距离
    // 用bitset保存每个点能到达的和 谁能到达自己 in[a][b] out[a][b]
    // 枚举二元环即有 in[a] & out[a] 1的个数大于0  复杂度 300 / 32
    // 枚举三元环, 枚举任意点i, 然后枚举能到达点j 若有 in[i] & out[j] 1的个数大于0
    // 说明有 i -> j j -> k k -> i形成三元环 复杂度 300 * 300 / 32 * 300 / 32 = 3e4
    // 二元环和三元环上点进行并查集合并
    // 最多有300 / 2 个环 总复杂度 = 300 / 2 * 3e4 = 1e7

    cin >> n >> m;
    iota(f, f + n, 0);
    for(int i = 0; i < m; i++ ){
        int a, b;
        cin >> a >> b;
        a--, b--;
        out[a][b] = 1;
        in[b][a] = 1;
    }

    while(work()){
        rebuild();
    }

    vector<int> dis(n, -1);
    dis[0] = 0;
    queue<int> q;
    q.push(0);
    while(!q.empty()){
        auto x = q.front();
        q.pop();
        for(int i = 0; i < n; i++ ){
            if(out[x][i] && !~dis[i]){
                dis[i] = dis[x] + 1;
                q.push(i);
            }
        }
    }
    for(int i = 0; i < n; i++ ){
        cout << dis[find(i)] << " \n"[i == n - 1];
    }
    return 0;
}