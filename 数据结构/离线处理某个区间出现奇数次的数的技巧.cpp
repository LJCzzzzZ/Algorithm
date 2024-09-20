#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define se second
#define mp make_pair
#define pii pair<int, int>
const int N = 5e5 + 10;
int lowbit(int x) { return x & -x;}
int c[N];
void update(int x, int w){
    for(; x < N; x += lowbit(x) ){
        c[x] ^= w;
    }
}
int query(int x){
    int res = 0;
    for(; x ; x -= lowbit(x) ){
        res ^= c[x];
    }
    return res;
}
int main() 
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    map<int, int> mp;
    vector<int> a(n + 1);
    vector<int> pre(n + 1);
    for(int i = 1; i <= n; i++ ){
        cin >> a[i];
        pre[i] = mp[a[i]]; // 记录上一次出现的地方
        mp[a[i]] = i;   // 最后一次出现的地方
    }

    vector<int> s(n + 1);
    for(int i = 1; i <= n; i++ ){
        s[i] = s[i - 1] ^ a[i];
    }

    vector<tuple<int, int, int>> que;
    for(int i = 0; i < q; i++ ){
        int l, r;
        cin >> l >> r;
        que.emplace_back(r, l, i);
    }
    sort(que.begin(), que.end());

    vector<int> ans(q);
    for(int i = 0, j = 1; i < q; i++ ){
        auto [R, L, id] = que[i];
        while(j <= R){
            if(pre[j]){ // 覆盖掉上一次出现的
                update(pre[j], a[j]);
            }
            update(j, a[j]);
            j++;
        }
        ans[id] = (query(R) ^ query(L - 1) ^ s[R] ^ s[L - 1]);
    }

    for(int i = 0; i < q; i++ ){
        cout << ans[i] << "\n";
    } 
    return 0;
}