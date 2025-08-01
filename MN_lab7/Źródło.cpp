#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

double funkcja(double x)
{
	return x * x + 2 * x + 5;
}

void metoda_prostokatow(double f(double x), double a, double b, double n)
{
	string wf = "x*x + 2 * x + 5";
	//string wf = "sin(x)";
	//string wf = "exp(x)";
	//metoda prostokatow
	vector<double> XP;
	XP.resize(n);
	double s = (b - a) / n;
	for (int i = 0; i < n; i++)
	{
		XP[i] = a + i * s;
	}
	double temp = 0;
	for (int i = 0; i < n; i++)
	{
		temp += f(XP[i] + 0.5 * s);
	}
	double wynik = s * temp;
	cout << "Metoda prostokatow " << endl;
	cout << "Wzor: " << wf << endl;
	//cout << "n-1" << endl << "--" << endl  << ">" << " f(xi + 1/2s)" << endl << "--" << endl << "i=0" << endl;
	cout << "Przedzial calkowania: <" << a << ";" << b << ">" << endl;
	cout << "Liczba przedzialow: " << n << endl;
	cout << "Wynik metoda prostokatow: " << wynik << endl;
}

void metoda_trapezow(double f(double x), double a, double b, double n)
{
	string wf = "x*x + 2 * x + 5";
	//string wf = "sin(x)";
	//string wf = "exp(x)";
	//metoda trapezow
	vector<double> XT;
	XT.resize(n);
	double s = (b - a) / n;
	for (int i = 0; i < n; i++)
	{
		XT[i] = a + i * s;
	}
	double temp = 0;
	for (int i = 0; i < n; i++)
	{
		temp += ((XT[i] + s - XT[i]) / 2) * (f(XT[i]) + f(XT[i] + s));
	}
	double wynik = temp;
	cout << endl << "Metoda traperow" << endl;
	cout << "Wzor: " << wf << endl;
	//cout << "n-1" << endl << "--" << endl << ">" << " f((x(i+1) - xi)/2 * (f(xi) + f(x(i+1)))" << endl << "--" << endl << "i=0" << endl;
	cout << "Przedzial calkowania: <" << a << ";" << b << ">" << endl;
	cout << "Liczba przedzialow: " << n << endl;
	cout << "Wynik metoda trapezow: " << wynik << endl;
}

void metoda_Simpsona(double f(double x), double a, double b, double n)
{
	string wf = "x*x + 2 * x + 5";
	//string wf = "sin(x)";
	//string wf = "exp(x)";
	//metoda simpsona
	vector<double> XS;
	XS.resize(n);
	double s = (b - a) / n;
	for (int i = 0; i < n; i++)
	{
		XS[i] = a + i * s;
	}
	double temp = 0;
	for (int i = 0; i < n; i++)
	{
		temp += ((XS[i] + s - XS[i]) / 6) * (f(XS[i]) + 4 * f((XS[i] + XS[i] + s) / 2) + f(XS[i] + s));
	}
	double wynik = temp;
	cout << endl << "Metoda Simpsona" << endl;
	cout << "Wzor: " << wf << endl;
	//cout << "n-1" << endl << "--" << endl << ">" << " f((x(i+1) - xi)/6 * (f(xi) + 4*f((xi + x(i+1))/2) + f(x(i+1))" << endl << "--" << endl << "i=0" << endl;
	cout << "Przedzial calkowania: <" << a << ";" << b << ">" << endl;
	cout << "Liczba przedzialow: " << n << endl;
	cout << "Wynik metoda Simpsona: " << wynik << endl;
}

int main()
{
	metoda_prostokatow(funkcja, 0.5, 5, 20);
	metoda_trapezow(funkcja, 0.5, 5, 20);
	metoda_Simpsona(funkcja, 0.5, 5, 20);

	return 0;
}