#include<iostream>

using namespace std;

class Vrijeme {
	int _sati;
	int _minute;
	int _sekunde;
public:

	//Konstruktor bez parametara
	Vrijeme() {
		_sati = _minute = _sekunde = 0;
	}
	//Konstruktor sa 3 parametra (sati, minute i sekunde)
	Vrijeme(int h, int m, int s) {
		if (s > 60 && s < 1 && m>60 && m < 1 && h < 0 && h>24) {
			_sati = _minute = _sekunde = 0;
			return;
		}
		else {
			_sati = h;
			_minute = m;
			_sekunde = s;

		}

	}
	//Konstruktor sa 2 parametra (sati i minute)
	Vrijeme(int h, int m) {
		if (m>60 && m < 1 && h < 0 && h>24) {
			_sati = _minute =  0;
			return;
		}
		else {
			_sati = h;
			_minute = m;
			_sekunde = 0;


		}

	}

	//Funkciju Info sa neobaveznim parametrom tipa bool koji određuje da li će vrijeme biti ispisano u punom formatu
	//(hh:mm:ss) ili u skraćenom formatu (hh:mm). Default-no funkcija vrši ispis u punom formatu.
	void Info(bool type=true) {
		if (type)
			cout << _sati << ":" << _minute << ":" << _sekunde << endl;
		else
			cout << _sati << ":" << _minute << endl;
	}

	//Funkciju Add koja kao rezultat vraća novi objekat tipa vrijeme koji predstavlja 
	//sumu vremena poslijeđenog kao parametar i instance this.
	Vrijeme Add(Vrijeme& obj) {
		Vrijeme novo;
		int ukupno = ((_sati * 60 * 60) + (_minute * 60) + _sekunde) + ((obj._sati * 60 * 60) + (obj._minute * 60) + obj._sekunde);
		while (ukupno) {
			ukupno -= 60;
			novo._minute++;
			if (novo._minute == 60) {
				novo._sati++;
				novo._minute = 0;
			}
			if (ukupno < 60) {
				novo._sekunde = ukupno;
				ukupno = 0;
			}
		}
		return novo;
	}

	//Funkciju Add koja kao rezultat vraća novi objekat tipa vrijeme koji predstavlja 
	//sumu parametra izraženog u minutama i vremena instance this.
	Vrijeme AddMin(int min) {
		Vrijeme novo;
		int ukupno = ((_sati * 60 * 60) + (_minute * 60) + _sekunde) + (min * 60);
		while (ukupno) {
			ukupno -= 60;
			novo._minute++;
			if (novo._minute == 60) {
				novo._sati++;
				novo._minute = 0;
			}
			if (ukupno < 60) {
				novo._sekunde = ukupno;
				ukupno = 0;
			}
		}
		return novo;
	}


	//Funkciju CompareTo koja vraća vrijednost tipa int u zavisnosti od toga da li je vrijeme instance this prije, jednako ili poslije
	//vremena proslijeđenog kao parametar.
	//Moguće povratne vrijednosti:
	//-1 - vrijeme instance this nastupa prije vremena v2
	// 0 - vrijeme instance this je jednako vremenu v2
	// 1 - vrijeme instance this nastupa nakon vremena v2
	int CompareTo(Vrijeme& obj) {
		int v1 = (_sati * 60 * 60) + (_minute * 60) + _sekunde;
		int v2 = (obj._sati * 60 * 60) + (obj._minute * 60) + obj._sekunde;
		if (v1 < v2)
			return -1;
		if (v1 == v2)
			return 0;
		else
			return 1;
	}

};


/*
Potrebno je kreirati aplikaciju za dijeljenje znanja putem razmjene članaka među korisnicima.
Izdvojene su sljedeće funkcionalnosti:
- Administrator sistema je zadužen za upravljanje korisničkim nalozima (Ime, Prezime, Email, DatumRegistracije, KorisnickoIme, Lozinka).
- Svaki članak (Naslov, Sadrzaj, Datum, Satnica, BrojPregleda) može sadržavati više tagova, ali pripada samo jednoj oblasti.
- Članke mogu dodavati svi registrovani korisnici.
- Korisnici aplikacije također mogu ostaviti komentar (Tekst, Datum, Popularnost) na određeni članak.
*/

/*
Na osnovu datih klasa implementirati opisane funkcionalnosti sistema. Po potrebi dopuniti klase novim atributima i/ili funkcijama.
*/

class Datum
{
	int _dan;
	int _mjesec;
	int _godina;
public:
	//Potrebne konstruktor i destruktor funkcije

	Datum() {
		_dan = _mjesec = 1;
		_godina = 2000;
	}
	Datum(int godina, int mjesec, int dan) {
		_dan = dan;
		_mjesec = mjesec;
		_godina = godina;
	}

	//Funkciju Info
	void Info() {
		cout << _dan << "/" << _mjesec << "/" << _godina << endl;
	}
	int getDan()const { return _dan; }
	int getMjesec()const { return _mjesec; }
	int getGodina()const { return _godina; }
};

enum TipKorisnika { Administrator, Guest };
class Korisnik
{
	char _ime[30];
	char _korisnickoIme[20];
	char* _lozinka;
	TipKorisnika _tipKorisnika; //Administrator, Guest
public:
	char * getIme(){ return _ime; }
	char* getKorisnicko() { return _korisnickoIme; }
	char* getLozinka() { return _lozinka; }
	TipKorisnika getTipKorisnika() { return _tipKorisnika; }
	TipKorisnika getTipKorisnika()const { return _tipKorisnika; }
	//Potrebne konstruktor i destruktor funkcije
	Korisnik() {
		strcpy_s(_ime, 30, "---");
		strcpy_s(_korisnickoIme, 20, "---");
		_lozinka = nullptr;
		_tipKorisnika = Guest;
	}
	Korisnik(const char* ime, const char* korisnicko, const char* lozinka, TipKorisnika tip) {
		strcpy_s(_ime, 30, ime);
		strcpy_s(_korisnickoIme, 20, korisnicko);
		int vel = strlen(lozinka) + 1;
		_lozinka = new char[vel];
		strcpy_s(_lozinka, vel, lozinka);
		_tipKorisnika = tip;
	}
	~Korisnik() {
		delete[] _lozinka; _lozinka = NULL;
	}

	//Funkciju za promjenu korisničke lozinke
	void PromjenaLozinke(const char* novaLoz) {
		if (_lozinka != nullptr) {
			delete[]_lozinka;
			_lozinka = new char[strlen(novaLoz) + 1];
			strcpy_s(_lozinka, strlen(novaLoz) + 1, novaLoz);
		}
		else {
			_lozinka = new char[strlen(novaLoz) + 1];
			strcpy_s(_lozinka, strlen(novaLoz) + 1, novaLoz);
		}
	}

	//Funkciju Info
	void Info() {
		cout << "Ime: " << _ime << endl;
		cout << "Korisnicko ime: " << _korisnickoIme << endl;
		if (_lozinka != nullptr)
			cout << "Lozinka: " << _lozinka << endl;
		cout << "Tip Korisnika: ";
		if (_tipKorisnika == 0)
			cout << "Administrator" << endl;
		else
			cout << "Guest" << endl;
	}

};

class Komentar
{
	char* _tekst;
	Datum _datum;
	Vrijeme _satnica;
	int _popularnost;
	Korisnik* _autor;
public:
	char* getTekst()const { return _tekst; }
	Datum getDatum()const { return _datum; }
	Vrijeme getSatnica()const { return _satnica; }
	int getPopularnost()const { return _popularnost; }
	Korisnik* getKorisnik() const { return _autor; }

	void setText(const char* tekst) {
		if (tekst != nullptr) {
			int vel = strlen(tekst) + 1;
			_tekst = new char[vel];
			strcpy_s(_tekst, vel, tekst);
		}
	}
	void setDatum(Datum d) {
		_datum = d;
	}
	void setSatnica(Vrijeme v) { _satnica = v; }
	void setPopularnost(int pop) { _popularnost = pop; }
	void setKorisnik(Korisnik& obj) {
		if(&obj!=nullptr)
			_autor = new Korisnik(obj.getIme(), obj.getKorisnicko(), obj.getLozinka(), obj.getTipKorisnika());
	}
	//Potrebne konstruktor i destruktor funkcije
	Komentar() {
		_tekst = nullptr;
		_popularnost = 0;
		_autor = nullptr;
	}
	Komentar(const char* text, Datum d, Vrijeme v,const char * ime, const char* korisnicko, const char* lozinka, TipKorisnika tip)
		:_datum(d), _satnica(v) {
		_tekst = new char[strlen(text) + 1];
		strcpy_s(_tekst, strlen(text) + 1, text);
		_popularnost = 0;
		_autor = new Korisnik(ime, korisnicko, lozinka, tip);
	}
	~Komentar(){
		delete[] _tekst; _tekst = NULL;
		delete _autor; _autor = NULL;
	}
	//Funkciju za izmjenu popularnosti komentara
	void PromjenaPopularnosti() {
		_popularnost+=1;
	}

	//Funkciju Info
	void Info() {
		if (_tekst != nullptr)
			cout << "Komentar: " << _tekst << endl;
		_datum.Info();
		_satnica.Info();
		cout << "Popularnost: " << _popularnost<<endl;
		if (_autor != nullptr)
			_autor->Info();
	}
};

class Clanak
{
	char _naslov[150];
	char* _sadrzaj;
	Datum _datum;
	Vrijeme _satnica;
	int _brojPregleda;
	char* _tagovi[10];
	char _oblast[100];
	Korisnik* _autor;
	Komentar* _komentari;
	int _brojKomentara;
public:
	//Konstruktor i destruktor
	Clanak(){
		strcpy_s(_naslov, 150, "---");
		_sadrzaj = nullptr;
		_brojPregleda = 0;

		for (int i = 0; i < 10; i++)
			_tagovi[i] = nullptr;
		strcpy_s(_oblast, 100, "---");
		_autor = nullptr;
		_komentari = nullptr;
		_brojKomentara = 0;

	}
	Clanak(const char* naslov, const char* sadrzaj, Datum d, Vrijeme v, const char* oblast,
		const char* ime, const char* korisnicko, const char* lozinka, TipKorisnika tip):_datum(d), _satnica(v) {
		strcpy_s(_naslov, 150, naslov);
		int vel = strlen(sadrzaj) + 1;
		_sadrzaj = new char[vel];
		strcpy_s(_sadrzaj, vel, sadrzaj);
		_brojPregleda = 0;
		for (int i = 0; i < 10; i++)
			_tagovi[i] = nullptr;
		strcpy_s(_oblast, 100, oblast);
		_autor = new Korisnik(ime, korisnicko, lozinka, tip);
		_komentari = nullptr;
		_brojKomentara = 0;

	}
	~Clanak() {
		delete[]_sadrzaj; _sadrzaj = NULL;
		for (int i = 0; i < 10; i++)
			if (_tagovi[i] != nullptr) {
				delete[] _tagovi[i];
				_tagovi[i] = NULL;
			}
		delete _autor; _autor = NULL;
		if (_komentari != nullptr) {
			delete [] _komentari; _komentari = NULL;
		}
	}
	//Funkciju za dodavanje tagova za članak
	void AddTag(const char* tag) {
		for (int i = 0; i < 10; i++){
			if (_tagovi[i] == nullptr) {
				_tagovi[i] = new char[strlen(tag) + 1];
				strcpy_s(_tagovi[i], strlen(tag) + 1, tag);
				break;
			}
			else {
				cout << "Svi tagovi su popunjeni!!" << endl;
			}
		}
	}
	

	/*Funkciju za promjenu sadržaja i vremena promjene članka. Kao verifikaciju dozvole potrebno je
	proslijediti korisničko ime autora članka.
	Samo kreator članka ima permisije da mijenja njegov sadržaj.
	*/
	bool PromjenaSadrazaja(const char * autor, Vrijeme v, const char * novisadrzaj) {
		if (strcmp(_autor->getIme(), autor) == 0) {
			_satnica = v;
			if (_sadrzaj != nullptr) {
				delete[] _sadrzaj;
				_sadrzaj = new char[strlen(novisadrzaj) + 1];
				strcpy_s(_sadrzaj, strlen(novisadrzaj) + 1, novisadrzaj);
			}
			else {
				_sadrzaj = new char[strlen(novisadrzaj) + 1];
				strcpy_s(_sadrzaj, strlen(novisadrzaj) + 1, novisadrzaj);
			}
			return true;


		}
		else
			return false;
	}

	//Funkciju za dodavanje komentara
	void addKomentar(Komentar& obj) {
		Komentar* temp = new Komentar[_brojKomentara + 1];
		for (int i = 0; i < _brojKomentara; i++)
		{
			temp[i].setDatum(_komentari[i].getDatum());
			temp[i].setKorisnik(*_komentari[i].getKorisnik());
			temp[i].setPopularnost(_komentari[i].getPopularnost());
			temp[i].setSatnica(_komentari[i].getSatnica());
			temp[i].setText(_komentari[i].getTekst());
		}
		temp[_brojKomentara].setDatum(obj.getDatum());
		temp[_brojKomentara].setKorisnik(*obj.getKorisnik());
		temp[_brojKomentara].setPopularnost(obj.getPopularnost());
		temp[_brojKomentara].setSatnica(obj.getSatnica());
		temp[_brojKomentara].setText(obj.getTekst());

		delete[] _komentari;
		_brojKomentara++;
		_komentari = new Komentar[_brojKomentara];
		for (int i = 0; i < _brojKomentara; i++)
		{
			_komentari[i].setDatum(temp[i].getDatum());
			_komentari[i].setKorisnik(*temp[i].getKorisnik());
			_komentari[i].setPopularnost(temp[i].getPopularnost());
			_komentari[i].setSatnica(temp[i].getSatnica());
			_komentari[i].setText(temp[i].getTekst());
		}

	}

	//Funkciju Info

	void Info() {
		cout << "Clanak: " << _naslov << endl;
		if (_sadrzaj != nullptr)
			cout << "Sadrzaj: " << _sadrzaj << endl;
		_datum.Info();
		_satnica.Info();
		cout << "Broj pregleda: " << _brojPregleda << endl;
		for (int i = 0; i < 10; i++)
			if (_tagovi[i] != nullptr)
				cout << "Tag " << i + 1 << ": " << _tagovi[i] << endl;
		cout << "Oblast: " << _oblast << endl;
		cout << "Autor: ";
		if (_autor != nullptr)
			_autor->Info();
		cout << "Komentari: ";
		if (_komentari != nullptr)
			for (int i = 0; i < _brojKomentara; i++)
				_komentari[i].Info();
	}

};

int main()
{
	//Kreirati testni program koji demonstrira implementirane funckionalnosti
	Vrijeme v1, v2(22, 31, 60), v3(10, 30);
	v1.Info();
	v2.Info();
	v3.Info();
	
	Datum d1(17, 3, 2020);

	Korisnik k1, k2("Dalibor", "Borrki", "1234", Guest);
	k1.Info();
	k2.Info();
	cout << "---------------------------------------------" << endl;
	k2.PromjenaLozinke("novaLozinka");
	k2.Info();
	k1.PromjenaLozinke("novaLozinka");
	k1.Info();
	cout << "---------------------------------------------" << endl;
	Komentar kom1, kom2("text komentara", d1, v2, k2.getIme(), k2.getKorisnicko(), k2.getLozinka(), k2.getTipKorisnika());
	Komentar kom3("text komentara3", d1, v2, "Dina", "Glupko", "Dina124", Guest);
	//kom1.Info();
	kom3.PromjenaPopularnosti();
	kom3.Info();
	cout << "---------------------------------------------" << endl;
	cout << "---------------------------------------------" << endl;
	Clanak c1, c2("Krema", "Sadrzaj clanka o kremi", d1, v2, "Njega koze i lica", k2.getIme(), k2.getKorisnicko(), k2.getLozinka(), k2.getTipKorisnika());
	c1.Info();
	c2.Info();
	c1.AddTag("tag1");
	c1.AddTag("tag2");
	c1.AddTag("tag3");
	c2.AddTag("tag1");
	c2.AddTag("tag2");
	c2.AddTag("tag3");
	cout << "---------------------------------------------" << endl;

	c1.Info();
	c2.Info();
	cout << "-------------------RADI--------------------------" << endl;
	
	c2.addKomentar(kom2);
	c2.addKomentar(kom1);
	kom3.PromjenaPopularnosti();
	c2.Info();
	cout << "-------------------RADI--------------------------" << endl;
	if (c2.PromjenaSadrazaja("Dina"\, v3, "Funcija radi")) {
		cout << "sadrzaj uspjesno promjenjen!" << endl;
		c2.Info();
	}
	else
		cout << "Nemate permisije za promjenu sadrzaja!" << endl;

	return 0;
}
