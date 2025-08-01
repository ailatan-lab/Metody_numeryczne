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
			cout << "Wystapienie 0 na przekatnej macierzy, nie mozna rozwiazac ukladu rownan za pomoca eliminacji Gaussa" << endl;
			exit(0);
		}
	}
	czytaj.close();

	return M;
}

void eliminacja_Gaussa_wybor_czesciowy(string n_plik)
{
	cout << "Wybor czesciowy - zamiana po wierszach" << endl;

	int rozmiar = rozmiar_tab(n_plik);
	vector<vector<double>> M = plik(n_plik);

	// Metoda eliminacji Gaussa
	int a = M[0].size();	//ilosc znaków w wierszu

	int roz = rozmiar;
	//postepowanie proste
	//zamiana wierszy
	for (int i = 0, k = 1; i < a; i++, k++) //kolumny
	{
		for (int j = 1; j < a - 1; j++) //wiersze
		{
			if ((j > i) && (abs(M[j][i]) > abs(M[i][i])))
			{
				for (int k = 0; k < a; k++) //kolumny	//zamiana wierszy
				{
					double temp = 0;
					temp = M[i][k];
					M[i][k] = M[j][k];
					M[j][k] = temp;
				}
			}	
		}
		//zerowanie wierszy
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

	cout << endl << "Macierz rozszerzona - postepowanie proste " << endl;
	for (int i = 0; i < M.size(); i++)
	{
		for (int j = 0; j < M[i].size(); j++)
			cout << setw(11) << left << M[i][j];
		cout << endl;
	}


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

	cout << endl << "Rozwiazanie ukladu rownan " << endl;
	for (int i = 0, j = rozmiar - 1; i < rozmiar; i++, j--)
	{
		cout << "x[" << i << "] = " << xi[j] << endl;
	}
}

void eliminacja_Gaussa_Crouta(string n_plik)
{
	cout << endl << endl << "Eliminacjia Gaussa-Crouta" << endl;

	int rozmiar = rozmiar_tab(n_plik);
	vector<vector<double>> M = plik(n_plik);
	vector<double> X;
	for (int i = 0; i < rozmiar; i++)	//wektor z poczatkowym polo¿eniem kolumn
	{
		X.push_back(i);
	}

	// Metoda eliminacji Gaussa
	int a = M[0].size();	//ilosc znaków w wierszu
	int roz = rozmiar;
	for (int i = 0, k = 1; i < a - 1; i++, k++) //kolumny
	{
		double max = M[i][i];
		int max_i = i;
		for (int k = 0; k < a - 1; k++)		
		{
			if (k > i && abs(M[i][k]) > abs(max))	//szukanie najwiêkszego elementu w wierszu
			{
				max = M[i][k];
				max_i = k;
			}
		}
		if (max != 0)		//zapisanie zamiany kolumn
		{
			int temp = X[i];
			X[i] = X[max_i];
			X[max_i] = temp;
		}
		
		if (max_i > i && abs(M[i][max_i]) > abs(M[i][i]))		//zamiana kolumn
		{
			for (int k = 0; k < a - 1; k++) //wiersze
			{
				double temp = 0;
				temp = M[k][i];
				M[k][i] = M[k][max_i];
				M[k][max_i] = temp;
			}
		}
		
		//zerowanie wierszy
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

	cout << endl << "Macierz rozszerzona - postepowanie proste " << endl;
	for (int i = 0; i < M.size(); i++)
	{
		for (int j = 0; j < M[i].size(); j++)
			cout << setw(11) << left << M[i][j];
		cout << endl;
	}

	cout << endl << "Wektor przechowujacy informacje o numerach kolumn" << endl;
	for (int z = 0; z < a-1; z++)
	{
		cout << "X[" << z << "] =" << X[z] << endl;
	}

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
	reverse(xi.begin(), xi.end());

	cout << endl << "Rozwiazanie ukladu rownan " << endl;
	for (int i = 0; i < rozmiar; i++)
	{
		for (int j = 0; j < rozmiar; j++)
		{
			if (X[j] == i)
			{
				cout << "x[" << i << "] = " << xi[j] << endl;
			}
		}
	}
}

int main()
{
	eliminacja_Gaussa_wybor_czesciowy("RURL_dane2.txt");
	eliminacja_Gaussa_Crouta("RURL_dane2.txt");

	return 0;
}