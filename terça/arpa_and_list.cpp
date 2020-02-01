// https://codeforces.com/contest/851/problem/D

#include <bits/stdc++.h>

using namespace std;

#define maxn 1000006
typedef long long ll;

bool debug = false;

bool composto[maxn];
vector<ll> primos;
void sieve() {
  for (ll i = 2; i < maxn; i++) {
    if (composto[i]) continue;
    primos.push_back(i);
    for (ll j = i * i; j < maxn; j += i) {
      composto[j] = 1;
    }
  }
}

ll quant[2*maxn];  // quant[i] = quantidade dos números <= i;
ll sum[2*maxn];  // sum[i] = soma dos números <= i;

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  sieve();

  ll n, x, y;
  cin >> n >> x >> y;

  ll ans = n * x;  // custo de excluir todos
  while (n--) {
    int a;
    cin >> a;
    sum[a] += a;
    quant[a]++;
  }
  for (int i = 1; i < 2 * maxn; i++){
    sum[i] += sum[i-1];
    quant[i] += quant[i-1];
  }

  // Calcula o custo de transformar os números da lista em múltiplos de primos[i].
  // Itera nos múltiplos de primos[i] e vê se fica mais barato somar os
  // números da lista até alcançar esse múltiplo ou deletar o número da lista.
  for (int i = 0; i < primos.size() ;i++) {
    ll atu = 0;

    // Calcula pros números do intervalo (p - primos[i], p]
    for (int p = primos[i]; p < 2 * maxn; p += primos[i]) {
      // limite é a quantidade de vezes que vale a pena somar até alcançar o
      // valor p, todos os números que precisa somar mais do que limite vezes
      // vale mais a pena excluir do que somar.
      int limite = max(min((x + y - 1) / y, primos[i]), 1LL);

      // Vale a pena excluir os números no range (inicio_intervalo, fim_intervalo - limite]
      // Exclui os números do intervalo (p - primos[i], p - limite] com custo x
      ll qtdd_excluida = quant[p-limite] - quant[p-primos[i]];
      atu += qtdd_excluida * x;  // custo pra excluir


      // Vale a pena somar de 1 em 1 os números no range (fim_intervalo - limite, limite]
      // Soma de 1 em 1 até chegar em primos[i] nos números do intervalo (p - limite, p]
      // com custo y * unidades somadas.
      ll unidades_antes = sum[p] - sum[p - limite];
      ll unidades_depois = (quant[p] - quant[p - limite]) * p;
      ll qtdd_unidades_somadas = unidades_depois - unidades_antes;
      atu += qtdd_unidades_somadas * y;  // custo pra somar

      if (debug) {
        cout << "Calculo pro range [" << p-primos[i]+1 << ", " << p << "]" << endl;
        cout << "- limite: " << limite << endl;
        cout << "Excluiu no range [" << p-primos[i]+1 << ", " << p-limite << "]" << endl;
        cout << "- qtdd numeros excluidos: " << qtdd_excluida << endl;
        cout << "- custo excluir: " << qtdd_excluida * x << endl;
        cout << "Somou no range [" << p-limite+1 << ", " << p << "]" << endl;
        cout << "- unidades antes: " << unidades_antes << endl;
        cout << "- unidades depois: " << unidades_depois << endl;
        cout << "- qtdd unidades somadas: " << qtdd_unidades_somadas << endl;
        cout << "- custo somar: " << qtdd_unidades_somadas * y << endl;
        cout << "Custo atual " << atu << endl << endl;
      }
    }

    ans = min(ans, atu);
  }
  cout << ans << endl;
}
