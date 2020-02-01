// https://codeforces.com/contest/954/problem/F

#include <bits/stdc++.h>

typedef long long ll;

using namespace std;

#define mod 1000000007

// Identifica o inicio ou o fim de um obstaculo.
typedef struct obstaculo {
  int linha;
  ll coluna;
  bool fim;
} Obstaculo;

// As colunas [l, r] possuem a linha i livre se linha_livre[i] == true.
typedef struct corredor {
  vector<bool> linha_livre;
  ll l, r;
} Corredor;

typedef struct mat {
  ll M[3][3];
} Mat;

Mat create_mat(const vector<bool>& linha_livre) {
  Mat m;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      m.M[i][j] = linha_livre[j];
    }
  }
  m.M[0][2] = m.M[2][0] = 0;
  return m;
}

Mat mat_mult(const Mat &a, const Mat &b) {
  Mat c;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      c.M[i][j] = 0;
      for (int k = 0; k < 3; k++) {
        c.M[i][j] = (c.M[i][j] + a.M[i][k] * b.M[k][j]) % mod;
      }
    }
  }
  return c;
}

Mat mat_id(int tam) {
  Mat m;
  for (int i = 0; i < tam; i++) {
    for (int j = 0; j < tam; j++) {
      m.M[i][j] = (i == j);
    }
  }
  return m;
}

Mat mat_pow(const Mat& a, ll k) {
  if (!k) return mat_id(3);
  Mat aux = mat_pow(a, k/2);
  aux = mat_mult(aux, aux);
  return k&1 ? mat_mult(a, aux) : aux;
}

Corredor create_corredor(const vector<int>& num_obs, ll l, ll r) {
  Corredor c;
  for (int i = 0; i < 3; i++) {
    c.linha_livre.push_back(num_obs[i] == 0);
  }
  c.l = l;
  c.r = r;
  return c;
}

bool operator < (const Obstaculo &a, const Obstaculo &b) {
  return a.coluna < b.coluna;
}

int main() {
  cin.tie(0); ios::sync_with_stdio(false);

  ll n, m;
  cin >> n >> m;

  vector<Obstaculo> obstaculos;
  for (int i = 0; i < n; i++) {
    int a;
    ll l, r;
    cin >> a >> l >> r;

    Obstaculo o;
    o.linha = a - 1;
    o.coluna = l;
    o.fim = false;
    obstaculos.push_back(o);

    o.coluna = r + 1;
    o.fim = true;
    obstaculos.push_back(o);
  }

  sort(obstaculos.begin(), obstaculos.end());

  vector<Corredor> corredores;
  vector<int> num_obs = {0, 0, 0};
  corredores.push_back(create_corredor(num_obs, 1, obstaculos[0].coluna - 1));

  for (int i = 0; i < obstaculos.size(); i++) {
    num_obs[obstaculos[i].linha] += obstaculos[i].fim ? -1 : 1;

    int j = i+1;
    while (j < obstaculos.size() &&
           obstaculos[i].coluna == obstaculos[j].coluna) {
      num_obs[obstaculos[j].linha] += obstaculos[j].fim ? -1 : 1;
      j++;
    }
    ll l = obstaculos[i].coluna;
    ll r = (j < obstaculos.size()) ? obstaculos[j].coluna : m;
    corredores.push_back(create_corredor(num_obs, l, r));

    i = j - 1;
  }

  vector<ll> v = {1, 1, 1};
  for (int i = 0; i < corredores.size(); i++) {
    Mat m = create_mat(corredores[i].linha_livre);
    m = mat_pow(m, corredores[i].r - corredores[i].l);

    ll aux[] = {v[0], v[1], v[2]};
    for (int j = 0; j < 3; j++) {
      v[j] = 0;
      for (int k = 0; k < 3; k++) {
        v[j] = (v[j] + m.M[j][k] * aux[k]) % mod;
      }
    }
  }
  cout << v[1] << endl;
}
