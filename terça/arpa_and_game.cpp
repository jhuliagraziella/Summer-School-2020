// https://codeforces.com/contest/851/problem/E

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int debug = false;

unordered_map<int, int> primos;
unordered_map<int, int> dp;

string formata(int bitmask) {
  string ans = "";
  for (int i = bitmask; i != 0; i /= 2) {
    ans += '0' + ((bitmask & i) != 0);
  }
  return ans;
}

int grundy(int bitmask){
  if (bitmask <= 1) return 0;
  if (dp.count(bitmask)) return dp[bitmask];

  // Grundy de todos os estados que eu alcanço.
  set<int> out;

  // Pra um primo p, podemos escolhe dividir por p^1, p^2, ...
  // Ao dividir pelo bit j, todo bit >= j shifta j posições pra direita, o resto
  // fca normal.
  for (int j = 1; (1 << j) <= bitmask; j++) {
    int parte_normal = bitmask & ((1 << j) - 1);
    int parte_que_shifta = (bitmask ^ parte_normal);
    int parte_shiftada = (parte_que_shifta >> j);
    int bitmask_nova = parte_shiftada | parte_normal;

    if (debug) {
      cout << "dividindo " << formata(bitmask) << " por p^" << j << endl;
      cout << "parte normal: " << formata(parte_normal) << endl;
      cout << "parte que shifta: " << formata(parte_que_shifta) << endl;
      cout << "parte shiftada: " << formata(parte_shiftada) << endl;
      cout << "bitmask nova: " << formata(bitmask_nova) << endl << endl;
    }
    // Eu alcanço o estado bitmask_nova.
    out.insert(grundy(bitmask_nova));
  }

  // Primeiro valor de grundy que esse estado não alcança.
  int ans = 0;
  for (set<int>::iterator it = out.begin(); it != out.end(); it++) {
    if (*it != ans) break;
    ans++;
  }
  return dp[bitmask] = ans;
}

// Cada fator primo é independente. Fatora cada número da lista e cria uma
// bitmask para cada primo, setando o bit i se o fator primo^i divide algum
// número da entrada.
int main() {
  cin.tie(0);
  ios::sync_with_stdio(false);
  int n;
  cin >> n;

  for (int i = 0; i < n; i++) {
    int a;
    cin >> a;

    // Fatora o número a.
    // Como a < 10^9 dá pra fatorar direto, se a < 10^12 daria pra usar crivo
    // pq os primos > 10^6 sempre teriam no máximo um fator na entrada.
    for (ll j = 2; j * j <= a; j++) {
      int potencia = 0;
      while (a % j == 0) {
        a /= j;
        potencia++;
      }
      if (potencia != 0) {
        if (!primos.count(j)) primos[j] = 0;

        // Seta o bit potencia da bitmask primos[j].
        primos[j] |= (1 << potencia);
      }
    }
    // a é primo, seta o 1o bit da bitmask a.
    if (a != 1) primos[a] |= (1 << 1);
  }

  int ans = 0;
  for (unordered_map<int, int>::iterator it = primos.begin(); it != primos.end(); it++) {
    // Tira o xor dos grundy numbers da bitmask de cada primo.
    ans ^= grundy(it->second);
  }

  cout << (ans ? "Mojtaba" : "Arpa") << endl;
}
