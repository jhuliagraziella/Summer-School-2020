// Link pro contest: https://codeforces.com/gym/102428
// Solucao em n^2 log n usando binary search the answer.

#include<bits/stdc++.h>

using namespace std;

int n, m;
int grid[1000][1000];

bool check(int v) {
  for (int j = 0; j < m; j++) {
    int cont = 0;  // quantos nessa coluna sao >= v
    for (int i = 0; i < n; i++) {
      if (grid[i][j] >= v) {
        cont++;
      } else {
        cont = 0;
      }

      if (cont >= v) return true;
    }
  }
  return false;
}

int main() {
  cin.tie(0); ios::sync_with_stdio(false);

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
  // vezes seguidas. Chuta um valor x e checka em O(n*m).
  int esq = 1;
  int dir = min(n, m);
  int mid = (esq + dir) / 2;
  while (esq <= dir) {
    if (check(mid)) {
      esq = mid + 1;
    } else {
      dir = mid - 1;
    }
    mid = (esq + dir) / 2;
  }
  cout << mid * mid << endl;
}
