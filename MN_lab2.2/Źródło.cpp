#include <iostream>
#include <fstream>
#include <vector>
#include <string>
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

	//interpolaja wielomianowa Newtona
	//pk
	vector<double> PK;
	double pk0 = 1;
	PK.push_back(pk0);
	for (int i = 1; i < rozmiar; i++)
	{
		double pk = 1;
		for (int j = 0; j < i; j++)
		{
			pk *= x - M[j][0];
		}
		PK.push_back(pk);
	}

	//bk
	vector<double> BK;
	vector<double> BKT;
	double bk0 = M[0][1];
	//L2.push_back(bk0);
	vector<double> T;
	for (int j = 0; j < rozmiar - 1; j++)
	{
		double templ = 1;
		double tempm = 1;
		templ *= M[j + 1][1] - M[j][1];
		tempm *= M[j + 1][0] - M[j][0];
		BK.push_back(templ / tempm);
		T.push_back(templ / tempm);
	}
	BKT.push_back(BK[0]);

	int rozmiar2 = rozmiar;
	for (int k = 2; k < rozmiar; k++)
	{
		vector<double> LT;
		for (int i = 0; i < rozmiar2 - 2; i++)
		{
			double templ = 1;
			double tempm = 1;
			templ *= T[i + 1] - T[i];
			tempm *= M[i + k][0] - M[i][0];
			BK.push_back(templ / tempm);
			LT.push_back(templ / tempm);
		}
		BKT.push_back(LT[0]);
		T.clear();
		T = LT;
		LT.clear();
		rozmiar2--;
	}
	BKT.insert(BKT.begin(), bk0);

	// Wn
	double Wn = 0;
	for (int i = 0; i < rozmiar; i++)
	{
		Wn += BKT[i] * PK[i];
	}

	cout << "Liczba wezlow: " << rozmiar << endl;
	cout << "Wartosc wielomianu Newtona w danym punkcie: " << Wn << endl;
	cout << "Wspolczynniki wielomianu Newtona: " << endl;
	for (int i = 0; i < BKT.size(); i++)
	{
		cout << BKT[i] << endl;
	}
	cout << endl;
}


int main()
{
	double x;
	cin >> x;
	cout << "Punkt w ktorym liczymy wartosc wielomianu: " << x << endl;
	interpolacja_1(x, "MN-2-p2.txt");

	return 0;
}