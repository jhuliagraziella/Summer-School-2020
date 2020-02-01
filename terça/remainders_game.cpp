// https://codeforces.com/problemset/problem/687/B

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll gcd(ll a, ll b) {
  return __gcd(a, b);
  return b == 0 ? a : gcd(b, a % b);
}

ll lcm(ll a, ll b) {
  return (a * b) / gcd(a, b);
}

int main() {
  cin.tie(0);
  ios::sync_with_stdio(false);
  ll n, k;
  cin >> n >> k;
  ll mmc = 1;
  while (n--) {
    ll a;
    cin >> a;

    // Calcula o lcm mas tira o gcd com k a cada passo pra não dar overflow.
    // Tirar o gcd com k só vai jogar fora os fatores que forem "inúteis" pra k.
    mmc = lcm(a, mmc);
    mmc = gcd(mmc, k);
  }
  cout << (gcd(mmc, k) == k ? "Yes" : "No") << endl;
}
