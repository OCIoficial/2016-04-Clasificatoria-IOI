#include <iostream>
#include <fstream>
#include <string>
#include <vector>


using namespace std;

bool fn_cuadrado(int n);
bool fn_validar(int n, int f, int d[]);
int fn_fichas(int n);
int fn_sum(int n, int f, int d[]);
bool eval_construir(int n, int k, int f, int d[]);

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
	
	int t, n, k, f;
	string raw_ans;
	bool ans, feasible;
	int *d;
	
	fin >> t;
	
	switch (t) {
	case 1:
		fin >> n;
		ftest >> raw_ans;
		if (raw_ans == "true")
			ans = true;
		else if (raw_ans == "false")
			ans = false;
		else
			return wrong_ans();
		return ans == fn_cuadrado(n) ? right_ans() : wrong_ans();
		
	case 2:
		fin >> n >> f;
		d = new int[2 * f];
		for (int i = 0; i < 2 * f; i++)
			fin >> d[i];
		ftest >> raw_ans;
		if (raw_ans == "true")
			ans = true;
		else if (raw_ans == "false")
			ans = false;
		else
			return wrong_ans();
		return ans == fn_validar(n, f, d) ? right_ans() : wrong_ans();
		
	case 3:
		fin >> n >> k >> f;
		d = new int[2 * f];
		ftest >> raw_ans;
		if (raw_ans == "true")
			ans = true;
		else if (raw_ans == "false")
			ans = false;
		else
			return wrong_ans();
		for (int i = 0; i < 2 * f; i++)
			ftest >> d[i];
		feasible = fn_cuadrado(n) && k >= f / 4 * (n-1) && k <= (f / 4 + 1) * (n-1);
		if (ans != feasible)
			return wrong_ans();
		return !feasible || eval_construir(n, k, f, d) ? right_ans() : wrong_ans();
		
	default:
		return 1;
	}
}

bool fn_cuadrado(int n) {
	return (n-1) % 8 >= 6;
}

bool fn_validar(int n, int f, int d[]) {
	if (!fn_cuadrado(n))
		return false;
	
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

int fn_sum(int n, int f, int d[]) {
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

bool eval_construir(int n, int k, int f, int d[]) {
	if (!fn_validar(n, f, d) || k != fn_sum(n, f, d)) {
		return false;
	}
	return true;
}
