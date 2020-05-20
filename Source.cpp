#include<iostream>
using namespace std;

int sifra = 15000;


class Uposlenik {

	int _sifra; //Automatski uvecavati za 1 za svakog novog uspolenika.
	char _ime[30];
	char _prezime[30];
	char* _radnoMjesto;
	static const char* _kompanija;

public:

	char* getIme() { return _ime; }
	char* getPrezime() { return _prezime; }
	int getSifra() { return _sifra; }


	Uposlenik() :_sifra(sifra) {
		strncpy_s(_ime, "---" , _TRUNCATE);
		strncpy_s(_prezime, "---", _TRUNCATE);
		_radnoMjesto = nullptr;
	}

	//Implementirati potrebne konstruktor i destruktor funkcije
	

	Uposlenik(const char * ime, const char* prezime, const char* radnoMjesto) :_sifra(sifra++)
	{

		strncpy_s(_ime, ime, _TRUNCATE);
		strncpy_s(_prezime, prezime, _TRUNCATE);

		int vel = strlen(radnoMjesto) + 1;
		_radnoMjesto = new char[vel];
		strcpy_s(_radnoMjesto, vel, radnoMjesto);

	}
	Uposlenik(Uposlenik& orig) :_sifra(sifra++) {
		strncpy_s(_ime, orig._ime, _TRUNCATE);
		strncpy_s(_prezime, orig._prezime, _TRUNCATE);

		int vel = strlen(orig._radnoMjesto) + 1;
		_radnoMjesto = new char[vel];
		strcpy_s(_radnoMjesto, vel, orig._radnoMjesto);

	}

	

	~Uposlenik()
	{
		
			delete[] _radnoMjesto;
			_radnoMjesto = NULL;

	}
	void operator= (Uposlenik& desni) {
		if (this != &desni) {
			strcpy_s(_ime, desni._ime );
			strcpy_s(_prezime, desni._prezime);

			if (_radnoMjesto != nullptr)
				delete[] _radnoMjesto;
			int vel = strlen(desni._radnoMjesto) + 1;
			_radnoMjesto = new char[vel];
			strcpy_s(_radnoMjesto, vel, desni._radnoMjesto);
		}

	}

	//Ostale funkcije dodati po potrebi

	void Info()
	{
		cout << "Sifra: " << _sifra << endl;
		cout << "Ime i prezime: " << _ime << " " << _prezime << endl;
		if(_radnoMjesto!=nullptr)
			cout << "Radno mjesto: " << _radnoMjesto << endl;
		cout << "Kompanija: " << _kompanija << endl;
	}

};
const char* Uposlenik::_kompanija = "DOO ImeKompanije";

class Aktivnost {
	char* _naziv;
	bool _zavrsena;
	int* _trajanje; //Izrazeno u danima
	Uposlenik* _uposlenici[5];
public:
	char* getNaziv()const { return _naziv; }
	bool getZavrsena()const { return _zavrsena; }
	void setZavrsena() {
		_zavrsena = true;
	}
	Uposlenik * getUposlenik(int lok)const{
			return _uposlenici[lok];
	}
	//Implementirati potrebne konstruktor i destruktor funkcije
	Aktivnost() :_zavrsena(false) {
		_naziv = nullptr;
		_trajanje = nullptr;
		for (int i = 0; i < 5; i++)
			_uposlenici[i] = nullptr;
	}
	Aktivnost(const char* naziv, int trajanje) :_zavrsena(false) {
		int vel = strlen(naziv) + 1;
		_naziv = new char[vel];
		strcpy_s(_naziv, vel, naziv);
		_trajanje = new int(trajanje);
		for (int i = 0; i < 5; i++)
			_uposlenici[i] = nullptr;
	}
	Aktivnost(Aktivnost& orig):_zavrsena(orig._zavrsena) {
		int vel = strlen(orig._naziv) + 1;
		_naziv = new char[vel];
		strcpy_s(_naziv, vel, orig._naziv);

		_trajanje = new int(*orig._trajanje);

		for (int i = 0; i < 5; i++)
			if (orig._uposlenici[i] != nullptr)
				_uposlenici[i] = new Uposlenik(*orig._uposlenici[i]);
	}
	//Funkciju koja omogucava angazovanje uposlenika na projektnoj aktivnosti. Funkcija treba da vrati vrijednost tipa
	//bool za uspjesno, odnosno neuspjesno dodavanje uposlenika. Nije moguce dodati istog uposlenika vise puta. Nije moguce
	//angazovati uposlenike na vec zavrsenoj aktivnosti.

	bool addUposlenika(Uposlenik& obj) {
		if (_zavrsena)
			return false;
		for (int i = 0; i < 5; i++)
			if (_uposlenici[i] != nullptr && strcmp(_uposlenici[i]->getIme(), obj.getIme()) == 0)
				return false;

		for (int i = 0; i < 5; i++)
			if (_uposlenici[i] == nullptr) {
				_uposlenici[i] = new Uposlenik(obj);
				return true;
			}
	}

	Aktivnost & operator =(Aktivnost& desni) {
		if (this != &desni) {
			int vel = strlen(desni._naziv) + 1;
			_naziv = new char[vel];
			strcpy_s(_naziv, vel, desni._naziv);

			delete[]_trajanje;
			_trajanje = new int(*desni._trajanje);

			for (int i = 0; i < 5; i++)
				if (_uposlenici[i] != nullptr) {
					delete _uposlenici[i];
					_uposlenici[i] = nullptr;
				}

			for (int i = 0; i < 5; i++)
				if (desni._uposlenici[i] != nullptr)
					_uposlenici[i] = new Uposlenik(*desni._uposlenici[i]);
		}
		return *this;

	}

	//Funkciju koja uklanja uposlenika na aktivnosti sa sifrom proslijedjenom kao parametar.

	/*bool removeUposlenikaSifra(int sifra) {
		for (int i = 0; i < 5; i++)
			if (_uposlenici[i] != nullptr && _uposlenici[i]->getSifra() == sifra) {
				delete _uposlenici[i];
				_uposlenici[i] = nullptr;
				return true;
			}
		return false;
	}*/
	void UkloniUposlenika(int sifra) {
		int indeks = -1;
		for (int i = 0; i < 5; i++)
		{
			if (_uposlenici[i] != nullptr) {
				if (_uposlenici[i]->getSifra() == sifra) {
					indeks = i;
					break;
				}
			}
		}
		if (indeks == -1) {
			cout << "Uposlenik nije pronadjen!\n";
			return;
		}
		for (int i = indeks; i < 4; i++)
		{
			delete _uposlenici[i];
			_uposlenici[i] = nullptr;
			if (_uposlenici[i + 1] != nullptr) {
				_uposlenici[i] = new Uposlenik(*_uposlenici[i + 1]);
				delete _uposlenici[i + 1];
				_uposlenici[i + 1] = nullptr;
			}
		}
	}

	//Funkciju koja uklanja sve uposlenike angazovane na aktivnosti.
	void ukloniSveUposlenike() {
		for (int i = 0; i < 5; i++)
			if (_uposlenici[i] != nullptr) {
				delete _uposlenici[i];
				_uposlenici[i] = nullptr;
			}
	}

	void info() {
		if(_naziv!=nullptr)
			cout << "Aktivnost naziv: " << _naziv << endl;
		if (_zavrsena)
			cout << "Aktivnost zavrsena" << endl;
		else
			cout << "Aktivnost u toku" << endl;
		cout << "Trajanje aktivnosti " << *_trajanje << " dana" << endl;
		cout << "Uposlenici: " << endl;
		for (int i = 0; i < 5; i++)
			if (_uposlenici[i] != nullptr) {
				_uposlenici[i]->Info();
			}
	}

	~Aktivnost() {
		delete[] _naziv; _naziv = NULL;
		delete _trajanje; _trajanje = NULL;
		for (int i = 0; i < 5; i++)
			{
				delete _uposlenici[i];
				_uposlenici[i] = NULL;
			}
		
	}
};

class Projekat {
	char* _naziv;
	char* _oblast;
	int _trajanje; //Izrazeno u mjesecima
	Aktivnost* _aktivnosti;
	int _brojAktivnosti;
public:

	//Implementirati potrebne konstruktor i destruktor funkcije.
	Projekat(const char* naziv, const char* oblast, int trajanje):_trajanje(trajanje) {
		int vel = strlen(naziv) + 1;
		_naziv = new char[vel];
		strcpy_s(_naziv, vel, naziv);
		vel = strlen(oblast) + 1;
		_oblast = new char[vel];
		strcpy_s(_oblast, vel, oblast);
		_brojAktivnosti = 0;
		_aktivnosti = nullptr;
	}
	Projekat(Projekat & obj) :_trajanje(obj._trajanje) {
		int vel = strlen(obj._naziv) + 1;
		_naziv = new char[vel];
		strcpy_s(_naziv, vel, obj._naziv);
		vel = strlen(obj._oblast) + 1;
		_oblast = new char[vel];
		strcpy_s(_oblast, vel, obj._oblast);
		_brojAktivnosti = obj._brojAktivnosti;
		for (int i = 0; i < _brojAktivnosti; i++)
		{
			_aktivnosti[i] = obj._aktivnosti[i];
		}
	}
	~Projekat() {
		delete[]_naziv; _naziv = NULL;
		delete[]_oblast; _oblast = NULL;
		delete[] _aktivnosti; _aktivnosti = NULL;
	}
	//Funkciju za dodavanje projektnih aktivnosti. Sprijeciti dodavanje vise aktivnosti sa istim nazivom.
	//Za potrebe poredjenja aktivnosti kreirati funkciju unutar klase Aktivnosti.
	void addAktivnost(Aktivnost& obj) {
		for (int i = 0; i < _brojAktivnosti; i++)
			if (strcmp(_aktivnosti[i].getNaziv(), obj.getNaziv()) == 0)
				break;
		Aktivnost* temp = new Aktivnost[_brojAktivnosti + 1];
		for (int i = 0; i < _brojAktivnosti; i++) 
		{
			temp[i] = _aktivnosti[i];
		}
		temp[_brojAktivnosti++] = obj;
		delete[] _aktivnosti;
		_aktivnosti = temp;
		

	}

	//Funkciju koja oznacava aktivnost kao zavrsenu. Funkcija kao parametar prima naziv aktivnosti.
	void zavrsiAktivnost(const char* ime) {
		for (int i = 0; i < _brojAktivnosti; i++)
			if (strcmp(_aktivnosti[i].getNaziv(), ime) == 0 && _aktivnosti[i].getZavrsena()==false ) {
				_aktivnosti[i].setZavrsena();
			}
	}


	//Funkciju koja treba da postojecoj aktivnosti dodijeli novog uposlenika.

	bool addUposlenika(Aktivnost& a, Uposlenik& u) {
		for (int i = 0; i < _brojAktivnosti; i++)
			if (strcmp(_aktivnosti[i].getNaziv(), a.getNaziv()) == 0) {
				return _aktivnosti[i].addUposlenika(u);
			}
		return false;
	}


	//Funkciju koja treba da vrati sve uposlenike angazovane na odredjenoj aktivnosti. Ulazni parametar je naziv aktivnosti.
	Uposlenik * getUposlenike(const char* ime, int & duzina) {
		
		int lok = 0;
		int brojac = 0;
		for (int i = 0; i < _brojAktivnosti; i++)
			if (strcmp(_aktivnosti[i].getNaziv(), ime) == 0) {
				lok = i;	
			}
		for (int i = 0; i < 5; i++)
			if (_aktivnosti[lok].getUposlenik(i)!=nullptr)
				brojac++;
		duzina = brojac;
		Uposlenik *u=new Uposlenik[brojac];
		int a = 0;
		for (int i = 0; i < 5; i++)
		{
			if (_aktivnosti[lok].getUposlenik(i) == nullptr)
				break;
			else {
				u[a] = *_aktivnosti[lok].getUposlenik(i);
				a++;
			}

		}
				
		return u;
	}

	//Funkciju koja uklanja odredjenog uposlenika na aktivnosti. Ulazni parametri funkcije su naziv aktivnosti i sifra uposlenika.


	//Funkciju koja uklanja sve uposlenike angazovane na aktivnosti sa nazivom proslijedjenim kao parametar.


	//Funkciju koja pronalazi uposlenika sa najvecim brojem angazmana na aktivnostima.


	//Funkciju koja pronalazi 3 uposlenika koja su angazovana na najvecem broju nezavrsenih aktivnosti.


	//Funkciju koja ispisuje sve zavrsene aktivnosti na projektu.

	void info() {
		cout << "Naziv projekta: " << _naziv << endl;
		cout << "Oblast: " << _oblast << endl;
		cout << "Trajanje projekta (" << _trajanje << ") dana" << endl;
		if (_aktivnosti != nullptr)
			for (int i = 0; i < _brojAktivnosti; i++) {
				cout << "		";
				_aktivnosti[i].info();
			}
				

	}

};


/*Kreirati globalnu funkciju koja pronalazi najuspjesnijeg usposlenika na projektima proslijedjenim kao parametar.
Uposlenik se smatra najuspjesnijim ako je angazovan na najvecem broju zavrsenih aktivnosti. Ako vise uposlenika
ima isti broj zavrsenih aktivnosti, uspjesnijim se smatra onaj cije su aktivnosti trajale duze.
*/


int main()
{
	//Testirati sve dostupne funkcionalnosti

	Uposlenik u1("Dalibor", "Blazevic","Programer");
	Uposlenik u2("Edin", "asdasd", "Programer");
	Uposlenik u3("Amar", "fafasfd", "Programer");
	Uposlenik u4("Dina", "afasfsa", "Programer");
	Uposlenik u5("Samir", "asdasd", "Programer");
	Uposlenik u6("Tarik", "fasfa", "Programer");

	u6.Info();


	Aktivnost a1("BIS", 126);
	Aktivnost a2("Kino", 333);
	
	a1.addUposlenika(u1);
	a1.addUposlenika(u2);
	a1.addUposlenika(u3);
	a1.addUposlenika(u4);
	a1.addUposlenika(u5);
	a1.addUposlenika(u6);

	a1.info();
	a1.UkloniUposlenika(15007);
	a1.UkloniUposlenika(15008);
	a1.UkloniUposlenika(15009);

	a1.addUposlenika(u6);
	a1.addUposlenika(u4);


	
	
	
	a1.info();
	cout << "-------------------------------------------------------" << endl;
	Projekat p1("ImeProjekta", "OblastProjekta", 124);
	p1.addAktivnost(a1);
	p1.addAktivnost(a2);
	int brojac = 0;
	Uposlenik * u= p1.getUposlenike("BIS", brojac);
	p1.info();
	cout << "-------------------------------------------------------" << endl;
	
	for (int i = 0; i < brojac; i++)
		u[i].Info();

	return 0;
}

