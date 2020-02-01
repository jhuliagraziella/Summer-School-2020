// Link pro contest: https://codeforces.com/gym/102428

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll soma(ll n) {  // retorna 1 + 2 + 3 + ... + n
  return (n * (n+1)) / 2;
}

int main() {
  cin.tie(0); ios::sync_with_stdio(false);

  string s;
  ll b;
  cin >> s >> b;

  // se so tem 1 fruta, qualquer corte q inclui essa fruta serve.
  int qtdd_frutas = 0;
  for (int i = 0; i < s.size(); i++) {
    qtdd_frutas += (s[i] == 'E');
  }

  if (qtdd_frutas == 1) {
    cout << soma(b) << endl;
    return 0;
  }

  s += s;  // simula vetor circular

  // pra cada eggfruit, quantos pedaços de tamanho <= b contem essa fruta e nao
  // contem a proxima eggfruit. O pedaco q contem essa e a proxima sera contado
  // quando calcularmos a resposta da proxima.
  ll ans = 0;
  int ultima_fruta = -1;
  for (ll i = 0; i < s.size(); i++) {
    if (s[i] == 'P') continue;

    if (ultima_fruta == -1) ultima_fruta = i;
    else if (ultima_fruta * 2 >= s.size()) break;
    else {  // quantos pedacoes contem a ultima eggfruit mas nao contem a atual
      ll esq = b - 1;
      ll dir = min(i - ultima_fruta - 1, b - 1);

      ll limite = min(esq, dir) + 1;
      ans += (b - limite) * limite + soma(limite);
      ultima_fruta = i;
    }
  }
  cout << ans << endl;
}
