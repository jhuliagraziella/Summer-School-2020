// https://codeforces.com/problemset/problem/1028/C

#include <bits/stdc++.h>

using namespace std;

typedef struct ret {
  int x1, x2, y1, y2;
} Ret;
Ret retangulos[133000];
Ret prefixo[133000];
Ret sufixo[133000];

Ret intersecao(Ret a, Ret b) {
  Ret c;
  c.x1 = max(a.x1, b.x1);
  c.x2 = min(a.x2, b.x2);
  c.y1 = max(a.y1, b.y1);
  c.y2 = min(a.y2, b.y2);
  return c;
}

bool empty(Ret a) {
  return a.x1 > a.x2 || a.y1 > a.y2;
}

int main() {
  cin.tie(0);
  ios::sync_with_stdio(false);

  int n;
  cin >> n;

  for (int i = 0; i < n; i++) {
    cin >> retangulos[i].x1 >> retangulos[i].y1
        >> retangulos[i].x2 >> retangulos[i].y2;
  }

  prefixo[0] = retangulos[0];
  for (int i = 1; i < n; i++) {
    prefixo[i] = intersecao(prefixo[i-1], retangulos[i]);
  }

  sufixo[n-1] = retangulos[n-1];
  for (int i = n-2; i >= 0; i--) {
    sufixo[i] = intersecao(retangulos[i], sufixo[i+1]);
  }

  // Se todos os retangulos tirando um tiverem interseção, essa é uma possível
  // resposta.
  Ret ans;
  if (!empty(sufixo[1])) {
    // Se a interseção de todo mundo menos o retângulo 0 é não vazia.
    ans = sufixo[1];
  } else if (!empty(prefixo[n-2])) {
    // Se a interseção de todo mundo menos o retângulo n-1 é não vazia.
    ans = prefixo[n-2];
  } else {
    for (int i = 1; i < n - 1; i++) {
      // prefixo[i-1] tem a interseção de todos antes do i;
      // sufixo[i+1] tem a interseção de todos depois do i;
      // intersecao(prefixo[i-1], sufixo[i+1]) tem a interseçao de todos menos o i.
      Ret intersecao_sem_i = intersecao(prefixo[i-1], sufixo[i+1]);
      if (!empty(intersecao_sem_i)) {
        ans = intersecao_sem_i;
        break;
      }
    }
  }
  cout << ans.x1 << " " << ans.y1 << endl;
}
