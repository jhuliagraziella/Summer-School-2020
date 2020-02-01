// Link pro contest: https://codeforces.com/gym/102428

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<ll> multiplica_polinomios(const vector<ll>& p, const vector<ll>& q) {
  vector<ll> ans;
  for (int i = 0; i < p.size(); i++) {
    for (int j = 0; j < q.size(); j++) {
      ll valor = p[i] * q[j];
      int grau = i + j;

      while (ans.size() <= grau) ans.push_back(0);

      ans[grau] += valor;
    }
  }
  return ans;
}

int main() {
  cin.tie(0); ios::sync_with_stdio(false);

  string s;
  cin >> s;

  vector<ll> p = {1};

  // Como as raízes são inteiras, sempre que a entrada muda de H->A ou A->H o
  // número ímpar que fica entre essas entradas é uma raiz.
  for (int i = 1; i < s.size(); i++) {
    if (s[i] == s[i-1]) continue;

    ll raiz = i * 2 + 1;
    vector<ll> q = {-raiz, 1};  // (x - raiz)

    // O polinomio da resposta é (x - raiz_1) * (x - raiz_2) * ...
    p = multiplica_polinomios(p, q);
  }

  cout << p.size() - 1 << endl;
  int sinal = s[s.size() - 1] == 'H' ? 1 : -1;  // se x^k é positivo ou negativo
  for (int i = p.size() - 1; i >= 0; i--) {
    cout << p[i] * sinal << (i == 0 ? "\n" : " ");
  }
}
