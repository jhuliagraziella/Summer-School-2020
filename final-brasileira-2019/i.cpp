// Link pro contest: https://codeforces.com/gym/102428

#include <bits/stdc++.h>

using namespace std;

#define mod 1000000007

typedef long long ll;

int n, l;
bool vis[2003];
ll cont[2003];
vector<int> g[2003];

ll dfs(int i) {
  // O único detalhe é que precisa usar um vetor de vis porque cont[i] % mod
  // pode ser 0 mesmo quando i já foi processado.
  if (vis[i]) return cont[i];
  for (int j = 0; j < g[i].size(); j++) {
    int u = g[i][j];
    cont[i] = (cont[i] + dfs(u) + (u >= l)) % mod;
  }
  vis[i] = true;
  return cont[i];
}

int main () {
  cin.tie(0); ios::sync_with_stdio(false);

  cin >> n >> l;
  for (int i = 0; i < l; i++) {
    int k;
    cin >> k;
    for (int j = 0; j < k; j++) {
      int x;
      cin >> x;
      g[i].push_back(x - 1);
    }
  }
  dfs(0);
  ll antes = cont[0];
  ll depois = 0;
  for (int i = l; i < n; i++) {
    depois += vis[i];
  }

  cout << antes << ' ' << depois << endl;
}
