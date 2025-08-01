#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <cmath>
using namespace std;

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

	cout << endl << "Macierz rozszerzona " << endl;
	for (int i = 0; i < M.size(); i++)
	{
		for (int j = 0; j < M[i].size(); j++)
			cout << M[i][j] << '\t';
		cout << endl;
		if (M[i][i] == 0)
		{
			cout << "Wystapienie 0 na przekatnej macierzy, nie mozna rozwiazac ukladu rownan" << endl;
			exit(0);
		}
	}
	czytaj.close();

	return M;
}

void rozklad_LU(string n_plik)
{
	int rozmiar = rozmiar_tab(n_plik);		
	vector<vector<double>> M = plik(n_plik);	
	int a = M[0].size();	//ilosc znaków w wierszu

	// rozklad LU
	vector<vector<double>> L;
	L.resize(rozmiar, vector<double>(a));
	vector<vector<double>> U;
	U.resize(rozmiar, vector<double>(a));
	for (int i = 0; i < rozmiar; i++)		//wypelnianie macierzy U 0 a L 0 z 1 na przekatnej diagonalnej
	{
		for (int j = 0; j < rozmiar; j++)
		{
			if (j == i)
				L[i][j] = 1;
			else
				L[i][j] = 0;
			U[i][j] = 0;
		}
	}

	for (int i = 0; i < rozmiar; i++)		//obliczenie elementow macierzy LU
	{
		for (int j = 0; j < rozmiar; j++)
		{
			if (j >= i)
			{
				double tempu = 0;
				for (int k = 0; k < i; k++)
				{
					tempu += L[i][k] * U[k][j];
				}
				U[i][j] = M[i][j] - tempu;
			}
			else
			{
				double templ = 0;
				for (int k = 0; k < j; k++)
				{
					templ += L[i][k] * U[k][j];
				}
				L[i][j] = 1 / U[j][j] * (M[i][j] - templ);
			}
		}
	}

	//macierz L
	cout << endl << "Macierz L" << endl;
	for (int i = 0; i < M.size(); i++)
	{
		for (int j = 0; j < M[i].size() - 1; j++)
			cout << setw(11) << left << L[i][j];
		cout << endl;
	}

	//macierz U
	cout << endl << "Macierz U" << endl;
	for (int i = 0; i < M.size(); i++)
	{
		for (int j = 0; j < M[i].size() - 1; j++)
			cout << setw(11) << left << U[i][j];
		cout << endl;

	}

	for (int i = 0; i < rozmiar - 1; i++)
	{
		if (U[i][i] == 0)
		{
			cout << endl << "Wystapienie 0 na przekatnej macierzy U, nie mozna rozwiazac ukladu rownan" << endl;
			exit(0);
		}
	}

	// wektor B
	vector<double> B;
	B.resize(rozmiar);
	for (int i = 0; i < rozmiar; i++)
	{
		B[i] = M[i][a - 1];		//wypelnienie wektora B wolnymi elementami
	}

	////wektor Y
	vector<double> Y;
	Y.resize(rozmiar);
	Y.push_back(B[0]);
	for (int i = 0; i < rozmiar; i++)
	{
		double tempy = 0;
		for (int j = 0; j < rozmiar - 1; j++)
		{
			tempy += L[i][j] * Y[j];		//we=ypelnienie wektora Y wg wzoru
		}
		Y[i] = B[i] - tempy;
	}

	cout << endl << "Wektor Y" << endl;
	for (int i = 0; i < rozmiar; i++)
	{
		cout << "y[" << i << "] = " << Y[i] << endl;
	}

	//  xn
	vector<double> X;
	X.resize(rozmiar);
	for (int i = rozmiar - 1; i >= 0; i--)
	{
		X[rozmiar - 1] = Y[a - 2] / U[a - 2][a - 2];
		double tempx = 0;	
		for (int j = 1; j < rozmiar; j++)
		{
			tempx += U[i][j] * X[j];
		}
		X[i] = 1 / U[i][i] * ( Y[i] - tempx);
	}

	cout << endl << "Roziazanie ukladu rownan" << endl;
	for (int i = 0; i < rozmiar; i++)
	{
		cout << "x[" << i << "] = " << X[i] << endl;
	}
}


int main()
{
	rozklad_LU("RURL_dane2.txt");

	return 0;
}