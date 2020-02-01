// Link pro contest: https://codeforces.com/gym/102428

#include <bits/stdc++.h>

#define mod 1000000007

using namespace std;

typedef long long ll;

ll dp[5003][5003];
bool vis[5003][5003];  // mesmo cuidado que na questão I.
ll f(ll chao, ll bloquinhos) {
  if (bloquinhos == 0) return 1;
  if (bloquinhos < 0 || chao <= 0) return 0;
  if (vis[chao][bloquinhos]) return dp[chao][bloquinhos];

  vis[chao][bloquinhos] = true;

  // A partir do estado (pilhas 123, b bloquinhos), onde cada numero (1,2 e 3)
  // representa uma pilha diferente, podemos chegar em:
  // pilhas(123, b-3) -> preencheu o chao com bloquinhos
  // pilhas(12, b) -> pilha da direita vazia
  // pilhas(23, b) -> pilha da esquerda vazia
  // Os estados (12,b) e (23, b) alcançam o estado(2, b), então tem que subtrair
  // ele pra não ficar duplicado.

  ll preenche_chao = f(chao, bloquinhos - chao);
  ll um_lado_vazio = f(chao - 1, bloquinhos);
  ll dois_lados_vazios = f(chao - 2, bloquinhos);

  dp[chao][bloquinhos] = preenche_chao + 2 * um_lado_vazio - dois_lados_vazios;
  dp[chao][bloquinhos] %= mod;
  dp[chao][bloquinhos] += mod;
  dp[chao][bloquinhos] %= mod;

  return dp[chao][bloquinhos];
}

int main() {
  cin.tie(0); ios::sync_with_stdio(false);

  int s, b;
  cin >> s >> b;
  cout << f(s, b-s) << endl;
}
