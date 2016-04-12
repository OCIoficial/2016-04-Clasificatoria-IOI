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
