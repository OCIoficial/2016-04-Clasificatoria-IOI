/*
 * -----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <nlehmann@dcc.uchile.cl> wrote this file. As long as you retain this notice
 * you can do whatever you want with this stuff. If we meet some day, and you
 * think this stuff is worth it, you can buy me a beer in return Nicolás Lehmann
 * -----------------------------------------------------------------------------
 */
#include <iostream>
#include <tuple>
using namespace std;

int xa[60], ya[60], xb[60], yb[60], dira[60], dirb[60];
long long c[60];
int x,y;

void rot(int xx, int yy, int dd){
  //aplicamos la rotación al vector (xx,yy). Lo guardamos en variables globales x,y.
  // 0 = nada
  // 1 = 90° a la derecha
  // 2 = 180°
  // 3 = 90° a la izquierda.
  if(dd == 0){x=xx; y=yy;}
  if(dd == 1){x=yy; y=-xx;}
  if(dd == 2){x=-xx; y=-yy;}
  if(dd == 3){x=-yy; y=xx;}
}
tuple<int,int,int> reca(long long n, int xx, int yy, int d, int h);
tuple<int,int,int> recb(long long n, int xx, int yy, int d, int h);

tuple<int,int,int> reca(long long n, int xx, int yy, int d, int h) {
  //recursión en a: Devuelve la posición y dirección
  // obtenida luego de avanzar N veces partiendo desde a.
  // entrada:
  // N = pasos por recorrer
  // xx = posición x inicial
  // yy = posición y inicial
  // d = dirección inicial
  // h = cantidad de veces que se substituye a.
  long N = n;
  int r0, r1, r2;
  r0=xx; r1=yy; r2=d;
  //si N = 0, nada que hacer.
  if(N == 0){return make_tuple(r0,r1,r2);}
  //si N = c[h], se avanza todo lo que está guardado en xa[h],ya[h].
  if(N == c[h]){
    rot(xa[h],ya[h],r2); r0+=x; r1+=y; r2=(r2+dira[h])%4;
    return make_tuple(r0,r1,r2);
  }
  //a -> aRbFR
  //si no, se aplica la substitución
  int k = h-1;
  //si la solución está contenida en la subparte a, trabajar ahí
  if(N < c[k]){return reca(n,xx,yy,d,k);}
  //si no, sumar el aporte de avanzar a[k] y rotar a al derecha.
  N-=c[k];
  rot(xa[k],ya[k],r2);
  r0+=x; r1+=y; r2=(r2+dira[k]+1)%4;
  //devolver el aporte de hacer b.
  return recb(N,r0,r1,r2,k);
  //no se necesita chequear el FR final, en ese caso se tendría N == c[h].
}

tuple<int,int,int> recb(long long n, int xx, int yy, int d, int h){
  //recursión en b: Devuelve la posición y dirección
  // obtenida luego de avanzar N veces partiendo desde b.
  // entrada:
  // N = pasos por recorrer
  // xx = posición x inicial
  // yy = posición y inicial
  // d = dirección inicial
  // h = cantidad de veces que se substituye b.
  long long N = n;
  int r0=xx, r1=yy, r2=d;
  if(N == 0){return make_tuple(r0,r1,r2);}
  if(N == c[h]){
    rot(xb[h],yb[h],r2); r0+=x; r1+=y; r2=(r2+dirb[h])%4;
    return make_tuple(r0,r1,r2);
  }
  int k = h-1;
  //b -> LFaLb
  //si no, se aplica la substitución
  //LF
  r2=(r2+3)%4;
  rot(0,1,r2);
  r0+=x; r1+=y;
  N--;
  if(N == 0){return make_tuple(r0,r1,r2);}
  //aL
  if(N < c[k]){return reca(N,r0,r1,r2,k);}
  else{
    rot(xa[k],ya[k],r2);
    r0+=x; r1+=y; r2=(r2+dira[k]+3)%4;
    N-=c[k];
  }
  if(N > 0){
    return recb(N,r0,r1,r2,k);
  }
  return make_tuple(r0,r1,r2);
}


int main() {
  int len = 60;
  int xx, yy, dd;
  xa[0]=
    xa[0]=ya[0]=xb[0]=yb[0]=0; dira[0]=dirb[0]=0; c[0]=0;
  //rellenamos los arreglos usando la regla de sustitución
  for (int i = 1; i < len; i++) {
    //calculamos c[i].
    c[i]=2*c[i-1]+1;
    ////////substituimos a -> aRbFR
    //a
    xx = xa[i-1]; yy = ya[i-1]; dd = dira[i-1];
    //R (rotar a la derecha)
    dd = (dd+1)%4;
    //b
    rot(xb[i-1],yb[i-1],dd);
    xx +=x; yy+=y;
    dd=(dd+dirb[i-1])%4;
    //F
    rot(0,1,dd);
    xx +=x; yy+=y;
    //R
    dd = (dd+1)%4;
    //Asignamos los valores.
    xa[i]=xx; ya[i]=yy; dira[i] = dd;
    ////////substituimos b -> LFaLb.
    //LF
    xx = -1; yy = 0; dd = 3;
    //a
    rot(xa[i-1],ya[i-1],dd);
    xx+=x; yy+=y; dd = (dd+dira[i-1])%4;
    //L
    dd = (dd+3)%4;
    //b
    rot(xb[i-1],yb[i-1],dd);
    xx+=x; yy+=y; dd = (dd+dirb[i-1])%4;
    //Asignamos los valores.
    xb[i]=xx; yb[i]=yy; dirb[i] = dd;
  }
  long long N;
  cin >> N;
  int a, b;
  tie(a,b, ignore) = reca(N-1,0,1,0,59);
  //imprimir la respuesta.
  cout << a << " " << b << endl;
  return 0;
}
