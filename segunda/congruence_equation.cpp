// https://codeforces.com/contest/919/problem/E

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll mod_pow(ll n, ll k, ll mod) {
  if (!k) return 1LL;
  ll ans = mod_pow(n, k/2, mod);
  ans = (ans * ans) % mod;
  return k & 1 ? (ans * n) % mod : ans;
}

ll inverso(ll n, ll mod) {
  return mod_pow(n, mod-2, mod);
}

int main () {
  cin.tie(0); ios::sync_with_stdio(false);

  ll a, b, p, max_x;
  cin >> a >> b >> p >> max_x;

  // n * a^n = b (mod p)
  // n * a^(n - (p-1)) * a^(p-1) = b (mod p), como a^(p-1) = 1 (mod p):
  // n * a^(n (mod p-1)) = b (mod p)
  // Considere x = n (mod p-1)
  // n * a^x = b (mod p)
  // n = b * inverso(a^x) (mod p)

  // Usar o Teorema Chinês do Resto pra resolver esse sistema:
  // n = x (mod p-1)
  // n = b * inverso(a^x) (mod p)
  ll ans = 0LL;
  ll a_pow_x1 = 1LL;
  for (int x1 = 1; x1 < p; x1++) {
    a_pow_x1 = (a_pow_x1 * a) % p;
    ll x2 = (b * inverso(a_pow_x1, p)) % p;
    // n = x1 (mod p-1)
    // n = x2 (mod p)
    // n1 * p = 1 (mod p-1) => n1 = 1 (mod p-1);
    // n2 * (p-1) = 1 (mod p) => n2 = 1 * inverso(p-1) (mod p)

    ll n1 = 1;
    ll n2 = inverso(p-1, p);

    ll P = p * (p - 1);
    ll n = (x1 * n1 * p + x2 * n2 * (p-1)) % P;

    // as solucoes sao da forma k*P + n.
    if (max_x < n) continue;
    ans += 1 + (max_x-n) / P;
  }
  cout << ans << endl;
}
