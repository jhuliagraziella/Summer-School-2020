// https://codeforces.com/contest/451/problem/E

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define MOD 1000000007

// calcula n^k mod m
ll modPow(ll n, ll k, ll mod) {
  if (!k) return 1LL;
  ll aux = modPow(n, k/2, mod);
  aux = (aux * aux) % mod;
  return (k & 1) ? (aux * n) % mod : aux;
}

// Inverso multiplicativo de n mod MOD
ll inverso(ll n, ll mod) {
  return modPow(n, mod-2, mod);
}

// Inverso multiplicativo de n!
ll inv_fat[21];
void pre() {
  inv_fat[0] = 1LL;
  for (int i = 1; i <= 20; i++) {
    // inverso multiplicativo de n! mod MOD:
    inv_fat[i] = (inv_fat[i - 1] * inverso(i, MOD)) % MOD;
  }
}

// Calcula fat(n) / fat(k)*fat(n-k)
// k eh no maximo 20 entao pode ser linear
ll C(ll n, ll k) {
  if (n < k) return 0LL;
  if (n == k) return 1LL;
  ll ans = inv_fat[k];
  for (ll i = n; i > n-k; i--) {
    ans = (ans * (i % MOD)) % MOD;
  }
  return ans;
}

int main() {
  cin.tie(0); ios::sync_with_stdio(false);

  int n;
  ll s;
  cin >> n >> s;

  ll f[20];
  for (int i = 0; i < n; i++) {
    cin >> f[i];
  }

  pre();

  ll ans = 0;
  for (int i = 0; i < (1 << n); i++) {
    ll restricao = 0;
    ll sinal = 1;
    for (int j = 0; j < n; j++) {
      if (i & (1 << j)) {  // se o bit j ta setado
        restricao += f[j] + 1;
        sinal *= -1;
      }
    }
    ans = (ans + sinal * C(s + n - 1 - restricao, n - 1)) % MOD;
  }

  cout << (ans + MOD) % MOD << endl;
}
