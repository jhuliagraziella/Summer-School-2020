// https://codeforces.com/contest/830/problem/C

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int v[102];

// O excedente de um bambu olhando de d em d dias vai ser o menor múltiplo de d
// maior que o tamanho ideal do bambu, menos o tamanho ideal do bambu.
// excedente = d * floor(tam_ideal / d) - tam_ideal.
// A soma dos excedentes dos bambus tem que ser <= k, queremos maximizar d.
// SOMA(d * floor(a_i / d) - a_i) <= k
// SOMA(d * floor(a_i / d)) - SOMA(a_i) <= k
// d * SOMA(floor(a_i)/d) <= k + SOMA(a_i)
// d <= (k + SOMA(a_i)) / SOMA(floor(a_i)/d), como d é inteiro:
// d = floor ((k + SOMA(a_i)) / SOMA(floor(a_i)/d))
// Calcula k + SOMA(a_i) = S e itera em todos os valores de d = floor(S/i).
int main() {
  cin.tie(0);
  ios::sync_with_stdio(false);

  int n; ll k;
  cin >> n >> k;

  for (int i = 0; i < n; i++){
    cin >> v[i];
    k += v[i];
  }

  ll ans = 1LL;
  for (ll i = 1; i <= k; i++){
    ll d = k / i;
    ll cont = 0;
    for (int j = 0; j < n; j++)
      cont += d * ((v[j] + d - 1) / d);  // floor(a / b) = (a + b - 1) / b

    if (cont <= k) ans = max(ans, d);

    // Calcula o maior número N tal que floor(k/N) == floor(k/i) e faz i = N.
    i = k / (k/i);
  }

  cout << ans << endl;
}
