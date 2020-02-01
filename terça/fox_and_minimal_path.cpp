// https://codeforces.com/problemset/problem/388/B

#include <bits/stdc++.h>

using namespace std;

bool debug = true;
bool grafo[202][202];

#define maxn 30

// constroi maxn "diamantes" conectados no vertice 2:
//    2
//    |
//    3
//  /   \
// 4     5
//  \   /
//    6
//  /   \
// 7     8
//  \   /
//    9
//   ...
void constroi_diamantes() {
  grafo[2][3] = grafo[3][2] = 1;
  for (int i = 0; i <= maxn; i++) {
    int cima = (i + 1) * 3;
    int esq = cima + 1;
    int dir = cima + 2;
    int baixo = cima + 3;

    grafo[cima][esq] = grafo[esq][cima] = 1;
    grafo[cima][dir] = grafo[dir][cima] = 1;
    grafo[baixo][esq] = grafo[esq][baixo] = 1;
    grafo[baixo][dir] = grafo[dir][baixo] = 1;

    if (debug) {
      cout << "conecta " << cima << " <-> " << esq << endl;
      cout << "conecta " << cima << " <-> " << dir << endl;
      cout << "conecta " << baixo << " <-> " << esq << endl;
      cout << "conecta " << baixo << " <-> " << dir << endl;
    }
  }
}

// Constroi uma linha de vertices: 1 - 100 - 101 - 102 ...
// Pra conectar no diamante e manter o mesmo tamanho de percurso.
void constroi_corredor() {
  grafo[1][100] = grafo[100][1] = 1;
  for (int i = 100; i < 100 + 2 * maxn; i++) {
    grafo[i][i + 1] = grafo[i + 1][i] = 1;
    if (debug) cout << "conecta " << i << " <-> " << i+1 << endl;
  }
}

int main() {
  cin.tie(0);
  ios::sync_with_stdio(false);

  constroi_diamantes();
  constroi_corredor();

  int k;
  cin >> k;

  // Todos os percursos construídos terão esse tamanho.
  int tam_percurso = 2 * maxn + 1;

  // Escreve k em binário, e.g. 11 = 2^3 + 2^1 + 2^0
  for (int i = 0; i <= maxn; i++) {
    if ((1 << i) & k) { // bit i faz parte da representação de k em binário
      // vertice do diamante que gera 2^i caminhos
      int diamante = (i + 1) * 3;

      // distancia de 2 até diamante
      int dist_2_diamante = i * 2 + 1;

      // distancia de 1 até o vertice do corredor
      int dist_1_corredor = tam_percurso - dist_2_diamante;
      int corredor = dist_1_corredor + 99;

      // conecta corredor no diamante
      grafo[corredor][diamante] = grafo[diamante][corredor] = 1;

      if (debug) {
        cout << "conecta " << corredor << " <-> " << diamante << endl;
      }
    }
  }

  int n = 200;
  cout << n << endl;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      cout << (grafo[i][j] ? "Y" : "N");
    }
    cout << endl;
  }
}
