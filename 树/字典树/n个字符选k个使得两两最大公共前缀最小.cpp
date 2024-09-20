#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define se second
#define mp make_pair
#define pii pair<int, int>
const int N = 1e6 + 10;
int tr[N][26], sz[N], ed[N];
void solve(){
    int n, k;
    cin >> n >> k;
    int cnt = 0;
    auto newNode = [&](){
        cnt++;
        sz[cnt] = ed[cnt] = 0;
        memset(tr[cnt], 0, sizeof tr[cnt]);
        return cnt;
    };
    newNode();
    auto add = [&](string s){
        int p = 1;
        int m = s.size();
        for(int i = 0; i < m; i++ ){
            int c = s[i] - 'a';
            if(!tr[p][c]){
                tr[p][c] = newNode();
            }
            p = tr[p][c];
            sz[p] += 1;
            if(i == m - 1){
                ed[p] += 1;
            }
        }
    };
    vector<string> s(n);
    for(int i =  0; i < n; i++ ){
        cin >> s[i];
        add(s[i]);
    }

    string ans = "";
    int p = 1;
    while(k >= 2){
        // cout << k << " " << ans << " " << p << "xx\n";
        bool ok = false;
        int ctt = 0;
        int tot = 0;
        for(int i = 0; i < 26; i++ ){
            if(!tr[p][i]){
                continue;
            }
            ok = true;
            ctt += 1;
            tot += sz[tr[p][i]];
            sz[tr[p][i]] -= 1;
        }   
        if(ctt >= k || tot == ctt){
            break;
        }
        int last = -1;
        for(int i = 0; i < 26; i++ ){
            if(!tr[p][i]){
                continue;
            }
            if(sz[tr[p][i]]){
                last = i;
                if(ctt + sz[tr[p][i]] >= k){
                    k = k - (ctt - 1);
                    k = max(0, k - ed[tr[p][i]]);
                    break;
                }
                ctt += sz[tr[p][i]];
            }
        }
        if(last == -1){
            break;
        }
        ans += char('a' + last);
        p = tr[p][last];
        if(!ok){
            break;
        }
    }   
    cout << (ans.empty() ? "EMPTY" : ans) << "\n";
}
int main() 
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while(T--){
        solve();
    }
    return 0;
}           