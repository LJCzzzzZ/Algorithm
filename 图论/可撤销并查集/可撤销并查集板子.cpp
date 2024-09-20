#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define se second
#define mp make_pair
#define pii pair<int, int>

constexpr int N = 2E5;

int f[N];
int e[N];
int s[N];

int find(int x){ // 不进行路径压缩, 根据启发式合并最多经过logn个点
    while(x != f[x]){
        x = f[x];
    }
    return x;
}

vector<pair<int &, int>> a; // 被改值传引用, 修改所有版本被改成的新值
void change(int &x, int y){
    a.emplace_back(x, x); // first是引用值下面被改, second是const值代表当前版本的旧值
    x = y;
}

bool merge(int x, int y){
    x = find(x);
    y = find(y);
    if(x == y){
        if(!e[x]){ // 原来联通, 多加一条边就形成环
            change(e[x], 1);
            return true;
        } else {
            return false;
        }
    }
    if(e[x] && e[y]){ // 两个不同的并查集都有环即所有点都可以被选就不合并了
        return false;
    }

    if(s[x] < s[y]){ // 启发式合并
        swap(x, y);
    }
    change(s[x], s[x] + s[y]);
    change(e[x], e[x] + e[y]);
    change(f[y], x); // 根指向并查集大小 较小的
    return true;
}
int main() 
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 树路径上两个数任选一个, 问根到每个点选出的集合中最多有多少个不同的数
    // 对每个点x的 <a[x], b[x]> 连边, 对每个联通块, 若有环则能全选, 否则能选 siz - 1个
    // 因此对树进行dfs 进去时连边, 退出时撤销操作, 由并查集撤销操作 想到可撤销并查集
    int n;
    cin >> n;
    iota(f, f + N, 0);
    fill(s, s + N, 1);
    vector<int> A(n), B(n);
    for(int i = 0; i < n; i++ ){
        cin >> A[i] >> B[i];
        A[i]--, B[i]--;
    }

    vector<vector<int>> adj(n);
    for(int i = 0; i < n - 1; i++ ){
        int x, y;
        cin >> x >> y;
        x--, y--;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    vector<int> ans(n);
    auto dfs = [&](auto self, int x, int p, int res) -> void {
        int t = a.size();
        res += merge(A[x], B[x]);
        ans[x] = res;
        for(auto u : adj[x]){
            if(u == p){
                continue;
            }
            self(self, u, x, res);
        }
        while(a.size() > t){ // 并查集操作撤销, 撤销到之前的操作大小
            auto [x, y] = a.back();
            a.pop_back();
            x = y;
        }
    };
    dfs(dfs, 0, -1, 0);
    for(int i = 1; i < n; i++ ){
        cout << ans[i] << " \n"[i == n - 1];
    }
    return 0;
}