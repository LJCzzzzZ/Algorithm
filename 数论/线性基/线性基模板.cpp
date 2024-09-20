#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define fi first
#define se second

int main() 
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<ull> B;
    auto insert = [&](ull x){
        for(auto b : B){ // 是否可以异或出x
            x = min(x, b ^ x);
        }
        for(auto &b : B){ // 集合中元素取最小
            b = min(b, b ^ x);
        }
        if(x > 0){ // 需要新元素
            B.push_back(x);
        }
    };
    auto k_num = [&](ll k){
        sort(B.begin(), B.end());
        ull ans = 0;
        if(B.size() < n){ // 比原集合数量少, 可以异或出0
            k--;
        }
        // 有 x 个互不干扰的元素, 则有 2^x 种数能异或出来, 第k大就是二进制下的第k大
        for(auto b : B){ // 二进制分解出需要哪几位, 
            if(k & 1){
                ans ^= b;
            }
            k >>= 1;
        }
        if(k == 0) return ans;
        return -1; // 如果要求的是第一小, 且能异或出0
    };
    vector<ull> a(n);
    for(int i = 0; i < n; i++ ){
        cin >> a[i];
        insert(a[i]);
    }

    ull ans = 0;
    for(auto b : B){
        ans ^= b;
    }
    cout << ans << "\n";
    return 0;
}