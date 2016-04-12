#include <iostream>
#include <fstream>
#include <vector>


using namespace std;

bool fn_cuadrado(int n);
bool fn_validar(int n, vector<int> &d);
int fn_fichas(int n);
int fn_sum(int n, int f, vector<int> &d);
bool eval_construir(int n, int k, int f, vector<int> &d);

int wrong_ans() {
	cout << "0.0\n";
	return 0;
}

int right_ans() {
	cout << "1.0\n";
	return 0;
}

int main (int argc, char *argv[]) {
	ifstream fin;  	// Input
	ifstream fcorr;	// Expected
	ifstream ftest;	// Submission
	
	fin.open(argv[1]);
	fcorr.open(argv[2]);
	ftest.open(argv[3]);
	
	if (argc < 4) {
		cerr << "Missing parameter. Please contact contest administrator.\n";
		return -1;
	}
	
	if (!fin.is_open()) {
		cerr << "Could not open file \"" << argv[1] << "\". Please contact contest administrator.\n";
		return 1;
	}

	if (!fcorr.is_open()) {
		cerr << "Could not open file \"" << argv[2] << "\". Please contact contest administrator.\n";
		return 2;
	}

	if (!ftest.is_open()) {
		cerr << "Could not open file \"" << argv[3] << "\". Please contact contest administrator.\n";
		return 3;
	}
	
	fcorr.close();	// Unused
	
	int t, n, k, f, ld;
	bool ans, feasible;
	vector<int> d;
	
	fin >> t;
	
	switch (t) {
	case 1:
		fin >> n;
		ftest >> ans;
		return ans == fn_cuadrado(n) ? right_ans() : wrong_ans();
		
	case 2:
		fin >> n >> ld;
		d.resize(ld);
		for (int i = 0; i < ld; i++)
			fin >> d[i];
		ftest >> ans;
		return ans == fn_validar(n, d) ? right_ans() : wrong_ans();
		
	case 3:
		fin >> n >> k >> ld;
		d.resize(ld);
		ftest >> ans;
		for (int i = 0; i < ld; i++)
			ftest >> d[i];
		f = fn_fichas(n);
		feasible = fn_cuadrado(n) && k >= f * (n-1) && k <= (f+4) * (n-1);
		if (ans != feasible)
			wrong_ans();
		return eval_construir(n, k, f, d) ? right_ans() : wrong_ans();
		
	default:
		return 1;
	}
}

bool fn_cuadrado(int n) {
	return (n-1) % 8 >= 6;
}

bool fn_validar(int n, vector<int> &d) {
	if (!fn_cuadrado(n))
		return false;
	
	int f = n * (n + 1) / 2;
	if (fn_sum(n, f, d) < 0)
		return false;
	
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

int fn_fichas(int n) {
	return n * (n + 1) / 2;
}

int fn_sum(int n, int f, vector<int> &d) {
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

bool eval_construir(int n, int k, int f, vector<int> &d) {
	if (!fn_validar(n, d) || k != fn_sum(n, f, d)) {
		return false;
	}
	return true;
}
