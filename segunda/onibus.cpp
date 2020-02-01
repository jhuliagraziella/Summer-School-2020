// https://www.urionlinejudge.com.br/judge/pt/problems/view/1474

#include <bits/stdc++.h>

#define mod 1000000

using namespace std;

typedef long long ll;
typedef struct mat
{
  ll m[3][3];
} Mat;

Mat mat_mult(Mat a, Mat b) {
  Mat ans;
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      ans.m[i][j] = 0;
      for (int k = 0; k < 2; k++)
        ans.m[i][j] = (ans.m[i][j] + a.m[i][k] * b.m[k][j]) % mod;
    }
  }
  return ans;
}

// retorna a matriz identidade.
Mat id() {
  Mat id;
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      id.m[i][j] = (i == j);
    }
  }
  return id;
}

Mat mat_pow(const Mat& base, ll exp) {
  if (exp == 0) return id();

  Mat ans = mat_pow(base, exp/2);
  ans = mat_mult(ans, ans);

  if (exp % 2) ans = mat_mult(ans, base);
  return ans;
}

int main() {
  cin.tie(0); ios::sync_with_stdio(false);

  ll n, k, l;
  while (cin >> n >> k >> l) {
    k %= mod;
    l %= mod;
    Mat base;
    base.m[0][0] = 0;
    base.m[0][1] = l;
    base.m[1][0] = 1;
    base.m[1][1] = k;

    Mat mat = mat_pow(base, n / 5);
    ll f0 = 1;
    ll f1 = k;
    ll ans = (f0 * mat.m[0][0] + f1 * mat.m[1][0]) % mod;

    printf("%.6d\n", ans);
  }
}
