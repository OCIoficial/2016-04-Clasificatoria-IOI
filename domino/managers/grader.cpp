#include <iostream>
#include <vector>

#include "domino.h" 


using namespace std;

int main() {
	int t, n, ld;
	
	cin >> t;
	
	switch (t) {
	case 1:
		cin >> n;
		cout << cuadrado(n) << endl;
		return 0;
		
	case 2:
		cin >> n >> ld;
		vector<int> d(ld);
		for (int i = 0; i < ld; i++) {
			cin >> d[i];
		}
		cout << validar(n, d) << endl;
		return 0;
		
	case 3:
		cin >> n >> k >> ld;
		vector<int> d(ld);
		cout << construir(n, k, d) << endl;
		for (int i = 0; i < ld; i++) {
			cout << d[i] << (i+1 != ld ? " " : endl);
		}
		return 0;
	default:
		return 1;
	}
}
