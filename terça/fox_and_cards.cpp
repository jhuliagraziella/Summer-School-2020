// https://codeforces.com/problemset/problem/388/C

#include <bits/stdc++.h>

using namespace std;

// As estratégias se equilibram.
// Se a pilha tem tamanho par:
// O jogador Cima sempre vai pegar as cartas da metade de cima, e o de Baixo
// sempre vai pegar as cartas da metade de baixo.
// Se uma carta "vale a pena", o jogador vai se esforçar pra pegar ela, e quem
// estiver mais perto vai conseguir pegar primeiro. Se uma carta não vale a pena,
// o jogador mais longe dela consegue se manter longe até obrigar o outro jogador
// a pegar ela.
// Se a pilha tem tamanho ímpar: é a mesma coisa, mas o jogador que joga primeiro
// vai conseguir pegar a maior carta que esteja no meio de uma pilha, e depois
// é como se o jogo recomeçasse com as pilhas restantes e invertendo quem começa,
// então o outro jogador consegue pegar a 2a maior carta que esteja no meio de
// uma pilha e assim por diante.
int main() {
  cin.tie(0);
  ios::sync_with_stdio(false);

  int n;
  cin >> n;

  int soma_cima = 0;
  int soma_baixo = 0;
  vector<int> cartas_no_meio;
  while (n--) {
    int s;
    cin >> s;

    for (int i = 0; i < s; i++) {
      int carta;
      cin >> carta;

      if (s % 2 == 1 && i == (s - 1) / 2) {  // carta no meio da pilha
        cartas_no_meio.push_back(carta);
      } else if (i < s / 2) {  // carta na metade de cima da pilha
        soma_cima += carta;
      } else {  // carta na metade de baixo da pilha
        soma_baixo += carta;
      }
    }
  }
  sort(cartas_no_meio.begin(), cartas_no_meio.end());

  int vez_cima = 1;
  for (int i = cartas_no_meio.size() - 1; i >= 0; i--) {
    if (vez_cima) soma_cima += cartas_no_meio[i];
    else soma_baixo += cartas_no_meio[i];
    vez_cima = !vez_cima;
  }
  cout << soma_cima << " " << soma_baixo << endl;
}
