#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <algorithm>
#include <math.h>

using namespace std;

const double EPS0 = 0.01; // dok³adnoœæ porównania z zerem
const double EPSX = 0.0000000001; // dok³adnoœæ wyznaczenia pierwiastka

double f(double x)
{
	//return cos(pow(x, 3)-2*x);
	//return pow(x, 5) - 8 * pow(x, 3) + 2 * pow(x, 2) - 1;
	return -pow(x, 2) - 3 * x;
}

double fp(double (*f)(double x), double x)
{
	return (f(x + EPSX) - f(x)) / EPSX;
}


void bisekcja(double (*f)(double x), double a, double b, double k)
{
	cout << "Metoda bisekcji" << endl;
	double x0 = 0;
	cout << setw(10) << "a" << setw(10) << "b" << setw(15) << "f(a)" << setw(15) << "f(b)" << setw(10) << "x0" << setw(15) << "f(x0)" << setw(22) << "f(a)*f(x0)" << endl;

	
	if (f(a) * f(b) < 0)
	{
		for (int i = 0; i < k; i++)
		{
			x0 = (a + b) / 2;
			cout << i + 1 << setw(10) << a << setw(10) << b << setw(15) << f(a) << setw(15) << f(b) << setw(10) << x0 << setw(15) << f(x0) << setw(20) << f(a) * f(x0) << endl;
			
			if (abs(f(x0)) < EPS0)
				return;
			else
			{
				if (f(a) * f(x0) < 0)
					b = x0;
				else
					a = x0;
			}
		}
	}
	else
		cout << "Funkcja nie posiada pierwiastka" << endl;
}

void regula_falsi(double (*f)(double x), double a, double b, int k)
{
	cout << endl << endl;
	cout << "Regula falsi" << endl;
	cout << setw(10) << "a" << setw(10) << "b" << setw(15) << "f(a)" << setw(15) << "f(b)" << setw(10) << "x0" << setw(15) << "f(x0)" << setw(22) << "f(a)*f(x0)" << endl;

	for (int i = 0; i < k; i++)
	{
		double x1 = a - (f(a) * (b - a)) / (f(b) - f(a));
		cout << i+1 << setw(10) << a << setw(10) << b << setw(15) << f(a) << setw(15) << f(b) << setw(10) << x1 << setw(15) << f(x1) << setw(20)<< f(a) * f(x1) << endl;
		
		if(abs(f(x1))<EPS0)
			break;

		if (f(x1) * f(a) < 0)
			b = x1;
		else
			a = x1;
	}
}


int main()
{
	//x^5 a=-2, b=1, x0=1
	//x^2 a=-2, b=1, x0=1
	bisekcja(f, -2, 1, 100);
	//x^5, x0=0.5
	//x^2 ,x0=1
	regula_falsi(f, -2, 1, 100);

	return 0;
}