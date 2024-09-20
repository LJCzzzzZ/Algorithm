#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define se second

int main() 
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++ ){
        cin >> a[i];
    }

    vector<tuple<int, int, int>> v(n);
    ll ans = 0;
    int x = 0;
    for(int s = 0; s < 30; s++ ){
        for(int i = 0; i < n; i++ ){
            v[i] = make_tuple(a[i] >> (s + 1), i, (a[i] >> s) & 1);
        }
        sort(v.begin(), v.end());

        ll inv0 = 0;
        ll inv1 = 0;
        int beg = 0;
        while(beg < n){
            int end = beg;
            while(end + 1 <  n && get<0>(v[end + 1]) == get<0>(v[end])){
                end++;
            }   
            // 只算当前这位对逆序对的贡献, 要求高位相同, 高位贡献会遍历到时再算
            int k0 = 0, k1 = 0;
            for(int i = beg; i <= end; i++ ){
                int bit = get<2>(v[i]);
                if(bit == 0){
                    inv0 += k1; // 原本的贡献
                    k0++;
                } else {
                    inv1 += k0; // 异或后的贡献
                    k1++;
                }
            }
            beg = end + 1;
        }

        if(inv1 >= inv0){ // 异或后的贡献更大
            ans += inv0;
        } else {
            ans += inv1;
            x |= (1 << s);
        }
    }

    cout << ans << " " << x << "\n";
    return 0;
}