/*
 * -----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <nlehmann@dcc.uchile.cl> wrote this file. As long as you retain this notice
 * you can do whatever you want with this stuff. If we meet some day, and you
 * think this stuff is worth it, you can buy me a beer in return Nicolás Lehmann
 * -----------------------------------------------------------------------------
 */
#include <cstdio>


int main () {
  int N;
  scanf("%d", &N);

  int suma = 0, sumb = 0;
  for (int i = 0; i < N; ++i) {
    int t;
    scanf("%d", &t);

    if (sumb < suma) {
      printf("%d\n", sumb);
      sumb += t;
    } else {
      printf("%d\n", suma);
      suma += t;
    }

  }
}
