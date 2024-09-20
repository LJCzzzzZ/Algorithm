#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define se second
#define mp make_pair
#define pii pair<int, int>
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
int main() 
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // 对于在原点(0, 0)的点来说, 有n个(+/-x, +/-y)的操作使用两次占用n * n矩阵的格子数的期望为 n * n / 2
    // 说明期望不被占用的概率为 1 / 2
    // 看到1 / 2概率自然地想到随机化枚举多次点位然后跑一次双向搜索看是否能不被b到达
    int n;
    cin >> n;
    int ax, ay, bx, by;
    cin >> ax >> ay >> bx >> by;
    vector<int> x(n), y(n);
    for(int i = 0; i < n; i++ ){
        cin >> x[i] >> y[i];
    }
    set<pair<int, int>> s;
    for(int i = 0; i < n; i++ ){
        s.insert(make_pair(x[i], y[i]));
    }
    s.insert(make_pair(0, 0));
    bool ok1 = false;
    for(int i = 0; i < n; i++ ){
        int dx = ax + x[i], dy = ay + y[i];
        if(dx < 1 || dy < 1 || dx > n || dy > n){
            continue;
        }
        int nx = bx - dx, ny = by - dy;
        if(s.count(make_pair(nx, ny))){
            ok1 = true;
        }
    }

    if(ok1){
        cout << "Alice wins\n";
    } else {
        bool ok2 = false;
        int ansx = -1, ansy = -1;
        for(int t = 0; t < 100; t++ ){
            int tx = rnd() % n + 1, ty = rnd() % n + 1;
            if(tx == bx && ty == by){
                continue;
            }
            bool ok3 = true;
            for(int i = 0; i < n; i++ ){
                int dx = bx + x[i], dy = by + y[i];
                if(dx < 1 || dy < 1 || dx > n || dy > n){
                    continue;
                }
                int nx = tx - dx, ny = ty - dy;
                if(s.count(make_pair(nx, ny))){
                    ok3 = false;
                }
            }
            if(ok3){
                ok2 = true;
                ansx = tx, ansy = ty;
            }
        }
        if(ok2){
            cout << "tie " << ansx << " " << ansy << "\n";
        } else {
            cout << "Bob wins\n";
        }
    }
    return 0;
}