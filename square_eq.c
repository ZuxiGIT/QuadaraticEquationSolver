#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define INF -1
#define FALSE 	 0
#define TRUE	 1
#define NOROOTS	 -2

const double precision = 1e-5;


void Input(double* coeff_mass)
{

	char buff_char = '0';

	for(int i = 0; i < 3; i ++)
	{
		printf("Enter the %d coeff, plz\n", i + 1);	
		while(scanf("%lg", (coeff_mass + i)) == 0 || (buff_char = getchar()) == ',')
		{
			printf("Wrong number, try again\n");
			if(buff_char == ',')
				printf("Plz use point instead comma\n");

			while((buff_char = getchar()) != '\n');   // try to empty input buffer
		}
		buff_char = '0';
	}
}


char Compare_Doubles(double num1, double num2)
{
	if(num1 - num2 > -1 * precision && num1 - num2 < precision)
		return TRUE;
	else
		return FALSE;
}

char LinearEqSolver(double* roots, double a, double b)
{

	double* x1 = roots;
	double* x2 = roots + 1;

	*x2 = NAN;

	if(Compare_Doubles(a, 0.))
		if(Compare_Doubles(b, 0.))
			return INF;
		else
			return NOROOTS;
	else
		{
			*x1 = -b / a;
			if(Compare_Doubles(*x1, 0.))
				*x1 = 0;
			return 1;
		}
	
}
char SquareEqSolver(double* roots, double a, double b, double c)
{
	double* x1 = roots;
	double* x2 = roots + 1;
	
	if(Compare_Doubles(a, 0.))
		return LinearEqSolver(roots, b, c);

	if(Compare_Doubles(b, 0.))  
	{	

		if(Compare_Doubles(c, 0.)) 
		{
			*x1 = *x2 = 0;
			return 1;
		}
		if (a*c < 0)
		{
			*x1 = - c / a;
			*x1 = - *x2;
			return 2;
		}
		return NOROOTS;

	}
	
	double discr = b*b - 4*a*c;
	
	if(discr < 0)
		return NOROOTS;

	double sqrt_disc = sqrt(discr);
	*x1 = (-b + sqrt_disc)/(2*a);
	*x2 = (-b - sqrt_disc)/(2*a);
	
	if(*x1 == *x2)
		return 1;
	return 2;
}

void PrintResult(double* roots, double* coeff_mass)
{
	switch(SquareEqSolver(roots, coeff_mass[0], coeff_mass[1], coeff_mass[2]))
	{
		case INF:
			printf("This eq has infinity roots\n");
			break;
		case NOROOTS:
			printf("This eq has no roots\n");
			break;
		case 1:
			printf("This eq has 1 root %lg\n", roots[0]);
			break;
		case 2:
			printf("This eq has 2 roots %lg and %lg\n", roots[0], roots[1]);
	}
}
int main()
{

	double* coeff_mass = (double*)calloc(3, sizeof(double));
	double* roots = (double*)calloc(2, sizeof(double));
	Input(coeff_mass);
	PrintResult(roots, coeff_mass);
	return 0;
}