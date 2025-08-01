#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

double funkcja(double x)
{
	return x * x + 2 * x + 5;
}

void kwadratura_Gaussa_Lagendrea(double f(double x), double a, double b, int n)
{
	//string wzor = "sin(x)";
	//string wzor = "exp(x)";
	string wzor = "x*x + 2 * x + 5";
	vector<double> X;
	X.resize(n);
	vector<double> A;
	A.resize(n);
	switch (n)
	{
	case 2:
		X[0] = -sqrt(3) / 3;
		X[1] = sqrt(3) / 3;
		A[0] = A[1] = 1;
		break;
	case 3:
		X[0] = -sqrt(3.0 / 5);
		X[1] = 0;
		X[2] = sqrt(3.0 / 5);
		A[0] = A[2] = 5.0 / 9;
		A[1] = 8.0 / 9;
		break;
	case 4:
		X[0] = -(1.0 / 35) * sqrt(525 + 70 * sqrt(30));
		X[1] = -(1.0 / 35) * sqrt(525 - 70 * sqrt(30));
		X[2] = (1.0 / 35) * sqrt(525 - 70 * sqrt(30));
		X[3] = (1.0 / 35) * sqrt(525 + 70 * sqrt(30));
		A[0] = A[3] = (1.0 / 36) * (18 - sqrt(30));
		A[1] = A[2] = (1.0 / 36) * (18 + sqrt(30));
		break;
	}

	vector<double> T;
	T.resize(n);
	for (int i = 0; i < n; i++)
	{
		T[i] = (a + b) / 2 + ((b - a) / 2) * X[i];
	}

	double temp = 0;
	for (int i = 0; i < n; i++)
	{
		temp += A[i] * f(T[i]);
	}
	double wynik = (b - a) / 2 * temp;

	/*for (int i = 0; i < n; i++)
	{
		cout << "x[" << i << "] = " << X[i] << endl;
	}


	for (int i = 0; i < n; i++)
	{
		cout << "A[" << i << "] = " << A[i] << endl;
	}*/
	cout << "Wzor: " << wzor << endl;
	cout << "Przedzial calkowania: <" << a << ";" << b << ">" << endl;
	cout << "Liczba wezlow kwadratury: " << n << endl;

	cout << endl << "wynik = " << wynik << endl;
}

int main()
{
	kwadratura_Gaussa_Lagendrea(funkcja, 0.5, 5, 4);

	return 0;
}