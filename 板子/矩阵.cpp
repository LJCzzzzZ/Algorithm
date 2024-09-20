struct matrix{
    int n, m;
    vector<vector<ll>> mat;
    matrix(int n, int m) : n(n), m(m) {
        vector<ll> tmp(m);
        for(int i = 0; i < n; i++ ){
            mat.push_back(tmp);
        }
        set(0);
    }

    matrix operator *(const matrix &a)const{
        matrix res(n, a.m);
        for(int i = 0; i < n; i++ ){
            for(int j = 0; j < a.m; j++ ){
                for(int k = 0; k < m; k++ ){
                    res.mat[i][j] += (mat[i][k] * a.mat[k][j]);
                    res.mat[i][j] %= mod;
                }
            }
        }
        return res;
    }

    void set(int k = 0){    
        for(int i = 0; i < n; i++ ){
            for(int j = 0; j < m; j++ ){
                if(i == j) mat[i][j] = k;
                else mat[i][j] = 0;
            }
        }
    }
    matrix ksm(matrix& a, ll k){
        matrix res(a.n, a.m);
        res.set(1);
        while(k){
            if(k & 1) res = res * a;
            a = a * a;
            k >>= 1;
        }
        return res;
    }
};