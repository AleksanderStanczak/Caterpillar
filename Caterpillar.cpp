#include "stdafx.h"
#include <iostream>
using namespace std;
#define GORA 49
#define DOL 50
#define LEWO 51
#define PRAWO 52
#define STRATA_MALE 33
#define STRATA_DUZE 34

struct modul {
	char litera;
	modul *nastepny;
	modul *poprzedni;
};

struct Caterpillar {
	modul *pierwszy;
	modul *ostatni;
	char biezacy_kierunek_ruchu;
	void dodaj_litere_na_koniec(char litera);
	void dodaj_litere_na_poczatek(char litera);
	void usun_z_poczatku();
	void usun_z_konca();
	void wyswietl_Caterpillara(Caterpillar *zbior_modulow);
	int Pozycja_x;
	int Pozycja_y;
};

void Caterpillar::dodaj_litere_na_koniec(char litera)
{
	modul *nowy = new modul;
	nowy->litera = litera;
	nowy->nastepny = NULL;
	nowy->poprzedni = ostatni;
	ostatni->nastepny = nowy;
	ostatni = nowy;
}

void Caterpillar::dodaj_litere_na_poczatek(char litera)
{
	modul *nowy = new modul;
	nowy->litera = litera;
	nowy->nastepny = pierwszy;
	nowy->poprzedni = NULL;
	pierwszy->poprzedni = nowy;
	pierwszy = nowy;
}

void Caterpillar::usun_z_poczatku()
{
	if (pierwszy->nastepny == NULL)
	{
		pierwszy->litera = '#';
	}
	else
	{
		modul *nowy;
		nowy = pierwszy->nastepny;
		delete pierwszy;
		pierwszy = nowy;
		nowy->poprzedni = NULL;
	}
}

void Caterpillar::usun_z_konca()
{
	if (pierwszy->nastepny == NULL)
	{
		pierwszy->litera = '#';
	}
	else
	{
		modul *nowy;
		nowy = ostatni->poprzedni;
		delete ostatni;
		ostatni = nowy;
		nowy->nastepny = NULL;
	}
}

void Caterpillar::wyswietl_Caterpillara(Caterpillar *zbior_modulow)
{
	modul *biezacy = pierwszy;

	cout << zbior_modulow->Pozycja_x << " " << zbior_modulow->Pozycja_y << " ";
	
	while (biezacy)
	{
		if (biezacy->litera >= 65 && biezacy->litera <= 90)
		{
			biezacy->litera += 32;
		}
		cout << biezacy->litera;
		biezacy = biezacy->nastepny;
	}
	cout << endl;
}

void ruch(char kierunek_ruchu, Caterpillar *zbior_modulow, int Xpozycja_na_mapie, int Ypozycja_na_mapie, int n, int m)
{
	switch (kierunek_ruchu)
	{
	case GORA:
		if (Xpozycja_na_mapie == 0)
		{
			zbior_modulow->Pozycja_y = m;
		}
		else
		{
			zbior_modulow->Pozycja_y -= 1;
		}
		zbior_modulow->biezacy_kierunek_ruchu = GORA;
		break;
	case DOL:
		if (Xpozycja_na_mapie == m - 1)
		{
			zbior_modulow->Pozycja_y = 1;
		}
		else
		{
			zbior_modulow->Pozycja_y += 1;
		}
		zbior_modulow->biezacy_kierunek_ruchu = DOL;
		break;
	case LEWO:
		if (Ypozycja_na_mapie == 0)
		{
			zbior_modulow->Pozycja_x = n;
		}
		else
		{
			zbior_modulow->Pozycja_x -= 1;
		}
		zbior_modulow->biezacy_kierunek_ruchu = LEWO;
		break;
	case PRAWO:
		if (Ypozycja_na_mapie == n - 1)
		{
			zbior_modulow->Pozycja_x = 1;
		}
		else
		{
			zbior_modulow->Pozycja_x += 1;
		}
		zbior_modulow->biezacy_kierunek_ruchu = PRAWO;
		break;
	}
}

void wykonaj_runde(Caterpillar *zbior_modulow, unsigned char ** plansza, int n, int m, int licznik_rund)
{
	int Xpozycja_na_mapie = zbior_modulow->Pozycja_y - 1;
	int Ypozycja_na_mapie = zbior_modulow->Pozycja_x - 1;
	char znak_na_mapie = plansza[Xpozycja_na_mapie][Ypozycja_na_mapie];
	if (znak_na_mapie >= GORA && znak_na_mapie <= PRAWO)//poruszanie
	{
		ruch(znak_na_mapie,zbior_modulow,Xpozycja_na_mapie,Ypozycja_na_mapie,n,m);
	}
	else
	{
		if (licznik_rund != 1)
		{
			ruch(zbior_modulow->biezacy_kierunek_ruchu, zbior_modulow, Xpozycja_na_mapie, Ypozycja_na_mapie, n, m);
		}
	}
		//nastąpiła zmiana pola, więc pobieramy współrzędne i znak
		Xpozycja_na_mapie = zbior_modulow->Pozycja_y - 1;
		Ypozycja_na_mapie = zbior_modulow->Pozycja_x - 1;
		znak_na_mapie = plansza[Xpozycja_na_mapie][Ypozycja_na_mapie]; 
		if (znak_na_mapie >= 97 && znak_na_mapie <= 122) // małe litery
		{
			zbior_modulow->dodaj_litere_na_poczatek(znak_na_mapie);
			if (znak_na_mapie == 97)
			{
				plansza[Xpozycja_na_mapie][Ypozycja_na_mapie] = STRATA_MALE;
			}
			else
			{
				plansza[Xpozycja_na_mapie][Ypozycja_na_mapie] = znak_na_mapie - 1;
			}
		}
		else if (znak_na_mapie >= 65 && znak_na_mapie <= 90) // duże litery
		{
			zbior_modulow->dodaj_litere_na_koniec(znak_na_mapie);
			if (znak_na_mapie == 65)
			{
				plansza[Xpozycja_na_mapie][Ypozycja_na_mapie] = STRATA_DUZE;
			}
			else
			{
				plansza[Xpozycja_na_mapie][Ypozycja_na_mapie] = znak_na_mapie - 1;
			}
		}
		else if (znak_na_mapie == STRATA_MALE) 
		{
			zbior_modulow->usun_z_poczatku();
		}
		else if (znak_na_mapie == STRATA_DUZE)
		{
			zbior_modulow->usun_z_konca();
		}
}

int main()
{
	int n, m, c, x, y, d;
	cin >> n >> m >> c; //wczytanie rozmiaru planszy i liczby ruchów
	cin >> x >> y >> d; //wczytanie pozycji Caterpillara i jego długości
	Caterpillar *zbior_modulow = new Caterpillar;
	char litera;
	for (int i = 0; i < d; ++i)
	{
		cin >> litera;
		if (i == 0)
		{
			modul *_pierwszy = new modul;
			_pierwszy->litera = litera;
			_pierwszy->nastepny = NULL;
			_pierwszy->poprzedni = NULL;
			zbior_modulow->pierwszy = _pierwszy;
			zbior_modulow->ostatni = _pierwszy;
		}
		else
		{
			zbior_modulow->dodaj_litere_na_koniec(litera);
		}
	}


	unsigned char ** plansza = new unsigned char *[m];

	for (int i = 0; i < n; i++)
	{
		plansza[i] = new unsigned char[n];
	}
	//wczytanie planszy
	char znak;
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin >> znak;
			plansza[i][j] = znak;
		}
	}
	//Ustawienie Caterpillara
	zbior_modulow->Pozycja_x = x;
	zbior_modulow->Pozycja_y = y;
	zbior_modulow->biezacy_kierunek_ruchu = PRAWO;

	for (int i = 0; i < c; i++)
	{
		wykonaj_runde(zbior_modulow, plansza, n, m,i+1);
		if (zbior_modulow->pierwszy->litera == '#')
		{
			i = c;
		}
	}

	zbior_modulow->wyswietl_Caterpillara(zbior_modulow);

	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (plansza[i][j] == STRATA_DUZE || plansza[i][j] == STRATA_MALE)
			{
				plansza[i][j] = '@';
			}
		}
	}

	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << plansza[i][j];
		}
		cout << endl;
	}

	system("pause");
	return 0;
}

