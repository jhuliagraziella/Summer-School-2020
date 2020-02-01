// https://codeforces.com/contest/148/problem/D

#include <bits/stdc++.h>

using namespace std;

bool vis[2][1003][1003];
double dp[2][1003][1003];

int princesa = 0;
int dragao = 1;

// f(i, w, b) calcula a probabilidade da PRINCESA ganhar nesse estado.
// i = jogador, w = qtdd de ratos brancos, b = qtdd de ratos pretos.
double f(int i, int w, int b){
  if (w == 0) return 0;  // só tem rato preto ou não tem nenhum rato
  if (b == 0) return i == princesa;  // só tem rato branco
  if (w < 0 || b < 0) return 0;  // pos inválida
  if (vis[i][w][b]) return dp[i][w][b];

  vis[i][w][b] = 1;
  if (i == princesa){
    double p = w / double(w + b);  // probabilidade de tirar um rato branco.

    // princesa ganha se tirar um branco OU ganhar o subjogo (dragao, w, b-1).
    return dp[i][w][b] = p * 1 + (1 - p) * f(!i, w, b-1);
  }
  else { // vez do dragão
    double p = w / double(w + b); // probabilidade de retirar um branco.

    // Se o dragão tirar um branco o jogo já termina (princesa perde.
    // Se ele tirar um preto algum rato (branco ou preto) pula do saco depois.
    double pb = w / double(w + b - 1); // probabilidade de um rato branco pular
    double pp = 1 - pb; // probabilidade de um rato preto pular

    // Princesa ganha se o dragão tirar um preto e o jogo continuar. O jogo
    // vai pro estado (princesa, w-1, b-1) se pular um branco ou pro estado
    // (princesa, w, b-2) se pular um preto.
    return dp[i][w][b] = (1 - p) * (pb * f(!i, w-1, b-1) + pp * f(!i, w, b-2));
  }
}

int main() {
  cin.tie(0);
  ios::sync_with_stdio(false);
  int w, b;
  cin >> w >> b;
  printf("%.15lf\n", f(0, w, b));
}
