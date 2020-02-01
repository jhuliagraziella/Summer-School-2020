// https://codeforces.com/contest/787/problem/C

#include<bits/stdc++.h>

using namespace std;

int n;
vector<int> jogadas[2];  // jogadas[i] sao os movimentos q o jogador pode fazer
int dp[2][7003];  // dp(jogador, pos_monstro) = jogador ganha nessa pos?
                  // 0 = empate, 1 = vitoria, 2 = derrota
int pos_perdedora[2][7003];  // em quantas posicoes perdedoras essa pos alcanca

int vitoria = 1;
int derrota = 2;

void bfs() {
  // (i, 0) eh posicao perdedora, porque o ultimo jogador ganhou.
  dp[0][0] = derrota;
  dp[1][0] = derrota;
  queue<pair<int, int>> q;
  q.push(make_pair(0, 0));
  q.push(make_pair(1, 0));

  while (!q.empty()) {
    int jogador = q.front().first;
    int monstro = q.front().second;
    q.pop();

    // eu ja conheco dp[jogador][monstro].
    int ans = dp[jogador][monstro];

    // quais jogadas do OUTRO jogador me fazem chegar aqui?
    for (int i = 0; i < jogadas[!jogador].size(); i++) {
      int novo_monstro = (monstro + n - jogadas[!jogador][i]) % n;
      if (dp[!jogador][novo_monstro]) continue;

      if (ans == derrota) {
        dp[!jogador][novo_monstro] = vitoria;
        q.push(make_pair(!jogador, novo_monstro));
      } else {
        pos_perdedora[!jogador][novo_monstro]++;
        // Checka se ele so alcanca posicoes perdedoras
        if (pos_perdedora[!jogador][novo_monstro] >= jogadas[!jogador].size()) {
          dp[!jogador][novo_monstro] = derrota;
          q.push(make_pair(!jogador, novo_monstro));
        }
      }
    }
  }
}

int main() {
  cin.tie(0);
  ios::sync_with_stdio(false);

  cin >> n;
  for (int jogador = 0; jogador < 2; jogador++) {
    int k;
    cin >> k;
    while (k--) {
      int s;
      cin >> s;
      jogadas[jogador].push_back(s);
    }
  }

  bfs();

  for (int jogador = 0; jogador < 2; jogador++) {
    for (int pos_monstro = 1; pos_monstro < n; pos_monstro++) {
      if (dp[jogador][pos_monstro] == 0) cout << "Loop ";
      else if (dp[jogador][pos_monstro] == vitoria) cout << "Win ";
      else cout << "Lose ";
    }
    cout << endl;
  }
}
