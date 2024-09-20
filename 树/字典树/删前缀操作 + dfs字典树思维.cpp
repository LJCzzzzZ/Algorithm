#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define se second
#define mp make_pair
#define pii pair<int, int>
const int N = 3e5 + 10;
int tr[N][26], sz[N];
int main() 
{
    // 题意: 给定n个字符串, 每一次操作可以删除拥有相同前缀的不多于k个字符串, 且此时拥有这个前缀的字符串不能多于k个
    // 题解: 把每个字符串插入到字典树中, 并记录sz[i], 当前以i为结尾的剩余字符串个数
    //       dfs自底向上遍历整颗字典树, 统计当前结点为枚举点还未被删除的字符串个数包括儿子大小小于k的(不能一次操作恰好删完的)
    //       那么当前字符串可分为两类, (1). 要在以儿子为结尾的地方删掉 (2). 要以当前结点为结尾删掉
    //       有个显然, 显然只能先删除部分儿子的(因为当前结点个数大于k), 然后以自己为结点删除k的倍数个(就算给父节点去删操作次数不变)
    //       删儿子时, 显然先删大的好, 因为先删小的操作次数不变, 而要使字符串个数尽可能变小, 删大的更优  
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k;
    cin >> n >> k;
    int cnt = 0;
    auto newNode = [&](){
        ++cnt;
        sz[cnt] = 0;
        return cnt;
    };
    newNode();
    auto add = [&](string s){
        int m = s.size();
        int p = 1;
        for(int i = 0; i < m; i++ ){
            int c = s[i] - 'a';
            if(!tr[p][c]){
                tr[p][c] = newNode();
            }
            p = tr[p][c];
        }
        sz[p] += 1;
    };
    for(int i = 0; i < n; i++ ){
        string s;
        cin >> s;
        add(s);
    }

    int ans = 0;
    auto dfs = [&](auto self, int x) -> int {
        int res = sz[x];
        vector<int> cand;
        for(int i = 0; i < 26; i++ ){
            if(tr[x][i]){
                int v = self(self, tr[x][i]);
                cand.push_back(v);
                res += v;
            }
        }
        sort(cand.begin(), cand.end());
        while(!cand.empty() && k < res ){
            res -= cand.back();
            cand.pop_back();
            ans += 1;
        }
        if(res >= k){
            ans += res / k;
            res %= k;
        }
        return res;
    };

    if(dfs(dfs, 1)){
        ans += 1;
    }
    cout << ans << "\n";
    return 0;
}                   