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

	for (int i = 0; i < rozmiar; i++)
	{
		double temp = 0;
		for (int j = 0; j < rozmiar; j++)
		{
			if (j != i)
				temp += abs(M[i][j]);
		}
		if (abs(M[i][i] > temp))
		{
			if (abs(M[i][i]) >= temp) 	
			{
				cout << "Macierz jest diagonalnie slabo dominujaca" << endl;
			}
			else
				cout << "Macierz nie jest diagonalnie slabo dominujaca" << endl;
		}
		else
			cout << "Macierz nie jest diagonalnie slabo dominujaca" << endl;
	}

	czytaj.close();

	return M;
}

void metoda_Jacobiego(string n_plik)
{
	int rozmiar = rozmiar_tab(n_plik);
	vector<vector<double>> M = plik(n_plik);
	int a = M[0].size();	//ilosc znaków w wierszu

	vector<vector<double>> L;
	L.resize(rozmiar, vector<double>(a));
	vector<vector<double>> U;
	U.resize(rozmiar, vector<double>(a));
	for (int i = 0; i < rozmiar; i++)		
	{
		for (int j = 0; j < rozmiar; j++)
		{
			L[i][j] = 0;
			U[i][j] = 0;
		}
	}

	for (int i = 0; i < rozmiar; i++)
	{
		for (int j = 0; j < rozmiar; j++)
		{
			if (i < j)
				U[i][j] = M[i][j];
			else if (i > j)
				L[i][j] = M[i][j];
		}
	}

	vector<vector<double>> LU;
	LU.resize(rozmiar, vector<double>(a));
	for (int i = 0; i < rozmiar; i++)
	{
		for (int j = 0; j < a; j++)
		{
			LU[i][j] = U[i][j] + L[i][j];
		}
	}

	//macierz L+U
	cout << endl << "Macierz L+U" << endl;
	for (int i = 0; i < M.size(); i++)
	{
		for (int j = 0; j < M[i].size() - 1; j++)
			cout << setw(11) << left << LU[i][j];
		cout << endl;
	}

	vector<vector<double>> D;
	D.resize(rozmiar, vector<double>(a));
	for (int i = 0; i < rozmiar; i++)
	{
		D[i][i] = 1/M[i][i];
	}

	cout << endl << "Macierz diagonalna odwrotna" << endl;
	for (int i = 0; i < M.size(); i++)
	{
		for (int j = 0; j < M[i].size() - 1; j++)
			cout << setw(11) << left << D[i][j];
		cout << endl;
	}

	// wektor B
	vector<double> B;
	B.resize(rozmiar);
	for (int i = 0; i < rozmiar; i++)
	{
		B[i] = M[i][a - 1];		//wypelnienie wektora B wolnymi elementami
	}

	vector<double> X(rozmiar, 0);
	vector<double> X2(rozmiar, 0);
	for (int k = 0; k < 5; k++)
	{
		for (int i = 0; i < rozmiar; i++)
		{
			double temp = 0;
			for (int j = 0; j < rozmiar; j++)
			{
				if (j != i)
					temp += (L[i][j] + U[i][j]) * X[j];
			}
			X2[i] = -D[i][i] * temp + D[i][i] * B[i];
		}
		X = X2;
		if (k == 4)
		{
			cout << endl << "Po " << k + 1 << " iteracjach" << endl;
			for (int i = 0; i < rozmiar; i++)
			{
				cout << "x[" << i << "]: " << X[i] << endl;
			}
		}
	}
}

void metoda_Jacobiego_stop(string n_plik)
{
	int rozmiar = rozmiar_tab(n_plik);
	vector<vector<double>> M = plik(n_plik);
	int a = M[0].size();	//ilosc znaków w wierszu

	vector<vector<double>> L;
	L.resize(rozmiar, vector<double>(a));
	vector<vector<double>> U;
	U.resize(rozmiar, vector<double>(a));
	for (int i = 0; i < rozmiar; i++)		//wypelnianie macierzy U 0 a L 0 z 1 na przekatnej diagonalnej
	{
		for (int j = 0; j < rozmiar; j++)
		{
			L[i][j] = 0;
			U[i][j] = 0;
		}
	}

	for (int i = 0; i < rozmiar; i++)
	{
		for (int j = 0; j < rozmiar; j++)
		{
			if (i < j)
				U[i][j] = M[i][j];
			else if (i > j)
				L[i][j] = M[i][j];
		}
	}

	vector<vector<double>> LU;
	LU.resize(rozmiar, vector<double>(a));
	for (int i = 0; i < rozmiar; i++)
	{
		for (int j = 0; j < a; j++)
		{
			LU[i][j] = U[i][j] + L[i][j];
		}
	}

	//macierz L+U
	cout << endl << "Macierz L+U" << endl;
	for (int i = 0; i < M.size(); i++)
	{
		for (int j = 0; j < M[i].size() - 1; j++)
			cout << setw(11) << left << LU[i][j];
		cout << endl;
	}

	vector<vector<double>> D;
	D.resize(rozmiar, vector<double>(a));
	for (int i = 0; i < rozmiar; i++)
	{
		D[i][i] = 1 / M[i][i];
	}

	cout << endl << "Macierz diagonalna odwrotna" << endl;
	for (int i = 0; i < M.size(); i++)
	{
		for (int j = 0; j < M[i].size() - 1; j++)
			cout << setw(11) << left << D[i][j];
		cout << endl;
	}

	// wektor B
	vector<double> B;
	B.resize(rozmiar);
	for (int i = 0; i < rozmiar; i++)
	{
		B[i] = M[i][a - 1];		//wypelnienie wektora B wolnymi elementami
	}

	vector<double> X(rozmiar, 0);
	vector<double> X2(rozmiar, 0);
	int max_lit = 90;
	double eps = 0.001;
	for (int k = 0; k < max_lit + 1; k++)
	{
		int x = 0;
		for (int i = 0; i < rozmiar; i++)
		{
			double temp = 0;
			for (int j = 0; j < rozmiar; j++)
			{
				if (j != i)
					temp += (L[i][j] + U[i][j]) * X[j];
			}
			X2[i] = -D[i][i] * temp + D[i][i] * B[i];
		}

		for (int i = 0; i < rozmiar; i++)
		{
			cout << endl << "Wartosc bledu dla x[" << i << "]=" << abs(X2[i] - X[i]) << " po " << k + 1 << " iteracji" << endl;
			if (abs(X2[i] - X[i]) < eps)
			{
				x++;
				if (x == X.size())
					goto exit;
			}
		}

		X = X2;
		exit:
		if (k == max_lit || x == X.size())
		{
			cout << endl << "Wartosc bledu: " << eps << endl;

			cout << endl << "Po " << k + 1 << " iteracjach" << endl;
			for (int i = 0; i < rozmiar; i++)
			{
				cout << "x[" << i << "]: " << X[i] << endl;
			}
			return;
		}	
	}
}

int main()
{
	//metoda_Jacobiego("RURL_Jacobi_dane1.txt");
	metoda_Jacobiego_stop("RURL_Jacobi_dane1.txt");


	return 0;
}