#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define se second
#define mp make_pair
#define pii pair<int, int>

const int N = 5e5 + 10;
int f[N];
int s[N];

int find(int x){
    while(x != f[x]){
        x = f[x];
    }
    return x;
}
vector<pair<int &, int>> a;
void change(int &x, int y){
    a.emplace_back(x, x);
    x = y;
}
bool merge(int x, int y){
    x = find(x);
    y = find(y);
    if(x == y){
        return false;
    }
    if(s[x] < s[y]){
        swap(x, y);
    }
    change(s[x], s[x] + s[y]);
    change(f[y], x);
    return true;
}
int main() 
{
    // 题意: 给定一张图, 给出多组询问, 每组询问包含多条不重复的边, 问是否存在一棵最小生成树包含里面所有的边
    // 题解: 性质题: 性质(1). 在同一张图任意的最小生成树中, 各权值的边的数量相等
    //              性质(2). 在同一张图任意的最小生成树中, 只添加权值小于x的边最后图的连通性是一样的
    // 那么可以将询问按权值离线, 对于同一权值的边, 又分成各询问组来查询, 对于同一询问组里的边, 添加到并查集里, 如果形成了环
    // 说明这条边必定不是MST上的边(MST无环, 且该边小于环上原本的边), 那么该询问组不符合, 因为要撤销每一次询问组的影响, 要用可撤销并查集
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<int> x(m), y(m), w(m);
    for(int i = 0; i < m; i++ ){
        cin >> x[i] >> y[i] >> w[i];
    }
    for(int i = 0; i < n; i++ ){
        s[i] = 1;
        f[i] = i;
    }
    int q;
    cin >> q;
    vector<vector<pair<int, int>>> que(N);
    for(int i = 0; i < q; i++ ){
        int k;
        cin >> k;
        for(int j = 0; j < k; j++ ){
            int x;
            cin >> x;
            x--;
            que[w[x]].emplace_back(x, i);
        }
    }
    vector<int> order(m);
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&](int a, int b){
        return w[a] < w[b];
    }); 
    vector<int> ans(q, 1);
    for(int i = 0; i < m; i++ ){
        int j = order[i];
        int val = w[j];
        int cur = a.size();
        for(int k = 0; k < (int)que[val].size(); k++ ){
            auto [u, id] = que[val][k];
            if(k > 0 && que[val][k - 1].se != que[val][k].se){
                while(a.size() > cur){
                    auto [x, y] = a.back();
                    a.pop_back();
                    x = y;
                }
            }
            if(!merge(x[u], y[u])){
                ans[id] = 0;
            }
        }

        int k = i;
        merge(x[j], y[j]);
        while(k + 1 < m && w[order[k + 1]] == val){
            merge(x[order[k + 1]], y[order[k + 1]]);
            k += 1;
        }
        i = k;
    }

    for(int i = 0; i < q; i++ ){
        cout << (ans[i] ? "YES" : "NO") << "\n";
    }
    return 0;
}