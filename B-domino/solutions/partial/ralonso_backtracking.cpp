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
	if (pos == 0) {
		// Inicialización
		int c = k - (n - 1) * n * (n + 1) / 8;
		int f = n * (n + 1) / 2;
		for (int j0 = 0; j0 <= n; j0++) {
			if (c > j0)
				pieza[c][j0] = true;
			else
				pieza[j0][c] = true;
			d[0] = c;
			d[1] = j0;
			for (int j1 = 0; j1 <= n; j1++) {
				if (j0 == j1)
					continue;
				if (c > j1)
					pieza[c][j1] = true;
				else
					pieza[j1][c] = true;
				d[f / 2] = c;
				d[f / 2 + 1] = j1;
				for (int j2 = 0; j2 <= n; j2++) {
					if (j0 == j2 || j1 == j2)
						continue;
					if (c > j2)
						pieza[c][j2] = true;
					else
						pieza[j2][c] = true;
					d[f] = c;
					d[f + 1] = j2;
					for (int j3 = 0; j3 <= n; j3++) {
						if (j0 == j3 || j1 == j3 || j2 == j3)
							continue;
						if (c > j3)
							pieza[c][j3] = true;
						else
							pieza[j3][c] = true;
						d[3 * f / 2] = c;
						d[3 * f / 2 + 1] = j3;
						if (backtrack(n, k, d, 2, c + j0, pieza))
							return true;
						if (c > j3)
							pieza[c][j3] = false;
						else
							pieza[j3][c] = false;
					}
					if (c > j2)
						pieza[c][j2] = false;
					else
						pieza[j2][c] = false;
				}
				if (c > j1)
					pieza[c][j1] = false;
				else
					pieza[j1][c] = false;
			}
			if (c > j0)
				pieza[c][j0] = false;
			else
				pieza[j0][c] = false;
		}
		return false;
	}
	if (pos == n * (n + 1)) {
		// Revisar último lado
		return sidesum + d[0] == k;
	}
	// Revisar 1°/2°/3° lado
	if (pos % (n * (n + 1) / 4) == 0) {
		if (sidesum + d[pos] == k) {
			if (backtrack(n, k, d, pos + 2, d[pos] + d[pos + 1], pieza))
				return true;
		}
		return false;
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j <= i; j++) {
			if (!pieza[i][j]) {
				pieza[i][j] = true;
				d[pos] = i;
				d[pos + 1] = j;
				if (backtrack(n, k, d, pos + 2, sidesum + i + j, pieza))
					return true;
				pieza[i][j] = false;
			}
		}
	}
	return false;
}
