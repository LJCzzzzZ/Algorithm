#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define se second
#define mp make_pair
#define pii pair<int, int>

int main() 
{
    // 题意: 给定一个排列问有多少个区间[L, R]满足 最小值的小标 < 最大值的下标
    // trick: 区间个数计数经典技巧, 枚举每个右端点有多少个合法区间数
    // 题解: 单调栈操作
    // 考虑将每一个数当成一个物品 event(idx, type)
    // type = 0代表为作为区间最小值出现, 1为最大值
    // 当右端点移动时, (1). 当一个数作为最小值出现, 那么前面比自己大的数就能不能作为左端点出现, 要减去一段段 [L1, R1].. [Lx, Rx]
    // 即弹出单调栈顶部的值, 并找到映射到set中的位置p1, 再找到其前缀p2, 那么p1 - p2 就不是一段合法的左端点, 直到遇到比自己小的
    // (2). 当一个数作为最大值出现, 那么比自己小的数就可以当成左端点出现, 即要加上一段区间[L1, R1].. [Lx, Rx]
    // 枚举过程中cur 为当前合法区间数进行动态变化, 每次ans += cur即可
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    set<pair<int, int>> cur;
    cur.emplace(-1, 0);
    cur.emplace(-1, 1);
    vector<pair<int, int>> smi, smx;
    smi.emplace_back(-1, -1);
    smx.emplace_back(n, -1);
    ll ans = 0, d = 0;
    for(int i = 0; i < n; i++ ){
        int x;
        cin >> x;
        x--;
        while(smi.back().fi > x){
            auto p = cur.lower_bound({smi.back().se, 0});
            auto pre = prev(p);
            d -= p->first - pre->first;
            cur.erase(p);
            smi.pop_back();
        }
        d += 1;
        smi.emplace_back(x, i);
        cur.emplace(i, 0);

        while(smx.back().fi < x){
            auto p = cur.lower_bound({smx.back().se, 1});
            auto pre = prev(p);
            d += p->first - pre->first;
            cur.erase(p);
            smx.pop_back();
        }
        smx.emplace_back(x, i);
        cur.emplace(i, 1);
        ans += d;
    }
    cout << ans - n << "\n";
    return 0;
}