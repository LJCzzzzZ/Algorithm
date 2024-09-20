#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define se second
using T = __int128;
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
 
T dot(const Point &a, const Point &b) {
    return a.x * b.x + a.y * b.y;
}
 
T cross(const Point &a, const Point &b) {
    return a.x * b.y - a.y * b.x;
}
int main() 
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    vector<int> b(n);
    for(int i = 0; i < n; i++ ){
        cin >> b[i];
    }
    sort(b.rbegin(), b.rend());

    vector<Point> h;
    for(int i = 0; i < n; i++ ){
        // 存入线段
        Point p(i + 1, 1ll * (i + 1) * b[i]);  // y = i * x + i * b[i];
        // 当前斜率大于之前斜率, 则之前的线段可以删掉
        while(h.size() > 1 && cross(h.end()[-1] - h.end()[-2], p - h.end()[-1]) >= 0){
            h.pop_back();
        }
        h.push_back(p);
    }

    for(int i = 0; i < m; i++ ){
        int c;
        cin >> c;
        Point p(c, 1);
        // dot(线段, 点) 等于 y = k * x + b 取值
        int l = 0, r = h.size() - 1;
        while(l < r){
            int mid = l + r >> 1;
            // 比较和, 取最值
            if(dot(h[mid], p) < dot(h[mid + 1], p)){
                l = mid + 1;
            } else {
                r = mid;
            }
        }
        ll ans = dot(h[l], p);
        cout << ans << " \n"[i == m - 1];
    }
    return 0;
}       