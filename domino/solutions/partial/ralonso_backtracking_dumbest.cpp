#include <vector>
#include <utility>

#include "domino.h"


using namespace std;

int suma(int, int, int d[]);
pair<int,int> pareja(int, int, int);
bool backtrack(int n, int k, int d[], int pos, int sidesum, vector<vector<bool> > &pieza);

bool cuadrado(int n) {
	return (n-1) % 8 >= 6;
}

bool verificar(int n, int f, int d[]) {
	// Revisa que n es válido
	if (!cuadrado(n))
		return false;
	// Revisa si los lados suman lo mismo
	if (suma(n, f, d) < 0)
		return false;
	// Revisa que pieza[a][b] (a >= b) no se ha usado más de una vez
	vector<vector<bool> > pieza(n);
	for (int i = 0; i < n; i++) {
		pieza[i].resize(i + 1, false);
	}
	int a, b;
	for (int i = 0; i < f; i++) {
		a = d[2 * i];
		b = d[2 * i + 1];
		if (a < b) {
			b = a;
			a = d[2 * i + 1];
		}
		if (a >= n || b < 0 || pieza[a][b])
			return false;
		else
			pieza[a][b] = true;
	}
	return true;
}

bool construir(int n, int k, int f, int d[]) {
	int p = f / 2;
	if (!cuadrado(n) || k < f / 4 * (n - 1) || k > (f / 4 + 1) * (n - 1))
		return false;
	
	// Valor promedio de las esquinas
	int c = k - (n - 1) * n * (n + 1) / 8;
	
	// Recordar qué piezas hemos usado
	vector<vector<bool> > pieza(n);
	for (int i = 0; i < n; i++) {
		pieza[i].resize(i+1, false);
	}
	
	return backtrack(n, k, d, 0, 0, pieza);
}

int suma(int n, int f, int d[]) {
	int side;
	for (int i = 0; i < 4; i++) {
		int curr = 0;
		for (int p = i * f / 2; p <= (i+1) * f / 2; p++) {
			curr += d[p % (2*f)];
		}
		if (i == 0) {
			side = curr;
		} else if (side != curr) {
			return -1;
		}
	}
	return side;
}

bool backtrack(int n, int k, int d[], int pos, int sidesum, vector<vector<bool> > &pieza) {
	if (pos == n * (n + 1)) {
		// Revisar último lado
		return sidesum + d[0] == k;
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j <= i; j++) {
			if (!pieza[i][j]) {
				if (pos == 0 && i != k - n*(n+1)*(n-1)/8)
					continue;
				pieza[i][j] = true;
				// Revisar lado
				if (pos != 0 && pos % (n * (n + 1) / 4) == 0) {
					if (sidesum + i == k && i == k - n*(n+1)*(n-1)/8) {
						d[pos] = i;
						d[pos + 1] = j;
						if (backtrack(n, k, d, pos + 2, i + j, pieza))
							return true;
					}
					if (sidesum + j == k && j == k - n*(n+1)*(n-1)/8) {
						d[pos] = j;
						d[pos + 1] = i;
						if (backtrack(n, k, d, pos + 2, i + j, pieza))
							return true;
					}
					pieza[i][j] = false;
					continue;
				}
				d[pos] = i;
				d[pos + 1] = j;
				if (backtrack(n, k, d, pos + 2, sidesum + i + j, pieza))
					return true;
				d[pos] = j;
				d[pos + 1] = i;
				if (backtrack(n, k, d, pos + 2, sidesum + i + j, pieza))
					return true;
				pieza[i][j] = false;
			}
		}
	}
	return false;
}
