/*
 * -----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <nlehmann@dcc.uchile.cl> wrote this file. As long as you retain this notice
 * you can do whatever you want with this stuff. If we meet some day, and you
 * think this stuff is worth it, you can buy me a beer in return Nicolás Lehmann
 * -----------------------------------------------------------------------------
 */
#include "hielo.h"

#include <queue>
#include <tuple>
#include <climits>
using namespace std;
typedef tuple<int, int, int> ti;


bool posible(int N, bool rocas[100][100], int xi, int yi, int xf, int yf) {
  return minimo(N, rocas, xi, yi, xf, yf) != -1;
}
bool choca(int N, bool rocas[100][100], int x, int y) {
  return x < 0 || x >= N || y < 0 || y >= N || rocas[x][y];
}

template<typename Fun>
void vecinos(int N, bool rocas[100][100], int x, int y, Fun f) {
  int dx[] = {-1, 0, 1, 0};
  int dy[] = { 0, 1, 0,-1};

  for (int i = 0; i < 4; ++i) {
    int cx = x, cy = y;
    while (!choca(N, rocas, cx+dx[i], cy+dy[i]))
      cx += dx[i], cy += dy[i];
    f(cx, cy, abs(cx-x) + abs(cy-y));
  }
}

int minimo(int N, bool rocas[100][100], int xi, int yi, int xf, int yf) {
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
    vecinos(N, rocas, x, y, [&](int vx, int vy, int vd) {
        if (d + vd < dist[vx][vy])
          q.push(make_tuple(d + vd, vx, vy)), dist[vx][vy] = d + vd;
      });
  }
  return -1;
}

