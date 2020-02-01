// https://codeforces.com/problemset/problem/603/C

#include <bits/stdc++.h>

using namespace std;

// Calcula grundy number pra k par.
// g(0) = 0
// g(1) = 1 -> alcança g(0) = 0;
// g(2) = 2 -> alcança g(0) = 0 e g(1) = 1;
// g(3) = 0 -> alcança g(2) = 2, não alcança nenhum grundy = 0;
// g(4) = 1 -> alcança g(3) = 0;
// g(5) = 0 -> alcança g(4) = 1, não alcança nenhum grundy = 0;
// g(6) = 1 -> alcança g(5) = 0;
// ...
// A partir de 4 começa a ciclar: todo ímpar tem grundy = 0 porque alcança o
// número par anterior que tem grundy = 1; e todo par tem grundy = 1 porque
// alcança o número ímpar anterior que tem grundy = 0.
int g_par(int n) {
  if (n <= 2) return n;
  return n % 2 == 0;
}

// Calcula grundy number pra k ímpar.
// g(0) = 0
// g(1) = 1 -> alcança g(0) = 0;
// g(2) = 0 -> alcança g(1) = 1, não alcança nenhum grundy = 0;
// g(3) = 1 -> alcança g(2) = 0;
// g(4) = 2 -> alcança g(3) = 1 e g(2) = 0;
// g(5) = 0 -> alcança g(4) = 2, não alcança nenhum grundy = 0
// g(6) = 1 -> alcança g(5) = 0;
// ...
// A partir de 5 começa a ciclar de forma parecida com o caso de k par:
// todo ímpar tem grundy = 0 porque alcança o número par anterior que tem
// grundy != 0; e todo par tem grundy != 0 porque alcança o número ímpar
// anterior que tem grundy = 0. A diferença é que só sabemos que grundy(par) é
// diferente de zero, não sabemos exatamente seu valor.
// Mas cada número par n só alcança o número ímpar anterior (n-1) e o
// número n/2, então dá pra computar isso com custo log n.
int g_impar(int n) {
  if (n == 4) return 2;
  if (n <= 3) return n % 2;
  if (n % 2 == 1) return 0;
  return g_impar(n / 2) == 1 ? 2 : 1;
}

int main() {
  int n, k;
  cin >> n >> k;
  int ans = 0;
  while (n--) {
    int p;
    cin >> p;

    if (k % 2 == 0)
      ans ^= g_par(p);
    else
      ans ^= g_impar(p);
  }
  cout << (ans != 0 ? "Kevin" : "Nicky") << endl;
}
