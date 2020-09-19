#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>


enum RESULT
{
	INF = -1,
	FALSE = 0,
	TRUE = 1,
	NOROOTS = -2
};


const double precision = 1e-5;


void Input(double* coeff_mass)
{
	assert(coeff_mass);

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


char zero_compare(double num)
{
	union { 
		double doub;
		long long ll;
	};
	doub = num;

	int res = (ll & (long long) 0xfff << 52 ) >> 52;
	if (res == 0x0 || res == 0x8000)
		return 1;

	return 0;
}


char LinearEqSolver(double* roots, double a, double b)
{
	printf("It is a Linear eq.");
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
	
	if(zero_compare(a))
		return LinearEqSolver(roots, b, c);

	if(zero_compare(b))  
	{	
		if(zero_compare(c)) 
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
			break;
	}
}


int main()
{

	double* coeff_mass = new double[3];
	double* roots = new double[2];
	Input(coeff_mass);
	PrintResult(roots, coeff_mass);

	delete[] coeff_mass;
	delete[] roots;
	return 0;
}