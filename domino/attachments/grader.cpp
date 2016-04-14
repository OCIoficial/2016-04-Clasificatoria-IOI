#include <iostream>

#include "domino.h" 


using namespace std;

int main() {
	int t, n, k, f;
	int *fichas;
	
	cin >> t;
	
	switch (t) {
	case 1:
		cin >> n;
		cout << (cuadrado(n) ? "true" : "false") << endl;
		return 0;
		
	case 2:
		cin >> n >> f;
		fichas = new int[2 * f];
		for (int i = 0; i < 2 * f; i++)
			cin >> fichas[i];
		cout << (verificar(n, f, fichas) ? "true" : "false") << endl;
		return 0;
		
	case 3: case 4:
		cin >> n >> k >> f;
		fichas = new int[2 * f];
		cout << (construir(n, k, f, fichas) ? "true" : "false") << endl;
		for (int i = 0; i < 2 * f; i++)
			cout << fichas[i] << (i + 1 != 2 * f ? " " : "\n");
		return 0;
	default:
		return 1;
	}
}
