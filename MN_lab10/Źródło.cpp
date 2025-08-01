#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <algorithm>
#include <math.h>
using namespace std;

double funkcja(double x)
{
	return x;
}


int rozmiar_tab(string n_plik)
{
	int rozmiar = 0;

	fstream czytaj;
	czytaj.open(n_plik);
	czytaj >> rozmiar;

	czytaj.close();


	return rozmiar;
}

vector<vector<double>> plik(string n_plik)
{
	int rozmiar = rozmiar_tab(n_plik);

	fstream czytaj;
	czytaj.open(n_plik);
	vector<vector<double>> M;

	string line1, line2;
	int a = 1;
	getline(czytaj, line1);
	if (getline(czytaj, line2))
	{
		int l = line2.length();
		for (int i = 0; i < l - 1; i++)
		{
			if (line2[i] == '\t')
				a++;
		}
	}

	czytaj.close();
	czytaj.open(n_plik);
	getline(czytaj, line1);

	int x = 0, y = 0;
	for (int i = 0; i < rozmiar; i++)
	{
		vector<double> TEMP;
		for (int j = 0; j < a; j++)
		{
			int tym;
			czytaj >> tym;
			TEMP.push_back(tym);
		}
		M.push_back(TEMP);
	}



	cout << endl;
	czytaj.close();

	return M;
}

double dw_Newtona(double n, double k)
{
	double l = 1.0;
	double m = 1.0;
	for (int i = 1; i <= n; i++)
	{
		l *= i;
		if (i <= n - k)
		{
			m *= i;
			if (i <= k)
			{
				m *= i;
			}
		}
	}

	return l/m;
}


double xn(double x, int n)
{
	if (n == 0)
		return 1;
	double iloczyn = 1;
	for (int i = 0; i < n; i++)
	{
		iloczyn *= x - i;
	}
	return iloczyn;
}

double Fnkq(double k, double n, double q)
{
	double suma = 0.0;
	if (q == 0)
		return 1;
	for (int s = 0; s <= k; s++)
	{
		suma += pow((-1), s) * dw_Newtona(k, s) * dw_Newtona(k + s, s) * (xn(q, s) / xn(n-1, s));
	}

	return suma;
}

vector<double> skf(double k, double n)
{
	
	vector<double> SUMA;
	SUMA.resize(k+1);
	for (int j = 0; j <= k; j++)
	{
		double suma = 0;
		for (int i = 0; i < n; i++)
		{
			double F = Fnkq(j, n, i);
			suma += pow(F, 2);
		}
		SUMA[j] = suma;
	}
	return SUMA;
}

vector<double> ckf(double k, double n, vector<double> Y)
{
	vector<double> suma;
	suma.resize(k+1);
	double F;
	for (int i = 0; i <=k; i++)
	{
		for (int j = 0; j < n; j++)
		{
			F = Fnkq(i, n, j);
			suma[i] += Y[j]*F;
		}
	}

	return suma;
}

void Gram(string n_plik, double x, double m)
{
	int rozmiar = rozmiar_tab(n_plik);
	vector<vector<double>> M = plik(n_plik);

	vector<double> Y;
	Y.resize(rozmiar);
	for (int i = 0; i < rozmiar; i++)
	{
		Y[i] = M[i][1];
	}

	double h = M[1][0] - M[0][0];
	double q = (x - M[0][0]) / h;

	vector<double> ck = ckf(m, rozmiar, Y);
	vector<double> sk = skf(m, rozmiar);

	vector<double> Ym;
	Ym.resize(rozmiar);
	for (int i = 0; i < rozmiar; i++)
	{
		double suma = 0.0;
		double q = ( M[i][0] - M[0][0]) / h;

		for (int k = 0; k <= m; k++)
		{
			suma += ck[k] / sk[k] * Fnkq(k, rozmiar, q);
		}
		Ym[i] = suma;
	}

	double suma = 0.0;
	for (int k = 0; k <= m; k++)
	{
		suma += ck[k] / sk[k] * Fnkq(k, rozmiar, q);
	}
	
	cout << "Stopien wielomianu: " << m << endl;
	cout << endl << "Liczba wezlow: " << rozmiar << endl << endl;
	for (int i = 0; i <= m; i++)
	{
		cout << "bk:" <<setw(10) << ck[i]/sk[i] << setw(10) << "ck:" <<setw(10)<< ck[i] << setw(10) << "sk:		" << sk[i] << endl;
	}

	cout << endl << "Podane wezly aproksymacji i wartosci w wezlach oraz obliczone" << endl << "wartosci funkcji aproksymujacej" << endl;
	for (int i = 0; i < rozmiar; i++)
	{
		cout << "x: " << M[i][0] << "	y: " << M[i][1] << "		ym[" << i << "] = " << Ym[i] << endl;
	}
	
	cout <<endl<<"Wartosc funkcja w x = " << x << " : " << suma << endl;
}


int main()
{
	Gram("MN_a.txt", 2.5, 2);
	return 0;
}