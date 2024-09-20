#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define se second
#define mp make_pair
#define pii pair<int, int>
const int N = 1010;
int sg1[N], sg2[N];
int l, r;
int dfs1(int x){
    if(x < l) return sg1[x] = 0; // 确定终态, 必败态
    if(sg1[x] != -1) return sg1[x]; // 记忆化搜索
    set<int> s;
    for(int i = l; i <= r; i++ ){
        for(int j = 0; j + i <= x; j++ ){
            s.insert(dfs1(j) ^ dfs1(x - (j + i))); // 一条链可以分为 x + y + z (y为切去的长度)
        }
    }

    int mex = 0;
    for(auto x : s){
        if(x == mex){
            mex += 1;
        }
    }
    // sg函数值为最小未出现整数 mex 如果sg[x] 为0说明只能转移到后继不为0的状态因此为必败态, sg[x] 不为0说明可以转移到0使得对手为必败态
    return sg1[x] = mex;
}

int dfs2(int x){
    if(x < l) return 0;
    set<int> s;
    for(int i = l; i <= r; i++ ){
        s.insert(dfs1(x - i));
    }
    int mex = 0;
    for(auto x : s){
        if(x == mex){
            mex += 1;
        }
    }
    return mex;
}
int main() 
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("data.out", "w", stdout);
    cin >> l >> r;
    memset(sg1, -1, sizeof sg1);
    for(int i = 0; i < l; i++ ){
        sg1[i] = 0;
    }
    for(int i = 1; i <= 100; i++ ){
        dfs1(i);
    }

    for(int i = 1; i <= 100; i++ ){
        cout << i << " " << dfs2(i) << "\n";
    }
    return 0;
}