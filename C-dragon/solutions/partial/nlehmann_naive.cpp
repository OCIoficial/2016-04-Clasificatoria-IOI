/*
 * -----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <nlehmann@dcc.uchile.cl> wrote this file. As long as you retain this notice
 * you can do whatever you want with this stuff. If we meet some day, and you
 * think this stuff is worth it, you can buy me a beer in return Nicolás Lehmann
 * -----------------------------------------------------------------------------
 */
#include <cstdio>
#include <vector>
#include <map>
using namespace std;

int main () {
  int N;
  scanf("%d", &N);

  vector<char> dragonseq = {'A', 'a'};
  vector<char> rulea = {'R', 'b', 'A', 'R'};
  vector<char> ruleb = {'L', 'A', 'a', 'L'};

  int as = 1;
  while (as < N) {
    unsigned int i = 0;
    while (i < dragonseq.size()) {
      if (dragonseq[i] == 'a') {
        dragonseq.insert(dragonseq.begin()+i+1, rulea.begin(), rulea.end());
        i += 5;
        as++;
      } else if (dragonseq[i] == 'b') {
        dragonseq.insert(dragonseq.begin()+i, ruleb.begin(), ruleb.end());
        i += 5;
        as++;
      } else {
        i += 1;
      }
    }
  }

  int dx = 0, dy = 1;
  int x = 0, y = 0;
  as = 0;
  for (char c : dragonseq) {
    switch (c) {
    case 'R': tie(dx, dy) = make_pair(dy, -dx); break;
    case 'L': tie(dx, dy) = make_pair(-dy, dx); break;
    case 'A': as++, x += dx, y += dy; break;
    }
    if (as == N)
      break;
  }
  printf("%d %d\n", x, y);

  return 0;
}
