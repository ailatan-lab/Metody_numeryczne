#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <algorithm>
#include <math.h>

using namespace std;

const double EPS0 = 0.0000000001; // dok³adnoœæ porównania z zerem
const double EPSX = 0.0000000001; // dok³adnoœæ wyznaczenia pierwiastka

double f(double x)
{
	//return -1 * x * x * x + 10 * x + 5;
	//return pow(x, 5) - 8 * pow(x, 3) + 2 * pow(x, 2) - 1;
	return -pow(x, 2) - 3 * x;
}

double fp(double (*f)(double x), double x)
{
	return (f(x + EPSX) - f(x)) / EPSX;
}


void metoda_stycznych(double (*f)(double x), double a, double b, double k, double x0)
{
	cout << "Metoda stycznych" << endl << endl;
	vector<double> X(k + 1);
	X[0] = x0;
	int max_i = 0;
	if (f(a) * f(b) < 0)	
	{
		for (int i = 0; i < k+1; i++)
		{
			if (i + 1 <= k)
			{
				max_i++;
				X[i + 1] = X[i] - f(X[i]) / fp(f, X[i]);
				
				if (abs(f(X[i + 1])) < EPS0)
					break;

			}
		}
	}
	X.erase(X.begin());
	max_i -= 1;

	if (abs(f(X[max_i])) > EPS0)
	{
		cout << "Nie znaleziono miejsca zerowego w " << k << " iteracjach" << endl << endl;
	}

	vector<double> F(max_i+1);
	for (int i = 0; i < max_i+1; i++)
	{
		F[i] = f(X[i]);
	}

	for(int i = 0; i < max_i+1; i++)
	{
		cout << "x[" << i << "] = " << X[i] << setw(10) << "f(x[" << i << "]) = " << F[i] << endl;
	}

	if((abs(f(X[max_i])) < EPS0))
		cout << endl << "Miejsce zerowe: x[" << max_i << "] = " << X[max_i] << setw(10) << "f(x[" << max_i << "]) = " << f(X[max_i]) << endl;
}

void metoda_siecznych(double (*f)(double x), double x0, int k)
{
	cout << endl << endl<< "Metoda siecznych" << endl;
	k += 1;
	double x_1 = x0 - 0.1;
	vector<double> F_prim(k);
	vector<double> X(k+2);
	X[0] = x_1;
	X[1] = x0;
	int max_i = 0;
	for (int i = 1; i < k; i++)
	{
		if (i <= k)
		{
			max_i++;
			X[i + 1] = X[i] - f(X[i]) * ((X[i] - X[i - 1]) / (f(X[i]) - f(X[i - 1])));
			
			if (abs(f(X[i + 1])) < EPS0)
				break;
		}
	}

	X.erase(X.begin());
	X.erase(X.begin());

	if (abs(f(X[max_i-1])) > EPS0)
	{
		cout << endl << "Nie znaleziono miejsca zerowego w " << k-1 <<" iteracjach" << endl;
	}

	vector<double> F(max_i);
	for (int i = 0; i < max_i; i++)
	{
		F[i] = f(X[i]);
	}
	cout << endl;
	for (int i = 0; i < max_i; i++)
	{
		cout << "x[" << i << "] = " << X[i] << setw(10) << "f(x[" << i << "]) = " << F[i] << endl;
	}

	if ((abs(f(X[max_i - 1])) < EPS0))
		cout << endl << "Miejsce zerowe: x[" << max_i-1 << "] = " << X[max_i-1] << setw(10) << "f(x[" << max_i-1 << "]) = " << f(X[max_i-1]) << endl;
}


int main()
{
	//x^5 a=-2, b=1, x0=1
	//x^2 a=-2, b=1, x0=1
	metoda_stycznych(f, -2, 1, 10, 1);
	//x^5, x0=0.5
	//x^2 ,x0=1
	metoda_siecznych(f, 1, 10);

	return 0;
}