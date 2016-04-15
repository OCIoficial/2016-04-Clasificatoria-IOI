import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Scanner;

public class sbarbieri {

    static public int[] xa,ya,xb,yb,dira,dirb;
    static public long[] c;
    static public int x,y;

    public static void main(String[] args) throws IOException {
        //La sustitución está dada por las reglas de reescritura siguientes:
        //a -> aRbFR
        //b -> LFaLb
        //vamos a guardar la posición final y dirección luego de avanzar toda la instrucción
        //dada al reemplazar a una cantidad n de pasos. Esto se guarda en los arreglos xa,ya,dira que
        //guardan la posición (x,y) y la dirección. Es suficiente hacerlo para unas 60 iteraciones (en verdad se necesita menos).
        // La dirección se codificará como un entero mod 4. 0 = norte, 1 = este, 2 = sur, 3 = oeste.
        xa = new int[60];
        ya = new int[60];
        dira = new int[60];
        //lo mismo para b
        xb = new int[60];
        yb = new int[60];
        dirb = new int[60];
        // en c guardaremos la cantidad de pasos avanzados al substituir
        // ya sea a o b una cierta cantidad de veces. La recursión es c[i]=2*c[i-1]+1, c[0]=0.
        // La razón es la siguiente: si analizamos a -> aRbFR, entonces a[n] = a[n-1]Rb[n-1]FR.
        // Equivalentemente, b[n] = LFa[n-1]Lb[n-1]. Como ambas tienen la misma forma se obtiene esa recursión.
        c = new long[60];
        //creamos enteros auxiliares xx,yy,dd (posición y dirección)
        int xx,yy,dd;
        //valores iniciales en 0.
        xa[0]=ya[0]=xb[0]=yb[0]=0; dira[0]=dirb[0]=0; c[0]=0;
        //rellenamos los arreglos usando la regla de sustitución
        for (int i = 1; i < yb.length; i++) {
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
        Scanner in = new Scanner(System.in);
        long N = in.nextLong();
        int[] resp = reca(N-1,0,1,0,59);
        //imprimir la respuesta.
        System.out.println(resp[0]+" "+resp[1]);

        //Ahora leemos los datos.
        //Scanner in = new Scanner(System.in);
        //int h = 1;
        //while(true){
        //long N = in.nextLong();
        //// Avanzar N-1 pasos en la cadena obtenida al sustituir a 59 veces (se necesita menos)
        //// partiendo desde (0,1) mirando al norte (dirección 0).
        //int[] resp = reca(N-1,0,1,0,59);
        ////imprimir la respuesta.
        //System.out.println(resp[0]+" "+resp[1]);
        //PrintWriter pw1 = new PrintWriter(new FileWriter(h+".in"));
        //PrintWriter pw2 = new PrintWriter(new FileWriter(h+".sol"));
        //pw1.println(N);
        //pw2.println(resp[0]+" "+resp[1]);
        //h++;
        //pw1.close();
        //pw2.close();
        //}
        //Parte extra: genera un código en Tikz que dibuja la curva de dragón.
        //		int X = 0; int Y = 0;
        //		PrintWriter pw = new PrintWriter(new FileWriter("curvita.txt"));
        //		for (int i = 0; i < c[12]; i++) {
        //			int[] r = reca(i,0,1,0,13);
        //			pw.println("\\draw[thick,-,red] ("+X+","+Y+") to ("+r[0]+","+r[1]+");");
        //			X = r[0]; Y = r[1];
        //		}
        //		pw.close();
    }

    public static int[] reca(long n, int xx, int yy, int d, int h){
        //recursión en a: Devuelve la posición y dirección
        // obtenida luego de avanzar N veces partiendo desde a.
        // entrada:
        // N = pasos por recorrer
        // xx = posición x inicial
        // yy = posición y inicial
        // d = dirección inicial
        // h = cantidad de veces que se substituye a.
        long N = n;
        int[] r = new int[3];
        r[0]=xx; r[1]=yy; r[2]=d;
        //si N = 0, nada que hacer.
        if(N == 0){return r;}
        //si N = c[h], se avanza todo lo que está guardado en xa[h],ya[h].
        if(N == c[h]){
            rot(xa[h],ya[h],r[2]); r[0]+=x; r[1]+=y; r[2]=(r[2]+dira[h])%4;
            return r;
        }
        //a -> aRbFR
        //si no, se aplica la substitución
        int k = h-1;
        //si la solución está contenida en la subparte a, trabajar ahí
        if(N < c[k]){return reca(n,xx,yy,d,k);}
        //si no, sumar el aporte de avanzar a[k] y rotar a al derecha.
        N-=c[k];
        rot(xa[k],ya[k],r[2]);
        r[0]+=x; r[1]+=y; r[2]=(r[2]+dira[k]+1)%4;
        //devolver el aporte de hacer b.
        return recb(N,r[0],r[1],r[2],k);
        //no se necesita chequear el FR final, en ese caso se tendría N == c[h].
    }

    public static int[] recb(long n, int xx, int yy, int d, int h){
        //recursión en b: Devuelve la posición y dirección
        // obtenida luego de avanzar N veces partiendo desde b.
        // entrada:
        // N = pasos por recorrer
        // xx = posición x inicial
        // yy = posición y inicial
        // d = dirección inicial
        // h = cantidad de veces que se substituye b.
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
        //si no, se aplica la substitución
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

    static public void rot(int xx, int yy, int dd){
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
}
