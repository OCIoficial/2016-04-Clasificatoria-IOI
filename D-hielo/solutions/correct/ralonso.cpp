#include <vector>
#include <utility>
#include <queue>
#include "hielo.h"


using namespace std;

int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};

bool posible(int N, bool rocas[100][100], int xi, int yi, int xf, int yf) {
	return minimo(N, rocas, xi, yi, xf, yf) >= 0;
	
}

int minimo(int N, bool rocas[100][100], int xi, int yi, int xf, int yf) {
	vector<vector<int> > pasos(101, vector<int>(101, -1));
	vector<vector<bool> > piedras(102, vector<bool>(102, true));
	
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			piedras[i+1][j+1] = rocas[i][j];
		}
	}
	
	priority_queue<pair<int,pair<int,int> > > pq;
	
	pq.emplace(0, pair<int,int>(xi + 1, yi + 1));
	
	while (!pq.empty()) {
		pair<int,pair<int,int> > curr = pq.top();
		int d = -curr.first;
		int x = curr.second.first;
		int y = curr.second.second;
		pq.pop();
		
		if (xf + 1 == x && yf + 1 == y)
			return d;
		
		if (pasos[x][y] != -1 && pasos[x][y] <= d)
			continue;
		
		pasos[x][y] = d;
		for (int r = 0; r < 4; r++) {
			if (piedras[x + dx[r]][y + dy[r]])
				continue;
			
			for (int i = 1; ; i++) {
				if (piedras[x + (i+1) * dx[r]][y + (i+1) * dy[r]]) {
					pq.emplace(-(d + i), pair<int,int>(x + i * dx[r], y + i * dy[r]));
					break;
				}
			}
		}
	}
	return -1;
}
