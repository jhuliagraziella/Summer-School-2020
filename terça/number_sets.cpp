// https://open.kattis.com/problems/numbersetshard

#include <bits/stdc++.h>

using namespace std;

#define maxn 1000006

typedef long long ll;

bool composto[maxn];
vector<ll> primos;

ll ini, fim, menor;
int ans;

// Podemos achar só os primos ate 10^6, porque não tem como aparecer mais de um
// múltiplo de um número maior que 10^6 num intervalo [A, B] onde B-A < 10^6.
void sieve() {
  for (ll i = 2; i < maxn; i++) {
    if (!composto[i]) {
      primos.push_back(i);
      for (ll j = i*i; j < maxn; j += i) {
        composto[j] = true;
      }
    }
  }
}

int componente[maxn];

int pai(int a) {
  return a == componente[a] ? a : componente[a] = pai(componente[a]);
}

void join (int a, int b) {
  int pa = pai(a);
  int pb = pai(b);
  if (pa != pb) ans--;
  componente[pa] = componente[pb];
}

int main() {
  cin.tie(0);
  ios::sync_with_stdio(false);

  sieve();

  int c;
  cin >> c;

  for (int t = 1; t <= c; t++) {
    cin >> ini >> fim >> menor;
    for (ll j = ini; j <= fim; j++) {
      componente[j-ini] = j - ini;
    }
    ans = fim-ini+1;
    for (int j = 0; j < primos.size(); j++) {
      ll p = primos[j];
      if (p < menor || p > fim) continue;

      ll menor = (p > ini) ? p : (ini / p) * p;
      if (menor < ini) menor += p;

      // Achar os multiplos de primos[j] no intervalo [ini, fim] e juntar.
      for (ll k = menor + p; k <= fim; k += p) {
        join(menor - ini, k - ini);
      }
    }

    cout << "Case #" << t << ": " << ans << endl;
  }
}
