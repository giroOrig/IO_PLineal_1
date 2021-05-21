/* Investigacion Operativa - 2021     */
/*        Girolami - Murcia           */
/* Programacion Lineal - optimizacion */
/* ---------------------------------- */

#include <stdio.h>

void introducirDatos(int *Dim, float Sist[][102]);
void escribirTablaDatos(int Dim, float Sist[][102]);
void resolucion(int Dim, float Sist[][102]);

/*
Pedir datos: 
beneficios-A, costoProduccion1-A, beneficios-B, costoProduccion1-B
beneficios-A=40; beneficios-B=30;
costoProduccion1-A=1;(espacio) costoProduccion2-A=2; (tiempo)
costoProduccion1-B=1;(espacio) costoProduccion2-B=1; (tiempo)
pedir restricciones: 
restriccion1, restriccion2, etc…
restriccion1=480; (espacio)
restriccion2=800; (tiempo)
restriccion3= x ≥ 0;
restriccion4= y ≥ 0;
*/

void introducirDatos(int *Dim,float Sist[][102])
{
	int A,B;
	printf("\n\n\n Cantidad de elementos a optimizar:");
	scanf("%d",&*Dim);
    printf("\n\n MATRIZ:\n");
    for(A=1;A<=*Dim;A++) for(B=1;B<=*Dim;B++){
        printf("\n Terminos(%d,%d):",A,B); scanf("%f",&Sist[A][B]);}
	printf("\n\n\n Elementos Disponibles:\n");
    for(A=1;A<=*Dim;A++){
        printf("\n Terminos(%d):",A);scanf("%f",&Sist[A][*Dim+1]);
    }}

void escribirTablaDatos(int Dim, float Sist[][102])
{
    int A,B;
    for(A=1;A<=Dim;A++){
        for(B=1;B<=(Dim+1);B++){
            printf("%7.2f",Sist[A][B]);
            if(B==Dim) printf("   |");}
		printf("\n");
    }}
/*
asociamos a X el beneficios-A 
asociamos a Y el beneficios-B
obtenemos función objetivo f(x,y)=beneficios-A*x +beneficios-B*y
f=40x+30y
generamos funciones a partir de las restricciones que conocemos y los costosProduccion
f1= costoProduccion1-A + costoProduccion1-B < restriccion1
f2=costoProduccion2-A + costoProduccion2-B  < restriccion2
f1= 1x+1y < 480
f2= 2x+y < 800
Conseguir vértices 
V1 = al origen basado en restricciones
V1= (0,0)
V2=sustituir en f1 con x = 0;
V2= y=480 -> V2 = (0,480)
V3= sustituir f2 con y = 0;
V3 = 2x = 800 -> x = 400 -> V3 = (400,0);
V4 o punto critico: se unen f1 y f2, se despeja una variable y se reemplaza para conseguir valores de X e Y
X+ y =480 -> x = 480 - y
2x + y = 800  
2(480 – y ) + y = 800 -> 960 -2y + y = 800 -> y = 160 
X= 480 – 160 -> x = 320
V4= (320,160)
Teniendo los cuatro vértices, se reemplazan los valores en la función objetivo y se ve cual da un máximo
Función objetivo = f = 40x + 30y
V1= (0,0) = 0
V2 = (0,480) = 14400
V3 = (400,0); = 16000
V4= (320,160) = 12800 + 4800 = 17600
Analizar cual es el resultado mas grande y devolverlo como solución ( f = 40*320 + 30*160 -> f = 17600)
*/
void resolucion(int Dim, float Sist[][102])
{
    int NoCero,Col,C1,C2,A;
	float Pivote,V1;

    for(Col=1;Col<=Dim;Col++){
        NoCero=0;A=Col;
        while(NoCero==0){
            if(Sist[A][Col]!=0){
				NoCero=1;}
            else A++;}
        Pivote=Sist[A][Col];
        for(C1=1;C1<=(Dim+1);C1++){
            V1=Sist[A][C1];
            Sist[A][C1]=Sist[Col][C1];
			Sist[Col][C1]=V1/Pivote;}
        for(C2=Col+1;C2<=Dim;C2++){
            V1=Sist[C2][Col];
            for(C1=Col;C1<=(Dim+1);C1++){
                Sist[C2][C1]=Sist[C2][C1]-V1*Sist[Col][C1];}
    }}

    for(Col=Dim;Col>=1;Col--) for(C1=(Col-1);C1>=1;C1--){
        Sist[C1][Dim+1]=Sist[C1][Dim+1]-Sist[C1][Col]*Sist[Col][Dim+1];
        Sist[C1][Col]=0;
	}
}

int main(void)
{
    int C,Dimension;
    float Sistema[101][102];
    introducirDatos(&Dimension,Sistema);
    printf("\n\n\nLa tabla es el siguiente: \n\n");
    escribirTablaDatos(Dimension,Sistema);
    resolucion(Dimension,Sistema);
    printf("\n\n\nLas soluciones son:\n");
    for(C=1;C<=Dimension;C++) printf("\n X%d=%f\n",C,Sistema[C][Dimension+1]);

    scanf("");
    scanf ("  ");
    return(0);
}
