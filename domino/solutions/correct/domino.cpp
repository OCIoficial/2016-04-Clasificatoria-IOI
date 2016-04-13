#include <vector>
#include <utility>

#include "domino.h"


using namespace std;

int suma(int, int, int d[]);
int fichas(int);
pair<int,int> pareja(int, int, int);

bool cuadrado(int n) {
	return (n-1) % 8 >= 6;
}

bool validar(int n, int f, int d[]) {
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
	
	int a, b;
	
	if (((n + 1) & 8) == 0) {
		// Llenar las piezas de las esquinas con su pieza "pareja"
		for (int s = 0; s < 4; s++) {
			d[s * p] = c;
			d[s * p + 1] = s;
			a = c > s? c : s;
			b = c > s? s : c;
			pair<int,int> par = pareja(a, b, n);
			d[s * p + 2] = par.first;
			d[s * p + 3] = par.second;
			pieza[a][b] = true;
			pieza[par.first][par.second] = true;
		}
		// Llenar el resto con parejas cualesquiera
		int a = 0, b = 0;
		for (int i = 2; 2 * i < p; i += 2) {
			for (int s = 0; s < 4; s++) {
				while (pieza[a][b]) {
					if (a == b) {
						a++;
						b = 0;
					} else {
						b++;
					}
				}
				d[s * p + 2 * i] = a;
				d[s * p + 2 * i + 1] = b;
				pair<int,int> par = pareja(a, b, n);
				d[s * p + 2 * i + 2] = par.first;
				d[s * p + 2 * i + 3] = par.second;
				pieza[a][b] = true;
				pieza[par.first][par.second] = true;
			}
		}
	} else {
		// Llenar las piezas de las esquinas con su pieza "pareja"; agregar una
		// pieza mediana/promedio para cubrir la posición impar; si la pieza ya
		// era mediana/promedio, llenar con una pareja al azar
		for (int s = 0; s < 4; s++) {
			d[s * p] = c;
			d[s * p + 1] = s;
			a = c > s? c : s;
			b = c > s? s : c;
			pieza[a][b] = true;
			if (a + b != n - 1) {
				pair<int,int> par = pareja(a, b, n);
				d[s * p + 2] = par.first;
				d[s * p + 3] = par.second;
				pieza[par.first][par.second] = true;
			}
		}
		for (int s = 0; s < 4; s++) {
			if (c + s != n - 1) {
				a = n - 1 - s;
				b = s;
				d[s * p + 4] = a;
				d[s * p + 5] = b;
				pieza[a][b] = true;
			} else {
				a = b = 0;
				while (pieza[a][b] || (a + b == n - 1)) {
					if (a == b) {
						a++;
						b = 0;
					} else {
						b++;
					}
				}
				d[s * p + 2] = a;
				d[s * p + 3] = b;
				pair<int,int> par = pareja(a, b, n);
				d[s * p + 4] = par.first;
				d[s * p + 5] = par.second;
				pieza[a][b] = true;
				pieza[par.first][par.second] = true;
			}
		}
		// Llenar el resto con parejas cualesquiera
		int a = 0; b = 0;
		for (int i = 3; 2 * i < p; i += 2) {
			for (int s = 0; s < 4; s++) {
				while (pieza[a][b]) {
					if (a == b) {
						a++;
						b = 0;
					} else {
						b++;
					}
				}
				d[s * p + 2 * i] = a;
				d[s * p + 2 * i + 1] = b;
				pair<int,int> par = pareja(a, b, n);
				d[s * p + 2 * i + 2] = par.first;
				d[s * p + 2 * i + 3] = par.second;
				pieza[a][b] = true;
				pieza[par.first][par.second] = true;
			}
		}
	}
	
	return true;
}

pair<int,int> pareja(int a, int b, int n) {
	if (a + b != n - 1)
		return pair<int,int>(n-1-b, n-1-a);
	
	if (b % 2 == 0)
		return pair<int,int>(a-1, b+1);
	else
		return pair<int,int>(a+1, b-1);
}

int fichas(int n) {
	return n * (n + 1) / 2;
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
