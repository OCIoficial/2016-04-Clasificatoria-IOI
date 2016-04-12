#include <iostream>

#include "domino.h" 


using namespace std;

int main() {
	int t, n, k, ld;
	int *d;
	
	cin >> t;
	
	switch (t) {
	case 1:
		cin >> n;
		cout << cuadrado(n) << endl;
		return 0;
		
	case 2:
		cin >> n >> ld;
		d = new int[ld];
		for (int i = 0; i < ld; i++) {
			cin >> d[i];
		}
		cout << validar(n, d) << endl;
		return 0;
		
	case 3:
		cin >> n >> k >> ld;
		d = new int[ld];
		cout << construir(n, k, d) << endl;
		for (int i = 0; i < ld; i++) {
			cout << d[i] << (i+1 != ld ? " " : "\n");
		}
		return 0;
	default:
		return 1;
	}
}
