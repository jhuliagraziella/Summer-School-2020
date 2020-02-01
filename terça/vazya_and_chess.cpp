// https://codeforces.com/problemset/problem/493/D

#include <bits/stdc++.h>

using namespace std;

// Se n == 2, W ganha andando pro quadrado (1, 2) e comendo a outra rainha.
// Se n == 3, W perde, B imita todas as jogadas em relação à coluna do meio:
// Rodada 1:
// W*B                                            _*B               _*_
// *** => W só pode mexer pra baixo sem perder => W** => B imita => W*B
// ***                                            ***               ***
//
// Rodada 2:
// _*_                                            _*_               _*_
// W*B => W só pode mexer pra baixo sem perder => _*B => B imita => _*_
// ***                                            W**               W*B
//
// Rodada 3:
// _*_
// _*_ => W vai pra direita ou pra diagonal, e B ganha.
// W*B
//
// Observe que W perde qualquer jogo de tamanho Nx3.
//
// Se n == 4, W ganha andando pro quadrado (1, 2), transformando o jogo num
// tauleiro 4x3 onde B é o primeiro a jogar.
// Se n é par, W ganha indo pra (1,2); senão perde com o B imitando suas jogadas.

int main() {
  int n;
  cin >> n;
  cout << (n & 1 ? "black" : "white\n1 2") << endl;
}
