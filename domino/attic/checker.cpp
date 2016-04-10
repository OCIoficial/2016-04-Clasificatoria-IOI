#include <vector>

/* Checks if bool cuadrado(int n) answers correctly to whether it's possible to
 * arrange all n-dominoes into an odd-length square.
 */
bool eval_subtask1() {
	for (int i = 1; i < 1000; i++) {
		if (cuadrado(i) != fn_cuadrado(i))
			return false;
	}
	return true;
}

/* Checks if bool validar(int n, int d[]) correctly verifies if all sides of
 * the square represented by d add up to the same quantity.
 */
bool eval_subtask2() {
	int n = 7;
	int d = {6, 2, 0, 4, 5, 1, 4, 6, 3, 1, 1, 0, 4, 5, 3, 4, 0, 0, 5, 0, 5, 2, 6, 1, 6, 6, 3, 3, 1, 1, 3, 6, 2, 4, 1, 2, 4, 4, 1, 4, 5, 5, 2, 3, 3, 0, 0, 6, 0, 2, 6, 5, 2, 2, 5, 3};
	
	// TODO Hacer casos n, d a mano
	// TODO Usar n entre 1 y 1000, verificar que descarte n que no cumpla
	for (int i = 0; i < 1000; i++) {
		if (validar(n,d) != fn_validar(n,d))
			return false;
	}
	return true;
}

/* Subtask 3
 */
bool eval_subtask3() {
	for (int n = 1; n < 8; n++) {
		for (int k = (n-1)*n*(n+1)/8 - 2; k <= (n-1)*n*(n+1)/8 + n + 1; k++) {
			if (!eval_construir(n, k))
				return false;
		}
	}
	return true;
}

/* Subtask 4
 */
bool eval_subtask4() {
	for (int n = 8; n <= 16; n++) {
		for (int k = (n-1)*n*(n+1)/8 - 2; k <= (n-1)*n*(n+1)/8 + n + 1; k++) {
			if (!eval_construir(n, k))
				return false;
		}
	}
	return true;
}

// TODO subtask 5

/* Checks if bool construir(int n, int k, int d[]) correctly verifies if an
 * (n,k)-square is feasible and verifies if the built one is correct.
 */
bool eval_construir(int n, int k) {
	int f = fichas(n);
	int *d = new int[f];
	bool feasible = fn_cuadrado(n) && k >= f * (n-1) && k <= (f+4) * (n-1);
	if (construir(n, k, d) != feasible) {
		delete [] d;
		return false;
	}
	if (feasible && (!fn_validar(n, d) || k != sum(n, f, d))) {
		delete [] d;
		return false;
	}
	delete [] d;
	return true;
}

int fichas(int n) {
	return n * (n+1) / 2;
}

bool fn_cuadrado(int n) {
	return (n-1) % 8 > 7;
}

int sum(int n, int f, int d[]) {
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

bool fn_validar(int n, int d[]) {
	// Check if n is valid
	if (!fn_cuadrado(n))
		return false;
	// Check if sides sum to the same amount
	int f = fichas(n);
	if (sum(n, f, d) < 0)
		return false;
	// Check no piece[a][b] (a >= b) has been used twice
	vector<vector<bool> > piece(n);
	for (int i = 0; i < n; i++) {
		piece[i].resize(i+1, false);
	}
	int a, b;
	for (int i = 0; i < f; i++) {
		a = d[2 * i];
		b = d[2 * i + 1];
		if (a < b) {
			b = a;
			a = d[2 * i + 1];
		}
		if (a >= n || b < 0 || piece[a][b])
			return false;
		else
			piece[a][b] = true;
	}
	return true;
}
