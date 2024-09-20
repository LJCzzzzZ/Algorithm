#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define se second
#define mp make_pair
#define pii pair<int, int>
int a[101][101][101];
int main() 
{
    // 题意: 在 100 * 100 * 100的三维空间里给出n个不相交的长方体的两个对顶角坐标, 问每个长方体与多少个其他长方体相交
    // 题解: 题目问相交, 就考虑长方体表面的点附近的点的情况
    // 对每个长方体在三维数组中标记 [(x, y, z)L, (x, y, z)R) -> i, 当一个点相邻六个方向有点与自己编号不同, 那么这两个长方体相交  
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    for(int i = 0; i < n; i++ ){
        int a1, b1, c1, a2, b2 ,c2;
        cin >> a1 >> b1 >> c1 >> a2 >> b2 >> c2;
        for(int j = a1; j < a2; j++ ){
            for(int k = b1; k < b2; k++ ){
                for(int z = c1; z < c2; z++ ){
                    a[j][k][z] = i + 1;
                }
            }
        }
    }

    vector<set<int>> st(n + 1);
    vector<tuple<int, int, int>> moves{{0, 0, 1}, {0, 0, -1}, {0, 1, 0}, {0, -1, 0}, {1, 0, 0}, {-1, 0, 0}};
    for(int i = 0; i <= 100; i++ ){
        for(int j = 0; j <= 100; j++ ){
            for(int k = 0; k <= 100; k++ ){
                if(a[i][j][k]){
                    for(auto [dx, dy, dz] : moves){
                        int x = i + dx, y = j + dy, z = k + dz;
                        if(x < 0 || y < 0 || z < 0 || x > 100 || y > 100 || z > 100 || !a[x][y][z]){
                            continue;
                        }
                        if(a[x][y][z] != a[i][j][k]){
                            st[a[i][j][k]].insert(a[x][y][z]);
                        }
                    }
                }
            }
        }
    }
    for(int i = 1; i <= n; i++ ){
        cout << (int)st[i].size() << "\n";
    }
    return 0;
}