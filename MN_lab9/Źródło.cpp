#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <algorithm>
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



	cout << endl;
	czytaj.close();

	return M;
}

vector<double> eliminacja_Gaussa(string n_plik, double n)
{
	int rozmiar = rozmiar_tab(n_plik);
	vector<vector<double>> M = plik(n_plik);

	cout << "Uklad rownan" << endl;
	for (int i = 0; i < M.size(); i++)
	{
		for (int j = 0; j < M[i].size(); j++)
			cout << setw(11) << left << M[i][j];
		cout << endl;
	}
	cout << endl;

	// Metoda eliminacji Gaussa
	int a = M[0].size();	//ilosc znaków w wierszu

	// Postêpowanie proste
	int roz = rozmiar;
	for (int i = 0, k = 1; i < a; i++, k++)	//kolumny
	{
		for (int j = 0; j < roz - 1; j++)	//wiersze
		{
			if (M[j + k][i] == 0)
				continue;
			else
			{
				double temp = M[j + k][i];
				for (int l = 1; l < a; l++)
				{
					M[j + k][l] = M[j + k][l] - temp / M[i][i] * M[i][l];

				}
				M[j + k][i] = M[j + k][i] - M[j + k][i] / M[i][i] * M[i][i];
			}
		}
		roz--;
	}

	cout << "Macierz rozszerzona - macierz schodkowa " << endl;
	for (int i = 0; i < M.size(); i++)
	{
		for (int j = 0; j < M[i].size(); j++)
			cout << setw(11) << left << M[i][j];
		cout << endl;
	}
	cout << endl;


	// Postêpowanie odwrotne
	double xn;
	xn = M[rozmiar - 1][a - 1] / M[rozmiar - 1][a - 2];
	vector<double> xi;
	xi.push_back(xn);
	double wynik = 0;
	double temp = 0;
	for (int i = 1; i < rozmiar; i++)	//wiersze
	{
		for (int j = 0; j < i; j++)	//kolumny
		{
			temp += M[rozmiar - i - 1][a - 2 - j] * xi[j];
		}
		wynik = (M[rozmiar - i - 1][a - 1] - temp) / M[rozmiar - i - 1][rozmiar - i - 1];
		xi.push_back(wynik);
		temp = 0;
	}

	cout << "Wspolczynniki wielomianu aproksymujacego: " << endl;
	for (int i = 0, j=n; i < n + 1, j >= 0; i++, j--)
	{
		cout << "a[" << i << "] = " << xi[j] << endl;
	}

	return xi;
}

void interpolacja_1(string n_plik,double n, double w)
{
	int rozmiar = rozmiar_tab(n_plik);
	vector<vector<double>> M = plik(n_plik);
	
	cout << "Wezly interpolacji i wartosci funkcji w wezlach " << endl;

	for (int i = 0; i < M.size(); i++)
	{
		for (int j = 0; j < M[i].size(); j++)
			cout << M[i][j] << '\t';
		cout << endl;
	}

	vector<vector<double>> G;
	G.resize(n + 1);
	for (int i = 0; i < n + 1; i++)
	{
		G[i].resize(n + 1);
	}
	vector<double> F;
	F.resize(n+1);
	for (int k = 0; k < n+1; k++)
	{
		for (int j = 0; j < n+1; j++)
		{
			for (int i = 0; i < rozmiar; i++)
			{
				G[k][j] += pow(M[i][0], k) * pow(M[i][0], j) * w;
			}
		}
		for (int i = 0; i < rozmiar; i++)
		{
			F[k] += pow(M[i][0], k) * M[i][1] * w;
		}
	}

	ofstream wplik("macierz.txt");
	wplik << n + 1 << endl;
	for (int k = 0; k < n + 1; k++)
	{
		for (int j = 0; j < n + 1; j++)
		{
			wplik << G[k][j] << "	";
		}
		wplik << F[k] << '\t' << endl;
	}
	wplik.close();


	cout << "Liczba wezlow: " << rozmiar << endl;
	vector<double> a = eliminacja_Gaussa("macierz.txt", 1);
	reverse(a.begin(), a.end());
	cout << endl << "Podane wezly aproksymacji i wartosci w wezlach oraz obliczone" << endl << "wartosci funkcji aproksymujacej w wezlach aproksymacji" << endl;
	for (int i = 0; i < rozmiar; i++)
	{
		double a_y = 0.0;
		for (int j = 0; j < n + 1; j++)
		{
			a_y += a[j] * pow(M[i][0], j);
		}
		cout << "x: " << M[i][0] << "	y: " << M[i][1] << "		a_y: " << a_y << endl;
	}

	/*for (int i = 0; i < n + 1; i++)
	{
		cout << a[i] << endl;
	}*/
}



int main()
{
	interpolacja_1("MN_a.txt",1 , 1);
	return 0;
}