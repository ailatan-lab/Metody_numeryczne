#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <vector>
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

vector<vector<int>> plik(string n_plik)
{
	int rozmiar = rozmiar_tab(n_plik);

	fstream czytaj;
	czytaj.open(n_plik);
	vector<vector<int>> M;

	int a = 0;
	string line1, line2;
	getline(czytaj, line1);
	if (getline(czytaj, line2))
	{
		for (char x : line2)
		{
			if (!isspace(x) && x != '-')
				a++;
		}
	}


	czytaj.close();
	czytaj.open(n_plik);
	getline(czytaj, line1);

	int x = 0, y = 0;
	for (int i = 0; i < rozmiar; i++)
	{
		vector<int> TEMP;
		for (int j = 0; j < a; j++)
		{
			int tym;
			czytaj >> tym;
			TEMP.push_back(tym);
		}
		M.push_back(TEMP);
	}

	cout << "Wezly interpolacji i wartosci funkcji w wezlach " << endl;

	for (int i = 0; i < M.size(); i++)
	{
		for (int j = 0; j < M[i].size(); j++)
			cout << M[i][j] << '\t';
		cout << endl;
	}

	czytaj.close();

	return M;
}

void interpolacja_1(double x, string n_plik)
{
	int rozmiar = rozmiar_tab(n_plik);
	vector<vector<int>> M = plik(n_plik);

	//wielomian interpolacyjny Lagrange'a
	vector<double> L;
	for (int i = 0; i < rozmiar; i++)
	{
		double templ = 1;
		double tempm = 1;
		for (int j = 0; j < rozmiar; j++)
		{
			if (i == j)
				continue;

			templ *= x - M[j][0];
			tempm *= M[i][0] - M[j][0];
		}
		L.push_back(templ / tempm);
	}

	//uwzgledniajac wzor 2
	double L3 = 0;
	for (int i = 0; i < rozmiar; i++)
	{
		L3 += M[i][1] * L[i];
	}

	cout << "Liczba wezlow: " << rozmiar << endl;
	cout << "Wartosc wielomianu Lagrange'a w danym punkcie: " << L3 << endl;
}

int main()
{
	double x;
	cin >> x;
	cout << "Punkt w ktorym liczymy wartosc wielomianu: " << x << endl;
	interpolacja_1(x, "MN-1.txt");

	return 0;
}