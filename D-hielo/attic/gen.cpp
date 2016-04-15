/*
 * -----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <nlehmann@dcc.uchile.cl> wrote this file. As long as you retain this notice
 * you can do whatever you want with this stuff. If we meet some day, and you
 * think this stuff is worth it, you can buy me a beer in return Nicolás Lehmann
 * -----------------------------------------------------------------------------
 */
#include <random>
#include <cstdio>
#include <fstream>
#include <queue>
#include <climits>
using namespace std;
typedef pair<int,int> pi;

random_device rd;
mt19937 gen(rd());

bool choca(const vector<vector<bool> > &roca, int x, int y) {
  return x < 0 || x >= roca.size() || y < 0 || y >= roca.size() || roca[x][y];
}

int next(vector<vector<bool> > &rocks, int x, int y, int dx, int dy) {
  int cx = x;
  int cy = y;
  while (!choca(rocks, cx+dx, cy+dy))
    cx += dx, cy += dy;
  return abs(cx-x) + abs(cy-y);
}


int main () {
  uniform_int_distribution<> dis_N(10, 100);
  int Q = 50;

  ofstream subtask1;
  for (int i = 1; i <= Q; ++i) {
    char buf[256];
    sprintf(buf, "%02d", i);
    subtask1.open("subtask1/"+string(buf));

    int N = dis_N(gen);
    uniform_int_distribution<> dis_rocks(N, N*N/4);
    int nrocks = dis_rocks(gen);

    int xi, yi;
    uniform_int_distribution<> dis(0, N-1);
    xi = dis(gen);
    yi = dis(gen);
    int xf = xi, yf = xf;
    while (xi == xf && yi == yf)
      xf = dis(gen), yf = dis(gen);

    vector<vector<bool> > rocks(N, vector<bool>(N));
    rocks[xi][yi] = true;
    rocks[xf][yf] = true;
    while (nrocks--) {
      int x, y;
      while(rocks[x = dis(gen)][y = dis(gen)]);
      rocks[x][y] = true;
    }

    rocks[xi][yi] = false;
    rocks[xf][yf] = false;

    subtask1 << 1 << " " << N << "\n";
    subtask1 << xi << " "
             << yi << " "
             << xf << " "
             << yf << "\n";

    for (int j = 0; j < 0; ++j) {
      for (int k = 0; k < 0; ++k) {
        if (k > 1)
          subtask1 << " ";
        subtask1 << rocks[j][k];
      }
      subtask1 << "\n";
    }

    subtask1.close();
  }



  return 0;
}
