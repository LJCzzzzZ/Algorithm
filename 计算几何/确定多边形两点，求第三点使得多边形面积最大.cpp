#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define se second
#define mp make_pair
#define pii pair<int, int>
struct Point{
    ll x, y;
};
void solve(){
    // 题意: 逆时针给出n个点, 求包含连续k条边b - c再选定一个点构成的多边形面积最大
    // 题解: 多边形构成 = 三角形abc + 多边形b - c, 那么枚举b, c就确定了, 然后就是要求使得三角形面积abc最大的a点
    //       (1). 三分求
    //       (2). 随着bc旋转, 点a也跟着旋转, a有单调性。
    // 多边形面积 S = Σcross(i, i + 1)  i <= n 
    int n, k;
    cin >> n >> k;
    vector<Point> P(n);
    for(int i = 0; i < n; i++ ){
        cin >> P[i].x >> P[i].y;
    }
    auto cross = [&](int a, int b){
        return P[a].x * P[b].y - P[b].x * P[a].y;
    };
    ll sum = 0;
    for(int i = 1; i <= k; i++ ){
        sum += cross(i - 1, i);
    }
    ll ans = 0;
    for(int b = 0, a = k; b < n; b++ ){
        int c = (b + k) % n;
        while(a != b){
            ll cur = cross(c, a) + cross(a, b);
            ll nxt = cross(c, (a + 1) % n) + cross((a + 1) % n, b);
            if(cur < nxt){
                a = (a + 1) % n;
            } else {
                break;
            }
        }
        ans = max(ans, sum + cross(c, a) + cross(a, b));
        sum -= cross(b, (b + 1) % n) - cross(c, (c + 1) % n);
        if(a == c){
            a = (a + 1) % n;
        }
    }
    cout << fixed << setprecision(12) << 1.0 * ans / 2 << "\n";
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