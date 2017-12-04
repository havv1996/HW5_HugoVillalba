#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

double Funcion(double R, double M_b,double M_d, double M_h){
	//constantes
	double b_b = 0.2497;
	double b_d = 5.16;
	double a_d = 0.3105;
	double a_h = 64.3;
	

	return (pow(M_b,1.0/2.0)*R)/pow((pow(R,2.0)+pow(b_b,2.0)),3.0/4.0) + (pow(M_d,1.0/2.0)*R)/pow((pow(R,2.0)+pow(b_d+a_d,2.0)),3.0/4.0) + (pow(M_h,1.0/2.0)/pow((pow(R,2.0)+pow(a_h,2.0)),1.0/4.0));
	//printf("%f \n",R);	
	//return M_b*R + M_d;
	

}

double Chi_cuadrado(double *Radios,double *Velocidades, double M_b,double M_d, double M_h){
	double suma =0;
	for (int i=0; i<300; i++){
		double chi_cuadrado = (Velocidades[i]-Funcion(Radios[i],M_b, M_d, M_h))*(Velocidades[i]-Funcion(Radios[i],M_b, M_d, M_h));
		suma += 1./2.*chi_cuadrado;
		
		//printf("%f %f \n",Radios[i],Velocidades[i]);
	}
	//printf("%f \n", exp(-suma/1000));	
        return exp(-suma/1000);
}

int main (void){
	
	FILE *in;
	FILE *inR;
	int var;
	int test;
	int N_datos = 300;
	
	double R;
	double V;	
	double Radios[300];
	double Velocidades[300];
	char TilR[100];
	char TilV[100];

	int N_iteraciones = 100000;
	double Masa_gal = 2.325e17;

	double ini;	
	double primer;
	
	double M_b1;
	double M_d1;
	double M_h1;

	double M_b2;
	double M_d2;
	double M_h2;

	double M_b[N_iteraciones];
	double M_d[N_iteraciones];
	double M_h[N_iteraciones];
	double Chi[N_iteraciones];

	double paso1=100;
	double paso2=100;
	double paso3=100;

	//leer el archivo
	
	in = fopen("RadialVelocities.dat","r");
		
	if(!in){
		printf("problems opening the file %s\n", "RadialVelocities");
		exit(1);
}
	fscanf(in, "%s %s \n", TilR, TilV);
	for (int i=0;i<N_datos;i++){
		fscanf(in,"%lf %lf \n", &R,&V);
		Radios[i]= R;
		Velocidades[i]= V;
		//printf("%f %f \n", Radios[i],Velocidades[i]);
}
	//Metropolis-hastings
	
	srand48(time(NULL));
	M_b1 = 1000;
	M_d1 = 10000;
	M_h1 = 20000;
	
	
	//printf("%f %f %f \n", M_b1,M_d1,M_h1);
	double M_b_max= M_b1;
	double M_d_max= M_d1;
	double M_h_max= M_h1;
	M_b[0]=M_b1;
	M_d[0]=M_d1;
	M_h[0]=M_h1;
	
	inR=fopen("Resultados.dat","w");
	if(!inR){
	printf("problems opening the file %s\n","Resultados");
	exit(1);
	}

	double Chi_cuadrado_max = Chi_cuadrado(Radios,Velocidades, M_b1, M_d1, M_h1);
	Chi[0]=Chi_cuadrado_max;
	for (int i=1;i<N_iteraciones;i++){
					
		if(drand48()<=0.5){
			M_b2 =(paso1*log(drand48()))+M_b[i-1];}
		else{
			M_b2 =(-paso1*log(drand48()))+M_b[i-1];}
		
		if(drand48()<=0.5){
			M_d2 =(paso2*log(drand48()))+M_d[i-1];}
		else{
			M_d2 =(-paso2*log(drand48()))+M_d[i-1];}

		if(drand48()<=0.5){
			M_h2 =(paso3*log(drand48()))+M_h[i-1];}
		else{
			M_h2 =(-paso3*log(drand48()))+M_h[i-1];}
	
		
	double Chi_cuadrado1 = Chi_cuadrado(Radios,Velocidades, M_b[i-1],M_d[i-1],M_h[i-1]);
	double Chi_cuadrado2 = Chi_cuadrado(Radios,Velocidades, M_b2,M_d2,M_h2);
	
	double alpha = Chi_cuadrado2/Chi_cuadrado1;
		
			
	if (alpha>1.0){
		M_b[i]=M_b2;
		M_d[i]=M_d2;
		M_h[i]=M_h2;
		Chi[i]=Chi_cuadrado2;
		if(Chi_cuadrado2>Chi_cuadrado_max){
			M_b_max= M_b2;
			M_d_max= M_d2;
			M_h_max= M_h2;
			Chi_cuadrado_max = Chi_cuadrado2;
		}		
	} 
	else{
		double beta = drand48(); 
		if(beta<alpha){
			M_b[i]=M_b2;
			M_d[i]=M_d2;
			M_h[i]=M_h2;
			Chi[i]=Chi_cuadrado2;
		}

		else{
			M_b[i]=M_b[i-1];
			M_d[i]=M_d[i-1];
			M_h[i]=M_h[i-1];
			Chi[i]=Chi[i-1];
		}

	}
	//printf("%f %f %f \n", M_b[i], M_d[i], M_h[i]);

	
	fprintf(inR,"%f,%f,%f,%f \n", M_b[i], M_d[i], M_h[i], Chi[i]);	
	
}
	printf(" M_b %f \n M_d %f \n M_h %f \n", M_b_max, M_d_max, M_h_max);		
	return 0;

}

