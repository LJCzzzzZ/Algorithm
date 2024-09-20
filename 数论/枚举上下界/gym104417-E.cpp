#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define se second
#define mp make_pair
#define pii pair<int, int>
inline __int128 read(){
    __int128 x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}
 
inline void write(__int128 x){
    if(x<0){
        putchar('-');
        x=-x;
    }
    if(x>9)
        write(x/10);
    putchar(x%10+'0');
}
void solve(){
    // 题意: 给定一个数n, 有两种操作: (1). 花费A, 将n = n * k + x(x任意, 0 <= x < k) (2). 花费B, n = n / k下取整
    // 题解: 操作顺序肯定是先除后乘, 因为不可能把加上的又下取整去掉
    // (1). 特判 k = 1
    // (2). n -> 0 需要logn次 先枚举需要除多少次, 然后乘, 假设乘x次 那么x次后n的取值范围为 [n * k ^ x, (n + 1) * k ^ x];
    //      显然x ~ y次之间的区间连续, 那么只要 L >= m那么必定会出现使得某个m的倍数出现在区间之间, 那么枚举乘的次数为logm
    //      那么显然有 O(logn * logm)的做法
    // 右边界R证明
    // n * k
    // n * k ^ 1 + x1
    // n * k ^ 2 + x1 * k ^ 1 + x2
    // n * k ^ 3 + x1 * k ^ 2 + x2 * k ^ 1 + x3
    // n * k ^ 4 + x1 * k ^ 3 + x2 * k ^ 2 + x3 * k ^ 1 + x4
    // x 全取 k - 1  ->  n * k ^ p + (k - 1) * (k ^ (p -1) + k ^ (p - 2)....) = n * k^p + k^p + ... + k
    //                                                                                        - k^(p-1)... -1 = n*k^p + k^p - 1 = (n + 1) * k^p - 1 
    __int128 n, k, m, a, b;
    n = read();
    k = read();
    m = read();
    a = read();
    b = read();
    if(k == 1){
        if(n % m == 0){
            cout << "0\n";
        } else {
            cout << "-1\n";
        }
        return;
    }
    __int128 ans = 2e18, B = 0;
    while(n > 0){
        __int128 L = n, R = n, A = 0, base = 1;
        int cnt = 0;
        while(true){
            if(R >= m && (L + m - 1) / m * m <= R || n % m == 0){
                ans = min(ans, A + B);
                break;
            }
            base = base * k;
            A += a;    
            L = n * base;
            R = base * (n + 1) - 1; 
            cnt += 1;
            if(cnt > 60){
                break;
            }
        }
        n /= k;
        B += b;
    }       
    ans = min(ans, B);
    write(ans);
    printf("\n");
}
int main() 
{
    int T;
    cin >> T;
    while(T--){
        solve();
    }
    return 0;
}