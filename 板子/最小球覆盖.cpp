#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define se second
#define mp make_pair
#define pii pair<int, int>

struct Point{
    double x, y, z;
};
int main() 
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    srand(1e9 + 7); // 随机种子
    int n;
    cin >> n;
    vector<Point> p(n);
    double sumx = 0, sumy = 0, sumz = 0;
    for(int i = 0; i < n; i++ ){
        cin >> p[i].x >> p[i].y >> p[i].z;
        sumx += p[i].x;
        sumy += p[i].y;
        sumz += p[i].z;
    }
    // 假设的中点坐标
    double mid_x = 1.0 * sumx / n;
    double mid_y = 1.0 * sumy / n;
    double mid_z = 1.0 * sumz / n;

    auto calc = [&](int i, double x, double y, double z){
        return sqrt((p[i].x - x) * (p[i].x - x) + (p[i].y - y) * (p[i].y - y) + (p[i].z - z) * (p[i].z - z));
    };

    double ans = 2e9;
    auto SA = [&]() -> void{
        double T = 3000;
        double T_min = 1e-12;
        double r = 0.996; // 参数
        double now_x = mid_x, now_y = mid_y, now_z = mid_z;
        while(T > T_min){
            double new_x = now_x + (rand() * 2 - RAND_MAX) * T;
            double new_y = now_y + (rand() * 2 - RAND_MAX) * T;
            double new_z = now_z + (rand() * 2 - RAND_MAX) * T;
            double res = 0;
            for(int i = 0; i < n; i++ ){
                res = max(res, calc(i, new_x, new_y, new_z));
            } // 算出球半径
            double delta = res - ans;
            if(delta < 0){ // 直接接受答案
                ans = res;
                mid_x = now_x = new_x;
                mid_y = now_y = new_y;
                mid_z = now_z = new_z;
            } else if(exp(-delta / T) * RAND_MAX > rand()){ // 概率大于随机概率也接受 
                now_x = new_x;
                now_y = new_y;
                now_z = new_z;
            } // 转移方程
            T = T * r;
        }
    };
    /*for(int i = 0; i < 5; i++ ){
        SA();
    }*/
    double time_limit = 2.8;
    while((double)clock() / CLOCKS_PER_SEC < time_limit){
        SA();
    }
    cout << fixed << setprecision(12) << ans << "\n";
    return 0;
}