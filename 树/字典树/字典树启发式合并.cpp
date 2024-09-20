#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define se second
#define mp make_pair
#define pii pair<int, int>
const int N = 1e5 + 10;
int tr[N][26];
int was[N];
multiset<int, greater<int>> s[N];
int main() 
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    int cnt = 1;
    auto add = [&](string s){
        int p = 1;
        int m = s.size();
        for(int i = 0; i < m; i++ ){
            int c = s[i] - 'a';
            if(!tr[p][c]){
                tr[p][c] = ++cnt;
            }
            p = tr[p][c];
            if(i == s.size() - 1){
                was[p] = 1;
            }
        }
    };
    vector<string> t(n);
    for(int i = 0; i < n; i++ ){
        cin >> t[i];
        add(t[i]);
    }

    auto dfs = [&](auto self, int cur, int dep) -> void{
        for(int i = 0; i < 26; i++ ){
            int p = tr[cur][i];
            if(p != 0){
                self(self, p, dep + 1);
                if(s[cur].size() < s[p].size()){
                    swap(s[p], s[cur]);
                }
                for(auto x : s[p]){
                    s[cur].insert(x);
                }
                s[p].clear();
            }
        }
        if(!was[cur]){
            if(!s[cur].empty()){
                s[cur].erase(s[cur].begin());
            }
            s[cur].insert(dep);
        } else {
            s[cur].insert(dep);
        }
    };

    int ans = 0;
    for(int i = 0; i < 26; i++ ){
        int p = tr[1][i];
        if(p != 0){
            dfs(dfs, p, 1);
            for(auto x : s[p]){
                ans += x;
            }
            s[p].clear();
        }
    }
    cout << ans << "\n";
    return 0;
}