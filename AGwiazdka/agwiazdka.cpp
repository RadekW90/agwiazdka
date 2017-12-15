#include<iostream>
#include<fstream>

using namespace std;

double obliczHeurystyke(short w1, short k1, short w2, short k2) {
	return sqrt((double)((w1 - w2)*(w1 - w2) + (k1 - k2)*(k1 - k2)));
}

int main() {
	ifstream plik;

	const int PUSTY = 0;
	const int LO = 1;
	const int LZ = 2;
	const int DROGA = 3;

	const int BLAD = 0;
	const int LEWO = 1;
	const int PRAWO = 2;
	const int GORA = 3;
	const int DOL = 4;

	short plansza[20][20] = { 0 };
	int droga[20][20] = { 0 };
	double heurystyka[20][20] = { 0.0 };
	double suma[20][20] = { 0.0 };
	short pole_rodzica[20][20] = { 0 };
	int kolejnosc[20][20] = { 0 };
	bool meta = false;
	bool brak_drogi = false;


	plik.open("grid.txt");
	if (plik.is_open()) {

		int licznik = 0;

		short start_w = 0;
		short start_k = 0;

		short koniec_w = 19;
		short koniec_k = 19;

		for (short w = 19; w >= 0; w--)
		{
			for (short k = 0; k < 20; k++) {
				plik >> plansza[w][k];
			}
		}

		for (short w = 0; w < 20; w++) {
			for (short k = 0; k < 20; k++) {
				heurystyka[w][k] = obliczHeurystyke(w, k, koniec_w, koniec_k);
			}
		}

		plansza[start_w][start_k] = LO;
		droga[start_w][start_k] = 0;
		suma[start_w][start_k] = droga[start_w][start_k] + heurystyka[start_w][start_k];
		kolejnosc[start_w][start_k] = licznik;
		licznik++;

		while (!meta && !brak_drogi) {

			double suma_min = 9999999.9;
			short biezacy_w;
			short biezacy_k;
			int numer;

			for (short w = 0; w < 20; w++) {
				for (short k = 0; k < 20; k++) {
					if (plansza[w][k] == LO) {
						if (suma_min > suma[w][k] || (suma_min == suma[w][k] && numer < kolejnosc[w][k])) {
							suma_min = suma[w][k];
							biezacy_w = w;
							biezacy_k = k;
							numer = kolejnosc[w][k];
						}
					}
				}
			}

			if (suma_min == 9999999.9) {
				brak_drogi = true;
				break;
			}
			else if (biezacy_w == koniec_w && biezacy_k == koniec_k) {
				meta = true;
				break;
			}
			else {
				plansza[biezacy_w][biezacy_k] = LZ;

				//dó³*, lewo, góra*, prawo

				if (biezacy_w - 1 >= 0) {
					if (plansza[biezacy_w - 1][biezacy_k] == PUSTY || (plansza[biezacy_w - 1][biezacy_k] == LO && droga[biezacy_w - 1][biezacy_k] > droga[biezacy_w][biezacy_k] + 1)) {
						plansza[biezacy_w - 1][biezacy_k] = LO;
						droga[biezacy_w - 1][biezacy_k] = droga[biezacy_w][biezacy_k] + 1;
						suma[biezacy_w - 1][biezacy_k] = droga[biezacy_w - 1][biezacy_k] + heurystyka[biezacy_w - 1][biezacy_k];
						pole_rodzica[biezacy_w - 1][biezacy_k] = GORA;
						kolejnosc[biezacy_w - 1][biezacy_k] = licznik;
						licznik++;
					}
				}

				if (biezacy_k - 1 >= 0) {
					if (plansza[biezacy_w][biezacy_k - 1] == PUSTY || (plansza[biezacy_w][biezacy_k - 1] == LO && droga[biezacy_w][biezacy_k - 1] > droga[biezacy_w][biezacy_k] + 1)) {
						plansza[biezacy_w][biezacy_k - 1] = LO;
						droga[biezacy_w][biezacy_k - 1] = droga[biezacy_w][biezacy_k] + 1;
						suma[biezacy_w][biezacy_k - 1] = droga[biezacy_w][biezacy_k - 1] + heurystyka[biezacy_w][biezacy_k - 1];
						pole_rodzica[biezacy_w][biezacy_k - 1] = PRAWO;
						kolejnosc[biezacy_w][biezacy_k - 1] = licznik;
						licznik++;
					}
				}

				if (biezacy_w + 1 <= 19) {
					if (plansza[biezacy_w + 1][biezacy_k] == PUSTY || (plansza[biezacy_w + 1][biezacy_k] == LO && droga[biezacy_w + 1][biezacy_k] > droga[biezacy_w][biezacy_k] + 1)) {
						plansza[biezacy_w + 1][biezacy_k] = LO;
						droga[biezacy_w + 1][biezacy_k] = droga[biezacy_w][biezacy_k] + 1;
						suma[biezacy_w + 1][biezacy_k] = droga[biezacy_w + 1][biezacy_k] + heurystyka[biezacy_w + 1][biezacy_k];
						pole_rodzica[biezacy_w + 1][biezacy_k] = DOL;
						kolejnosc[biezacy_w + 1][biezacy_k] = licznik;
						licznik++;
					}
				}

				if (biezacy_k + 1 <= 19) {
					if (plansza[biezacy_w][biezacy_k + 1] == PUSTY || (plansza[biezacy_w][biezacy_k + 1] == LO && droga[biezacy_w][biezacy_k + 1] > droga[biezacy_w][biezacy_k] + 1)) {
						plansza[biezacy_w][biezacy_k + 1] = LO;
						droga[biezacy_w][biezacy_k + 1] = droga[biezacy_w][biezacy_k] + 1;
						suma[biezacy_w][biezacy_k + 1] = droga[biezacy_w][biezacy_k + 1] + heurystyka[biezacy_w][biezacy_k + 1];
						pole_rodzica[biezacy_w][biezacy_k + 1] = LEWO;
						kolejnosc[biezacy_w][biezacy_k + 1] = licznik;
						licznik++;
					}
				}
			}
		}

		if (brak_drogi) {
			cout << "Z punktu poczatkowego do koncowego nie ma drogi." << endl;
		}
		else if (meta) {
			short powrot_w = koniec_w;
			short powrot_k = koniec_k;

			while (powrot_w != start_w || powrot_k != start_k) {
				plansza[powrot_w][powrot_k] = DROGA;
				if (pole_rodzica[powrot_w][powrot_k] == GORA) powrot_w++;
				else if (pole_rodzica[powrot_w][powrot_k] == PRAWO) powrot_k++;
				else if (pole_rodzica[powrot_w][powrot_k] == DOL) powrot_w--;
				else if (pole_rodzica[powrot_w][powrot_k] == LEWO) powrot_k--;
			}
			plansza[start_w][start_k] = DROGA;


			for (short w = 19; w >= 0; w--)
			{
				for (short k = 0; k < 20; k++) {
					if (plansza[w][k] > 2) {
						cout << plansza[w][k] << " ";
					}
					else {
						cout << "  ";
					}
				}

				cout << endl;
			}
		}
	}
	else {
		cout << "Blad podczas otwierania pliku." << endl;
	}

	system("PAUSE");
	return 0;
}