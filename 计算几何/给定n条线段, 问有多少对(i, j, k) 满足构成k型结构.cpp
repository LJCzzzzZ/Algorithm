#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define se second
#define mp make_pair
#define pii pair<int, int>
using T = ll;
struct Point {
    T x;
    T y;
    Point(T x = 0, T y = 0) : x(x), y(y) {}
    
    Point &operator+=(const Point &p) {
        x += p.x, y += p.y;
        return *this;
    }
    Point &operator-=(const Point &p) {
        x -= p.x, y -= p.y;
        return *this;
    }
    Point &operator*=(const T &v) {
        x *= v, y *= v;
        return *this;
    }
    friend Point operator-(const Point &p) {
        return Point(-p.x, -p.y);
    }
    friend Point operator+(Point lhs, const Point &rhs) {
        return lhs += rhs;
    }
    friend Point operator-(Point lhs, const Point &rhs) {
        return lhs -= rhs;
    }
    friend Point operator*(Point lhs, const T &rhs) {
        return lhs *= rhs;
    }
};
// 点乘 a * b = |a| * |b| * cosα
T dot(const Point &a, const Point &b) {
    return a.x * b.x + a.y * b.y;
}
// 叉乘 a * b = |a| * |b| * sinα
T cross(const Point &a, const Point &b) {
    return a.x * b.y - a.y * b.x;
}
void solve(){
    // 题意: 给定n条线段, 问有多少对<i, j, k> 满足构成k型结构
    // n <= 1000 考虑n^2 ~ n^2 * logn的算法
    // 枚举每一条线段为主干, 然后枚举剩余线段, 确定一点为聚集点, 确定另一点在直线的左端还是右端, 以及其斜率
    // (1). 确定点在直线左端还是右端, 每次都以向量 a -> b为主干向量, 与向量 a -> c作叉乘, 结果为正则,
    //      a -> b -> c满足逆时针, 否则顺时针, 即可用面积正负区分左右
    // (2). 当确定一端点, 枚举其他端点, 要确定其斜率时, x = (a.x - b.x) y = (a.y - b.y) x和y同除gcd(x, y)即可
    // 最后计算时容斥或者双指针计算即可
    int n;
    cin >> n;
    vector<vector<Point>> p(n, vector<Point> (2));
    for(int i = 0; i < n; i++ ){
        for(int j = 0; j < 2; j++ ){
            cin >> p[i][j].x >> p[i][j].y;
        }
    }
    auto Onsegment = [&](Point a, Point b, Point c){
        return cross(b - c, a - c) == 0;
    };
    auto in = [&](Point a, Point b, Point c){
        return cross(b - c, a - c) == 0 && dot(a - c, b - c) < 0;
    };
    ll ans = 0;
    for(int i = 0; i < n; i++ ){
        auto x = p[i][0], y = p[i][1];
        vector<map<pair<ll, ll>, vector<Point>>> c(2);
        for(int j = 0; j < n; j++ ){
            if(cross(p[i][0] - p[j][0], p[i][1] - p[j][1]) == 0){
                continue;
            }
            auto u = p[j][0], v = p[j][1];
            if(in(x, y, u)){
                int sgn = cross(y - x, v - x) < 0;
                ll d1 = (v.x - u.x), d2 = (v.y - u.y);
                ll g = __gcd(d1, d2);
                d1 /= g, d2 /= g;
                c[sgn][{u.x, u.y}].push_back({d1, d2});
            }
            if(in(x, y, v)){
                int sgn = cross(y - x, u - x) < 0;
                ll d1 = (u.x - v.x), d2 = (u.y - v.y);
                ll g = __gcd(d1, d2);
                d1 /= g, d2 /= g;
                c[sgn][{v.x, v.y}].push_back({d1, d2});
            }
        }
        for(int j = 0; j < 2; j++ ){
            for(auto [_, v] : c[j]){
                sort(v.begin(), v.end(), [&](Point a, Point b){
                    return a.x == b.x ? a.y < b.y : a.x < b.x;
                });
                int cnt = (int)v.size();
                for(int k = 0; k < (int)v.size(); k++ ){
                    int z = k;
                    while(z + 1 < v.size() && v[z + 1].x == v[k].x && v[z + 1].y == v[k].y){
                        z += 1;
                    }
                    ans += 1ll * (cnt - (z - k + 1)) * (z - k + 1);
                    k = z;
                }
            }
        }
    }
    cout << ans / 2 << "\n";
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