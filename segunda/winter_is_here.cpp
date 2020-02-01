// https://codeforces.com/problemset/problem/839/D

#include <bits/stdc++.h>

#define mod 1000000007

using namespace std;

typedef long long ll;

int c[1000005];  // c[i] = quantos números da entrada dividem i
ll ans[1000005];  // ans[i] = soma das forças dos clãs que tem mdc = i

ll modPow(int n, int k) {
  if (k < 0) return 0LL;
  if (!k) return 1LL;

  ll aux = modPow(n, k/2);
  aux = (aux*aux) % mod;

  return k % 2 ? (aux * n) % mod : aux;
}

int main() {
  cin.tie(0); ios::sync_with_stdio(false);
  int n;
  cin >> n;

  int maior = 0;
  for (int i = 0; i < n; i++){
    int a;
    cin >> a;
    maior = max(maior, a);

    for (int i = 2; i <= sqrt(a); i++){
      if (a % i != 0) continue;
      c[i]++;
      if (i != a / i) c[a / i]++;
    }
    c[a]++;
  }

  ll ans_final = 0;
  for (int i = maior; i >= 2; i--) {
    ans[i] = (c[i] * modPow(2, c[i] - 1)) % mod;
    // tira o que já foi contado pelos outros múltiplos de i
    for (int j = 2 * i; j <= maior; j += i) {
      ans[i] -= ans[j];
      if (ans[i] < 0) ans[i] += mod;
    }

    ans_final = (ans_final + ((i * ans[i]) % mod)) % mod;
  }
  cout << ans_final << endl;
}
