// Link pro contest: https://codeforces.com/gym/102428
// Solucao em n^2 procurando maior retangulo no histograma.

#include<bits/stdc++.h>

using namespace std;

int maior_quadrado(const vector<int>& h) {
  stack<int> p;  // p tem os indices de h em ordem crescente de altura.

  int maior_lado = 0;
  for (int i = 0; i < h.size(); i++) {
    // tira todos os caras menores que h[i] e calcula resp pra eles.
    while (!p.empty() && h[i] < h[p.top()]) {
      int atual = p.top(); p.pop();
      int anterior = p.empty() ? -1 : p.top();

      // tem um retangulo de altura = h[atual] e largura = i - 1 - anterior.
      int lado_quadrado = min(h[atual], i - 1 - anterior);
      maior_lado = max(maior_lado, lado_quadrado);
    }
    p.push(i);
  }

  // tira todos os caras e calcula a resp pra eles.
  while (!p.empty()) {
    int atual = p.top(); p.pop();
    int anterior = p.empty() ? -1 : p.top();

    // tem um retangulo de altura = h[atual] e largura = h.size() - 1 - anterior.
    int lado_quadrado = min(h[atual], int(h.size()) - 1 - anterior);
    maior_lado = max(maior_lado, lado_quadrado);
  }
  return maior_lado * maior_lado;
}

int main() {
  cin.tie(0); ios::sync_with_stdio(false);

  int n, m;
  int grid[1000][1000];

  cin >> n >> m;

  // Pra cada linha da matriz, cria uma linha de inteiros que mostra quantos
  // terrenos consecutivos sao iguais a esse, e.g. BGGGBB => 112312 e BBB => 123
  for (int i = 0; i < n; i++) {
    string s;
    cin >> s;
    grid[i][0] = 1;
    for (int j = 1; j < m; j++) {
      grid[i][j] = (s[j] != s[j-1]) ? 1 : grid[i][j-1] + 1;
    }
  }

  // Pra cada coluna da matriz, achar o maior valor x que repita pelo menos x
  // vezes seguidas. Considerando cada coluna como um histograma, isso
  // corresponde a achar o maior quadrado no histograma. Complexidade O(n*m);
  int ans = 0;
  vector<int> histograma;
  for (int j = 0; j < m; j++) {
    histograma.clear();
    for (int i = 0; i < n; i++) {
      histograma.push_back(grid[i][j]);
    }
    ans = max(ans, maior_quadrado(histograma));
  }
  cout << ans << endl;
}

