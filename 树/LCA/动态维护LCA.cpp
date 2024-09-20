#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define se second
const int LOG = 20;
int main() 
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int Q;
    cin >> Q;
    vector<int> p1(1, -1); // 题目给出直接祖先
    vector<ll> w(1, 0); // 权值
    vector<int> p2(1, -1); // 权值大于等于该点的祖先

    vector<vector<int>> anc(1, vector<int>(LOG, -1));
    vector<vector<ll>> sum(1, vector<ll>(LOG, 0));
    int cnt = 1;
    ll last = 0;
    for(int i = 0; i < Q; i++ ){
        int o;
        cin >> o;
        if(o == 1){
            ll p, q;
            cin >> p >> q;
            ll R = p ^ last;
            ll W = q ^ last;
            R--;
            p1.push_back(R);
            w.push_back(W);
            if(w[R] >= W){ // 能连上祖先
                p2.push_back(R);
            } else {
                int v = R;
                while(v != -1 && w[v] < W){
                    v = p2[v];
                }
                p2.push_back(v);
            }

            anc.push_back(vector<int> (LOG, -1));
            sum.push_back(vector<ll> (LOG, 0));
            if(p2.back() != -1){
                anc.back()[0] = p2.back();
                sum.back()[0] = w[p2.back()];
                int v = p2.back();
                int e = 1;
                ll s = w[p2.back()];
                while(1){
                    s += sum[v][e - 1];
                    v = anc[v][e - 1];
                    if(v == -1){
                        break;
                    }
                    anc.back()[e] = v;
                    sum.back()[e] = s;
                    e++;
                }
            }
        } else {
            ll p, q;
            cin >> p >> q;
            ll R = p ^ last;
            ll X = q ^ last;
            R--;
            last = 0;
            if(X >= w[R]){
                X -= w[R];
                last = 1;
                int v = R;
                for(int i = LOG - 1; i >= 0; i-- ){
                    if(anc[v][i] != -1){
                        if(X >= sum[v][i]){
                            X -= sum[v][i];
                            v = anc[v][i];
                            last += (1 << i);
                        }
                    }
                }
            }
            cout << last << "\n";
        }
    }
    return 0;
}