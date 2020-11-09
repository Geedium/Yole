#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iostream>
#include <string>
#include <new>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <iomanip> 

using namespace std;

class Sinoptik
{
public:
	string vardas;
	double temperatura;
	string kryptis;
	Sinoptik* next;
	//-------------------------------------------------------------
	Sinoptik(string dvardas, double dtemperatura, string dkryptis) : vardas(dvardas), temperatura(dtemperatura), kryptis(dkryptis), next(NULL)
	{}
	//-------------------------------------------------------------
	void displayLink() {
		cout << " vardas: [" << vardas << "] ,temperatura: [" << temperatura << "] " << " kryptis: [" << kryptis << "] ;" << endl;

	} //sąrašo elemento išvedimas
};

////////////////////////////////////////////////////////////////
class FirstLastList
{
private:
	Sinoptik* pFirst; //nuoroda į pirmąjį sąrašo elementą
	Sinoptik* pLast; //nuoroda į paskutinį sąrašo elementą
public:
	//-------------------------------------------------------------
	FirstLastList() : pFirst(NULL), pLast(NULL) //konstruktorius
	{ }
	//-------------------------------------------------------------
	~FirstLastList() //destruktorius
	{ // (ištrina visus sąrašo elementus)
		Sinoptik* pCurrent = pFirst; //pradedama nuo sąrašo pradžios
		while (pCurrent != NULL) //kol pasiekiama sąrašo pabaigą,
		{
			Sinoptik* pTemp = pCurrent; //atsimenamas šalinamas sąrašo elementas
			pCurrent = pCurrent->next; //pereinama prie kito sąrašo elemento
			delete pTemp; //ištrinamas prieš tai atsimintas
		}
	}
	//-------------------------------------------------------------
	bool isEmpty() //gražinama true reikšmė, jeigu sąrašas yra tuščias
	{
		return pFirst == NULL;
	}
	//-------------------------------------------------------------
	void deleteFirst() //pašalinamas pirmasis elementas
	{
		if (!isEmpty())
		{
			Sinoptik* pTemp = pFirst;

			if (pFirst->next == NULL)//jeigu yra tik vienas elementas,
			{
				pLast = NULL; //NULL <-- last, pabaigos rodyklei priskiriame NULL
			}
			pFirst = pFirst->next; //first --> old next
			delete pTemp; //ištrinamas sąrašo elementas

		}
	}
	//-----------------------------------------------------------------------------
	double skirt(double temperaturite) {
		double temp = 0, sk = 0, vid = 0;
		Sinoptik* Temp = pFirst;
		while (Temp != NULL) {
			if (Temp->temperatura != temperaturite) {
				temp = temp + Temp->temperatura;
				sk++;
			}
			Temp = Temp->next;
		}
		temp = temp / sk;
		if (temp > 0) {
			temp = temp + 0.5;
		}
		else {
			temp = temp - 0.5;
		}
		int y = (int)temp;
		if (sk != 0 && y > temperaturite) {
			y = y - temperaturite;
		}
		if (sk != 0 && y < temperaturite && y < 0) {
			y = temperaturite - y;
			y = -y;
		}
		if (sk != 0 && y < temperaturite && y>0) {
			y = y - temperaturite;

		}
		if (sk == 0) {
			y = 0;
		}
		if (y == 0&& sk>0) {
			y = temperaturite - y;
			y = -y;
		}
		return y;
	}
	//------------------------------------------------------------------------------
	void getCountByTemperature(double temperaturite) {
		int count = 0;
		Sinoptik* pCurrent = pFirst;
		Sinoptik* penki = pFirst;
		Sinoptik* current = pFirst;
		Sinoptik* pOld = NULL;
		Sinoptik* vedam = pFirst;

		while (pCurrent != NULL) {
			if (pCurrent->temperatura == temperaturite) {
				count++;
				if (count == 5)
				{
					double skirtumas = skirt(temperaturite);

					while (vedam != NULL) {
						if (vedam->temperatura == temperaturite) {
							cout << "Yra 5 vienodos temperaturos" << endl;
							cout << "---------------------------" << endl;
							cout << "Vardas: " << vedam->vardas << endl;
							cout << "Temperatura: " << vedam->temperatura << endl;
							cout << "Kryptis: " << vedam->kryptis << endl;
							cout << "SKirtumas nuo vidurkio: " << skirtumas << endl;
							cout << "---------------------------" << endl;
						}
						vedam = vedam->next;
					}
					if (skirtumas <= 5 && skirtumas > 0) {
						while (penki != NULL) {
							if (penki->temperatura == temperaturite) {
								penki->temperatura = skirtumas + temperaturite;
								cout << "Yra 5 vienodos temperaturos bet jau pakoreguotos" << endl;
								cout << "---------------------------" << endl;
								cout << "Vardas" << endl;
								cout << penki->vardas << endl;
								cout << "Temperatura" << endl;
								cout << penki->temperatura << endl;
								cout << "Kryptis" << endl;
								cout << penki->kryptis << endl;
								cout << "---------------------------" << endl;
							}
							penki = penki->next;
						}
					}
					else {
						while (current != NULL) {
							if (current->temperatura == temperaturite)
							{
								if (current->next == NULL && pOld == NULL)
								{
									deleteFirst();
									break;
								}
								else if (current->next != NULL && pOld == NULL)
								{
									deleteFirst();
									current = pFirst;
									continue;
								}
								else if (current->next != NULL && pOld != NULL)
								{
									Sinoptik* temp = current;
									current = current->next;
									pOld->next = current;
									free(temp);
									continue;
								}
								else if (current->next == NULL && pOld != NULL)
								{
									free(pOld->next);
									current = NULL;
									pOld->next = current;
									break;
								}
							}
							pOld = current;
							current = current->next;
						}
					}
					if (current == NULL) {
						Sinoptik* pirmas = pFirst;
						if (pirmas == NULL) {
							pLast = pirmas;
						}
						while (pirmas != NULL) {
							pLast = pirmas;
							pirmas = pirmas->next;
						}
					}
					break;
				}
			}
			pCurrent = pCurrent->next;
		}

	}
	//---------------------------------------------------------------------------
	void vidurkis() {
		double temp = 0, sk = 0, vid = 0;
		Sinoptik* Temp = pFirst;
		while (Temp != NULL) {
			temp = fabs(temp + Temp->temperatura);
			sk++;
			Temp = Temp->next;
		}
		vid = temp / sk;
		cout << "Temperaturos vidurkis yra " << vid << endl;


	}

	void vejas() {
		string vkryptis;
		int v = 0;
		int s = 0;
		int p = 0;
		int r = 0;
		Sinoptik* pTemp = pFirst;
		cout << "Nurodykite vejo krypti: Vakarai, Pietus, Rytai, Siaure" << endl;
		cin >> vkryptis;
		if (!(vkryptis == "Vakarai" || vkryptis == "Pietus" || vkryptis == "Rytai" || vkryptis == "Siaure")) {
			cout << "\nBlogai ivesta vejo kryptis";
			cout << "\nGalimos vejo kryptis: Vakarai, Pietus, Rytai, Siaure";
			cout << "\nIveskite vejo krypti:";
			cin >> vkryptis;
		}
		while (pTemp != NULL) {
			if (pTemp->kryptis == "Vakarai") {
				v++;
				pTemp = pTemp->next;
			}
			else if (pTemp->kryptis == "Siaure") {
				s++;
				pTemp = pTemp->next;
			}
			else if (pTemp->kryptis == "Pietus") {
				p++;
				pTemp = pTemp->next;
			}
			else if (pTemp->kryptis == "Rytai") {
				r++;
				pTemp = pTemp->next;
			}
		}
		
		switch(vkryptis)
		{
			case "Vakarai": cout << "\nUz vakarus pasisako: " << v << " zmones"; break;
			case "Siaure": cout << "\nUz siaure  pasisako: " << s << " zmones"; break;
			case "Pietus": cout << "\nUz pietus  pasisako: " << p << " zmones"; break;
			case "Rytai": cout << "\nUz rytus   pasisako: " << r << " zmones"; break;
			default: cout << "nera" << break;
		}

	}
	void insertLast(string ddvardas, double ddtemperatura, string ddkryptis) //įterpimas sąrašo pabaigoje
	{
		Sinoptik* pNewLink = new Sinoptik(ddvardas, ddtemperatura, ddkryptis); //sukuriamas naujas sąrašo elementas (arba duomenų struktūra)

		if (isEmpty()) {//jeigu sąrašas yra tuščias,
			pFirst = pNewLink; //first --> newLink, jeigu sąrašas tusčias, naujam elementui priskiriama pradžios rodyklė
		}
		else {
			pLast->next = pNewLink; //old last --> newLink
		}

		pLast = pNewLink; //newLink <-- last
	}
	//-------------------------------------------------------------


	void displayList()//išvedami visi sąrašo nariai
	{
		cout << "Eile (nuo pradzios --> pabaigos): " << endl;
		Sinoptik* pCurrent = pFirst; //pradedama nuo sąrašo pradžios
		while (pCurrent != NULL) //kol nepasiekiama sąrašo pabaiga,
		{
			pCurrent->displayLink(); //atspausdinami sąrašo nario duomenys
			pCurrent = pCurrent->next; //pereinama prie kito sąrašo nario
		}
		cout << endl;

	}
	//-------------------------------------------------------------
	void insert() //naujo sąrašo nario įterpimas eilės pabaigoje
	{
		string i;
		double j;
		string k;
		cout << "Nurodykite sinoptiko varda" << endl;
		getchar();
		getline(cin, i);
		cout << "Nurodykite temperatura" << endl;
		cin >> j;



		cout << "Nurodykite vejo krypti: Vakarai, Pietus, Rytai, Siaure" << endl;
		cin >> k;
		if (!(k == "Vakarai" || k == "Pietus" || k == "Rytai" || k == "Siaure")) {
			cout << "\nBlogai ivesta vejo kryptis";
			cout << "\nGalimos vejo kryptis: Vakarai, Pietus, Rytai, Siaure";
			cout << "\nIveskite vejo krypti:";
			cin >> k;
		}
		insertLast(i, j, k);
		getCountByTemperature(j);
	}; //klasės FirstLastList pabaiga

};


void meniuTurinys() {
	cout << "===============================================================" << endl;
	cout << "Sinoptikai-----------------------------------------------------" << endl;
	cout << "---------------------------------------------------------------" << endl;
	cout << "Pasirinkite norima atlikti operacija---------------------------" << endl;
	cout << "---------------------------------------------------------------" << endl;
	cout << " [1] Naujos oro prognozes registravimas.                       " << endl;
	cout << " [2] Visu oro prognoziu isvedimas;                             " << endl;
	cout << " [3] Konkrecios vejo krypties prognoziu isvedimas, pateikiant skaiciu kiek sinoptiku uz tokia vejo krypti pasisako" << endl;
	cout << " [4] Oro prognozes paskelbimas: isvedami vidurkiai.            " << endl;
	cout << " [5] Baigti darba su Sinoptikai sistema.                       " << endl;
	cout << "================================================================" << endl;

}

void meniu(int* pas) {
	char lpas;
	meniuTurinys();

	do {
		lpas = getchar();
		if ((isdigit(lpas) == false) && (lpas != '\n')) {
			cout << "Privalote nurodyti skaiciu... [!]" << endl;
			cout << "Bandykite dar karta:" << endl;
			meniuTurinys();
		}
	} while (isdigit((unsigned char)lpas) == false);
	*pas = (int)lpas - '0';
}

int main()
{
	int pas;
	FirstLastList theQueue;

	do {
		meniu(&pas);
		switch (pas) {
		case 1:
			cout << "Pasirinkimas [1]" << endl;
			theQueue.insert();
			cout << endl;
			cout << "Registravimas atliktas sekmingai, spauskite bet kuri klavisa [info]..." << endl;
			getchar();
			getchar();
			break;
		case 2:
			cout << "Pasirinkimas [2]" << endl;
			cout << "Sinoptiku sarasas:" << endl;
			theQueue.displayList();
			cout << endl;
			cout << "Spausdinimas atliktas sekmingai, spauskite bet kuri klavisa [info]..." << endl;
			getchar();
			getchar();
			break;
		case 3:
			cout << "Pasirinkimas [3]" << endl;
			cout << "Sinoptiku vejo krypties isvedimas, pateikiant skaiciu kiek sinoptiku uz tokia vejo krypti pasisako:" << endl;
			theQueue.vejas();
			cout << endl;
			cout << "Spausdinimas atliktas sekmingai, spauskite bet kuri klavisa [info]..." << endl;
			getchar();
			getchar();
			break;
		case 4:
			cout << "Pasirinkimas [4]" << endl;
			theQueue.vidurkis();
			cout << "Spausdinimas atliktas sekmingai, spauskite bet kuri klavisa [info]..." << endl;
			getchar();
			getchar();
			break;
		case 5:
			cout << "Pasirinkimas [5]" << endl;
			cout << "Viso gero :)" << endl;
			break;
		}
	} while (pas != 5);

	return 0;


}
