#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define se second
#define mp make_pair
#define pii pair<int, int>

int main() 
{
    // 题意: 给定一个图, 要求给每个点赋予一个权值形成一个1 - n的排列, 满足 对边<s, t> ps < pt
    // 且 Li <= pi <= Ri
    // (1)有向图想到拓扑排序, 若原图不是DAG图则无解
    // 对于 边<s,t> 满足 Rs <= Pt <= Rt - 1, 先跑一遍拓扑排序使得R的约束条件更新
    // 接下来跑反图从小到大确定 1 - n
    // 开两个优先队列, A为待更新的点(Lx > 当前idx), B为当前可更新点(满足Lx <= 当前idx)
    // 每次从B中更新 Rx最小的点x, 合理性: 因为是跑反图, 满足他指向的点 Ry >= Rx + 1, 当更新更大的点时显然 Rz' > Rz > Ry >= Rx + 1
    // 因此 Rz可以下一回合更新也必定能满足, 而Rx下一回合不一定满足, 因此当前能更新最小的不影响更新更大的数
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n);
    vector<vector<int>> rev_g(n);
    for(int i = 0; i < m; i++ ){
        int x, y;
        cin >> x >> y;
        x--, y--;
        g[y].push_back(x);
        rev_g[x].push_back(y);
    }

    vector<int> L(n), R(n);
    for(int i = 0; i < n; i++ ){
        cin >> L[i] >> R[i];
        L[i] -= 1;
        R[i] -= 1;
    }

    queue<int> que;
    vector<int> deg(n);
    for(int i = 0; i < n; i++ ){
        deg[i] = rev_g[i].size();
        if(deg[i] == 0){
            que.emplace(i);
        }
    }

    while(!que.empty()){
        auto x = que.front();
        que.pop();
        for(auto u : g[x]){
            R[u] = min(R[u], R[x] - 1);
            if(--deg[u] == 0){
                que.emplace(u);
            }
        }
    }

    if(*max_element(deg.begin(), deg.end()) > 0){
        cout << "No\n";
        return 0;
    }

    priority_queue<pii, vector<pii>, greater<pii>> q, pending;
    for(int i = 0; i < n; i++ ){
        deg[i] = g[i].size();
        if(deg[i] == 0){
            pending.emplace(L[i], i);
        }
    }   

    int idx = 0;
    vector<int> ans(n, -1);
    auto refresh = [&](){
        while(!pending.empty()){
            auto [d, x] = pending.top();
            if(d <= idx){
                pending.pop();
                q.emplace(R[x], x);
            } else {
                break;
            }
        }
    };
    while(!q.empty() || !pending.empty()){
        refresh();
        if(!q.empty()){
            auto [_, x] = q.top();
            q.pop();
            if(R[x] < idx){
                cout << "No\n";
                return 0;
            }
            ans[x] = idx++;
            for(auto u : rev_g[x]){
                if(--deg[u] == 0){
                    pending.emplace(L[u], u);
                }
            }
        } else {
            cout << "No\n";
            return 0;
        }
    }
    if(*min_element(ans.begin(), ans.end()) == -1){
        cout << "No\n";
        return 0;
    }
    cout << "Yes\n";
    for(int i = 0; i < n; i++ ){
        cout << ans[i] + 1 << " \n"[i == n - 1];
    }
    return 0;
}