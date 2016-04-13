#include <iostream>

#include "domino.h" 


using namespace std;

int main() {
	int t, n, k, f;
	int *d;
	
	cin >> t;
	
	switch (t) {
	case 1:
		cin >> n;
		cout << (cuadrado(n) ? "true" : "false") << endl;
		return 0;
		
	case 2:
		cin >> n >> f;
		d = new int[2 * f];
		for (int i = 0; i < 2 * f; i++)
			cin >> d[i];
		cout << (validar(n, f, d) ? "true" : "false") << endl;
		return 0;
		
	case 3:
		cin >> n >> k >> f;
		d = new int[2 * f];
		cout << (construir(n, k, f, d) ? "true" : "false") << endl;
		for (int i = 0; i < 2 * f; i++)
			cout << d[i] << (i + 1 != 2 * f ? " " : "\n");
		return 0;
	default:
		return 1;
	}
}
