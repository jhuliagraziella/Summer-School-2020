// https://codeforces.com/contest/837/problem/F

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

typedef struct mat {
  int n;
  ll M[30][30];
} Mat;

Mat id;

ll k;
vector<ll> A;

// Pra previnir overflow, se x*y >= k retorna k, já que só precisamos achar
// algum valor >= k.
ll mult(ll x, ll y) {
  if (!x || !y) return 0;
  if (x >= 2 * k / y) return k;
  return min(x * y, k);
}

Mat mat_mult(const Mat& A, const Mat& B) {
  Mat C;
  C.n = A.n;
  for (int i = 0; i < A.n; i++) {
    for (int j = 0; j < B.n; j++) {
      C.M[i][j] = 0LL;
      for (int l = 0; l < A.n; l++) {
        C.M[i][j] = min(C.M[i][j] + mult(A.M[i][l], B.M[l][j]), k);
      }
    }
  }
  return C;
}

Mat mat_pow(const Mat& mat, ll exp) {
  if (!exp) return id;

  Mat ans = mat_pow(mat, exp/2);
  ans = mat_mult(ans, ans);

  return exp & 1 ? mat_mult(ans, mat) : ans;
}

// Se A.size <= 30 usa exp mat, complexidade = log2(10^18) * log2(10^18) * 30^3
ll solve_matrix() {
  Mat mat;
  mat.n = id.n = A.size();
  for (int i = 0; i < A.size(); i++) {
    for (int j = 0; j <= i; j++) {
      mat.M[i][j] = 1LL;
    }
    id.M[i][i] = 1LL;
  }

  ll esq = 0;
  ll dir = k + 1;
  ll mid = (esq + dir) / 2;
  while (esq < dir) {
    Mat teste = mat_pow(mat, mid);

    // Computa a última linha da matriz teste * A;
    ll sum = 0;
    for (int i = 0; i < A.size(); i++) {
      if (max(sum, max(teste.M[A.size() - 1][i], A[i])) >= k) {
        sum = k;
        break;
      }
      sum += mult(teste.M[A.size() - 1][i], A[i]);
    }

    if (sum >= k) {
      dir = mid;
    } else {
      esq = mid + 1;
    }
    mid = (esq + dir) / 2;
  }
  return mid;
}

// Se A.size() >= 30 resolve iterando.
ll solve_iterating() {
  ll a[2][A.size()];

  for (int i = 0; i < A.size(); i++) {
    if (A[i] >= k) return 0LL;
    a[0][i] = A[i];
  }

  ll ans = 1;
  while (1) {
    ll sum = 0;
    bool curr = (ans & 1);
    bool last = !curr;

    a[curr][0] = a[last][0];
    for (int i = 1; i < A.size(); i++) {
      a[curr][i] = min(k, a[curr][i-1] + a[last][i]);
    }

    if (a[curr][A.size() - 1] >= k) break;
    ans++;
  }
  return ans;
}

int main() {
  cin.tie(0); ios::sync_with_stdio(false);
  ll n;
  cin >> n >> k;

  for (int i = 0; i < n; i++) {
    ll a_i;
    cin >> a_i;

    // Pula os zeros do início.
    if (!a_i && A.empty()) continue;

    A.push_back(a_i);
  }

  ll ans = A.size() <= 30 ? solve_matrix() : solve_iterating();
  cout << ans << endl;
}
