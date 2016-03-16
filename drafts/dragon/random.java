import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Arrays;
// NOTA: ESTE ARCHIVO ES UN DESASTRE, hay que arreglarlo pa una solución oficial. 
// Esta huea calcula soluciones en O(log^2(n))
// Puse codigo pa generar codigo pa imprimir imagenes hermosas en TIKZ
// Nelman es un dinosaurio que vive en nuestra mente.

public class random {

	static public int gcd(int a, int b){
		if(a > b){return gcd(b,a);}
		if(a == 0){return b;}
		return gcd(b%a,a);
	}
	static public long gcd(long a, long b){
		if(a > b){return gcd(b,a);}
		if(a == 0){return b;}
		return gcd(b%a,a);
	}

	static long mod_exp(long x, long n, long p) {
	  if (n == 0) return 1;
	  if (n % 2 == 1)return (mod_exp(x, n-1, p) * x) % p;
	  x = mod_exp(x, n/2, p);
	  return (x * x) % p;
	}

	static public boolean is_square(long x){
		long y = sqrt(x);
		return x == y*y;
	}
	static public long sqrt(long x){
		return (long) Math.floor(Math.sqrt(x));
	}
	static public long pow(long x, int n){
		long a = 1;
		for (int i = 0; i < n; i++) {
			a*=x;
		}
		return a;
	}
	public static int digital_root(int x){
		if(x < 10){return x;}
		int a = 0; int b = x;
		while(b != 0){
			a+= b%10;
			b/=10;
		}
		return digital_root(a);
	}
	
	
	
	///////////////////////////////////////////////
	///////////////////////////////////////////////
	///////////////////////////////////////////////
	///////////////////////////////////////////////
	///////////////////////////////////////////////
	///////////////////////////////////////////////
	///////////////////////////////////////////////

	
	public static int[] recb(long n, int xx, int yy, int d, int h){
		long N = n;
		int[] r = new int[3];
		r[0]=xx; r[1]=yy; r[2]=d;
		if(N == 0){return r;}
		if(N == c[h]){
			rot(xb[h],yb[h],r[2]); r[0]+=x; r[1]+=y; r[2]=(r[2]+dirb[h])%4;
			return r;
		}
		int k = h-1;
		//b -> LFaLb
		//LF
		r[2]=(r[2]+3)%4;
		rot(0,1,r[2]);
		r[0]+=x; r[1]+=y;
		N--;
		if(N == 0){return r;}
		//aL
		if(N < c[k]){return reca(N,r[0],r[1],r[2],k);}
		else{
			rot(xa[k],ya[k],r[2]);
			r[0]+=x; r[1]+=y; r[2]=(r[2]+dira[k]+3)%4;
			N-=c[k];
		}
		if(N > 0){
			return recb(N,r[0],r[1],r[2],k);
		}
		return r;
	}
	
	public static int[] reca(long n, int xx, int yy, int d, int h){
		long N = n;
		int[] r = new int[3];
		r[0]=xx; r[1]=yy; r[2]=d;
		if(N == 0){return r;}
		if(N == c[h]){
			rot(xa[h],ya[h],r[2]); r[0]+=x; r[1]+=y; r[2]=(r[2]+dira[h])%4;
			return r;
		}
		//a -> aRbFR
		int k = h-1;
		if(N < c[k]){return reca(n,xx,yy,d,k);}
		N-=c[k];
		rot(xa[k],ya[k],r[2]);
		r[0]+=x; r[1]+=y; r[2]=(r[2]+dira[k]+1)%4;
		return recb(N,r[0],r[1],r[2],k);
	}
	
	static public int[] xa,ya,xb,yb,dira,dirb;
	static public long[] c;
	static public int x,y;
	
	static public void rot(int xx, int yy, int dd){
		if(dd == 0){x=xx; y=yy;}
		if(dd == 1){x=yy; y=-xx;}
		if(dd == 2){x=-xx; y=-yy;}
		if(dd == 3){x=-yy; y=xx;}
	}
	
	public static void main(String[] args) throws IOException {
		//a -> aRbFR
		//b -> LFaLb 
		xa = new int[60];
		ya = new int[60];
		xb = new int[60];
		yb = new int[60];
		c = new long[60];
		dira = new int[60];
		dirb = new int[60];
		int dd,xx,yy;
		xa[0]=ya[0]=xb[0]=yb[0]=0; dira[0]=dirb[0]=0; c[0]=0;
		for (int i = 1; i < yb.length; i++) {
			////////para a
			//a
			xx = xa[i-1]; yy = ya[i-1]; dd = (dira[i-1]+1)%4;
			//Rb
			rot(xb[i-1],yb[i-1],dd);
			xx +=x; yy+=y;
			dd=(dd+dirb[i-1])%4;
			//F
			rot(0,1,dd);
			xx +=x; yy+=y;
			//R
			dd = (dd+1)%4;
			//assign
			xa[i]=xx; ya[i]=yy; dira[i] = dd;
			////////para b
			//LF
			xx = -1; yy = 0; dd = 3;
			//aL
			rot(xa[i-1],ya[i-1],dd);
			xx+=x; yy+=y;
			dd = (dd+3+dira[i-1])%4;
			//b
			rot(xb[i-1],yb[i-1],dd);
			xx+=x; yy+=y;
			dd = (dd+dirb[i-1])%4;
			//assign
			xb[i]=xx; yb[i]=yy; dirb[i] = dd;
			c[i]=2*c[i-1]+1;
		}
		long N = 500;
		N = 1000000000000L;
		N--;
		int[] resp = reca(N,0,1,0,50);
		System.out.println(Arrays.toString(resp));
		//Para dibujar en latex usando Tikz:
		int X = 0; int Y = 0;
		PrintWriter pw = new PrintWriter(new FileWriter("curvita.txt"));
		for (int i = 0; i < 1000; i++) {
			int[] r = reca(i,0,1,0,10);
			pw.println("\\draw[thick,-,red] ("+X+","+Y+") to ("+r[0]+","+r[1]+");");
			X = r[0]; Y = r[1];
		}
		pw.close();
	}
}
