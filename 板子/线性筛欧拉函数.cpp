const int N = 1e6 + 10;
bool isPrime[N];
int primes[N], cnt;
int phi[N];
void init(){
    phi[1] = 1;
    for(int i = 2; i < N; i++){
        if (!isPrime[i]) primes[++cnt] = i, phi[i] = i - 1;
        for(int j = 1; i * primes[j] < N; j++){
            isPrime[i * primes[j]] = 1;
            if (i % primes[j] == 0){
                phi[i * primes[j]] = phi[i] * primes[j];
                break;
            }
            phi[i * primes[j]] = phi[i] * (primes[j] - 1);
        }
    }
}