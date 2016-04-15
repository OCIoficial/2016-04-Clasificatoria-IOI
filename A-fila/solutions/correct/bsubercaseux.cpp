#include<bits/stdc++.h>
#define rep(i,n) for(int i = 0; i < n; ++i)
typedef long long intt;
using namespace std;

int main(){
	int N; cin >> N; vector<int> V(N),A(N);
	rep(i,N) cin >> V[i];

	int fila1,fila2; fila1 = fila2 = 0;
	rep(i,N){
		if(fila2 < fila1) // decide cambio de fila
			{A[i] = fila2; fila2 += V[i];} // espera el tiempo total de la fila1, su tiempo se suma a la fila
		else // se mantiene
			{A[i] = fila1; fila1 += V[i];} // espera el tiempo total de la fila1, su tiempo se suma a la fila
	}
	rep(i,N) cout << A[i] << endl;

return 0;}