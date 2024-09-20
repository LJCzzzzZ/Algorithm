// for(int i = st; i <= ed; i++ ) ans += num / i;
int block(int st, int ed, int num){
    int ans = 0;
    ed = min(ed, num);
    for(int L = st, R; L <= ed; L = R + 1){
        R = min(ed, num / (num / L)); // 向下取整
        // R = min(ed, (num - 1) / ((num - 1) / L)) 向上取整
        ans += (R - L + 1) * (num / L);
    }
    return ans;
}