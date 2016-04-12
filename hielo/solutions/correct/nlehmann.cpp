/*
 * -----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <nlehmann@dcc.uchile.cl> wrote this file. As long as you retain this notice
 * you can do whatever you want with this stuff. If we meet some day, and you
 * think this stuff is worth it, you can buy me a beer in return Nicolás Lehmann
 * -----------------------------------------------------------------------------
 */
#include "hielo.h"

#include <cstdio>
#include <cstdlib>
#include <queue>
#include <tuple>
#include <climits>
#include <iostream>
using namespace std;
typedef tuple<int, int, int> ti;


bool posible(vector<vector<bool> > &roca, int N, int xi, int yi, int xf, int yf) {
  return minimo(roca, N, xi, yi, xf, yf) != -1;
}

bool choca(const vector<vector<bool> > &roca, int x, int y) {
  return x < 0 || x >= roca.size() || y < 0 || y >= roca.size() || roca[x][y];
}

template<typename Fun>
void vecinos(const vector<vector<bool> > &roca, int x, int y, Fun f) {
  int dx[] = {-1, 0, 1, 0};
  int dy[] = { 0, 1, 0,-1};

  for (int i = 0; i < 4; ++i) {
    int cx = x, cy = y;
    while (!choca(roca, cx+dx[i], cy+dy[i]))
      cx += dx[i], cy += dy[i];
    f(cx, cy, abs(cx-x) + abs(cy-y));
  }
}

int minimo(vector<vector<bool> > &roca, int N, int xi, int yi, int xf, int yf) {
  priority_queue<ti, vector<ti>, greater<ti>> q;
  vector<vector<int> > dist(N, vector<int>(N, INT_MAX));
  q.push(make_tuple(0, xi, yi));
  dist[xi][yi] = 0;

  while (!q.empty()) {
    int d = get<0>(q.top());
    int x = get<1>(q.top());
    int y = get<2>(q.top());
    q.pop();
    if (x == xf && y == yf)
      return d;

    if (d > dist[x][y])
      continue;
    vecinos(roca, x, y, [&](int vx, int vy, int vd) {
        if (d + vd < dist[vx][vy])
          q.push(make_tuple(d + vd, vx, vy)), dist[vx][vy] = d + vd;
      });
  }
  return -1;
}

int main() {
  int T, N;

  scanf("%d%d", &T, &N);

  int xi, yi, xf, yf;
  scanf("%d%d%d%d", &xi, &yi, &xf, &yf);

  vector<vector<bool> > roca(N, vector<bool>(N));
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      int b;
      scanf("%d", &b);
      roca[j][i] = b;
    }
  }

  if (T == 1)
    printf(posible(roca, N, xi, yi, xf, yf) ? "true\n" : "false\n");
  else if (T == 2)
    printf("%d\n", minimo(roca, N, xi, yi, xf, yf));
  else
    exit(1);

  return 0;
}
