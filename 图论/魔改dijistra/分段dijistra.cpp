#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define se second
#define mp make_pair
#define pii pair<int, int>

int main() 
{
    // https://atcoder.jp/contests/abc307/tasks/abc307_f
    // 题意: 给出一张图, 每一天可以从被感染的点感染距离 <= xi的点
    // 题解: 分段dijistra, 每次从最新被感染的点开始, 询问他的边, 对于满足w <= xi的边说明这次感染可以去到u
    // 那么可以实现一个trick, 有一个优先队列 q1保存之前被感染的点的边, 每天更新时, 先从q1中取出可以扩散的点
    // 然后维护一个优先队列q2 维护一个距离w： 从上一轮被感染的点到目前点的距离, 并把边加入q1
    // 循环k天即可 复杂度O((n + m)logn)
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> adj(n);
    for(int i = 0; i < m; i++ ){
        int x, y, w;
        cin >> x >> y >> w;
        x--, y--;
        adj[x].emplace_back(y, w);
        adj[y].emplace_back(x, w);
    }
    int k;
    cin >> k;
    vector<int> A(k);
    for(int i = 0; i < k; i++ ){
        cin >> A[i];
        A[i]--;
    }
    int d;
    cin >> d;
    vector<int> X(d + 1);
    for(int i = 1; i <= d; i++ ){
        cin >> X[i];
    }
    priority_queue<pair<int, int>> q;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> p;
    for(int i = 0; i < k; i++ ){
        p.emplace(0, A[i]);
    }
    vector<int> f(n, -1), ans(n, - 1);
    for(int i = 0; i <= d; i++ ){
        while(!p.empty()){
            auto [w, x] = p.top();
            if(w > X[i]){
                break;
            }
            q.emplace(X[i] - w, x);
            p.pop();
        }
        while(!q.empty()){
            auto [d, x] = q.top();
            q.pop();
            if(f[x] != -1){
                continue;
            }
            f[x] = d;
            ans[x] = i;
            for(auto [u, w] : adj[x]){
                if(w <= d){
                    q.emplace(d - w, u);
                }
                p.emplace(w, u);
            }
        }
    }
    for(int i = 0; i < n; i++ ){
        cout << ans[i] << "\n";
    }
    return 0;
}