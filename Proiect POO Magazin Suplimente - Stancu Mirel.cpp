//Magazin suplimente alimentare, articole sportive -- STANCU GHEORGHE-MIREL 1058E

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#pragma warning( disable : 6001 )
#pragma warning( disable : 26812 )
#pragma warning( disable : 6385 )
using namespace std;


class Suplimente
{
protected:

	const int idProdus;
	static int basicId;
	string nume;
	float valoareEnergetica;
	float grasimi; 
	float carbohidrati;
	float proteine;
	int nrGramaje;
	float* gramaj; 
	float* preturi;

public:

	//Constructor default
	Suplimente() : idProdus(++basicId + 100), valoareEnergetica(0), grasimi(0), carbohidrati(0), proteine(0), nrGramaje(0), gramaj(NULL), preturi(NULL)
	{
	}

	//Constructor cu parametrii
	Suplimente(string nume, float valoareEnergetica, float grasimi, float carbohidrati, float proteine, int nrGramaje, float* gramaj,float* preturi) : idProdus(++basicId + 100)
	{
		
		this->nume = nume;
		this->valoareEnergetica = valoareEnergetica;
		this->grasimi = grasimi;
		this->carbohidrati = carbohidrati;
		this->proteine = proteine;
		if (nrGramaje != 0 && gramaj != NULL)
		{
			this->nrGramaje = nrGramaje;
			this->gramaj = new float[nrGramaje];
			for (int i = 0; i < this->nrGramaje; i++)
				this->gramaj[i] = gramaj[i];
		}
		else
		{
			this->nrGramaje = 0;
			this->gramaj = NULL;
		}
		if(nrGramaje != 0 && preturi != NULL)
		{
			this->nrGramaje = nrGramaje;
			this->preturi = new float[nrGramaje];
			for (int i = 0; i < this->nrGramaje; i++)
				this->preturi[i] = preturi[i];
		}
		else
		{
		this->nrGramaje = 0;
		this->preturi = NULL;
		}
	}

	//Constructor copiere
	Suplimente(const Suplimente& s) : nume(s.nume), valoareEnergetica(s.valoareEnergetica), grasimi(s.grasimi), carbohidrati(s.carbohidrati), proteine(s.proteine), idProdus(++basicId + 100)
	{
		if (s.gramaj != NULL && s.nrGramaje > 0)
		{
			this->gramaj = new float[s.nrGramaje];
			this->nrGramaje = s.nrGramaje;
			for (int i = 0; i < this->nrGramaje; i++)
			{
				this->gramaj[i] = s.gramaj[i];
			}
		}
		else
		{
			this->gramaj = NULL;
			this->nrGramaje = 0;
		}
		if (s.preturi != NULL && s.nrGramaje > 0)
		{
			this->preturi = new float[s.nrGramaje];
			this->nrGramaje = s.nrGramaje;
			for (int i = 0; i < this->nrGramaje; i++)
			{
				this->preturi[i] = s.preturi[i];
			}
		}
		else
		{
			this->preturi = NULL;
			this->nrGramaje = 0;
		}
	}

	//Operator =
	Suplimente& operator=(const Suplimente& s)
	{
		this->nume = s.nume;
		this->valoareEnergetica = s.valoareEnergetica;
		this->grasimi = s.grasimi;
		this->carbohidrati = s.carbohidrati;
		this->proteine = s.proteine;
		delete[] this->gramaj;
		delete[] this->preturi;
		if (s.gramaj != NULL && s.nrGramaje > 0)
		{
			this->gramaj = new float[s.nrGramaje];
			this->nrGramaje = s.nrGramaje;
			for (int i = 0; i < this->nrGramaje; i++)
			{
				this->gramaj[i] = s.gramaj[i];
			}
		}
		else
		{
			this->gramaj = NULL;
			this->nrGramaje = 0;
		}
		if (s.preturi != NULL && s.nrGramaje > 0)
		{
			this->preturi = new float[s.nrGramaje];
			this->nrGramaje = s.nrGramaje;
			for (int i = 0; i < this->nrGramaje; i++)
			{
				this->preturi[i] = s.preturi[i];
			}
		}
		else
		{
			this->preturi = NULL;
			this->nrGramaje = 0;
		}
		return *this;
	}

	//Destructor
	~Suplimente()
	{
		delete[] this->gramaj;
		delete[] this->preturi;
	}

	//Operator indexare []
	float& operator[](int index)
	{
		return this->gramaj[index];
	}

	//Operator +
	Suplimente operator+(float nrCalorii)//Adauga calorii
	{
		Suplimente aux = *this;
		if (nrCalorii >= 0)
		{
			aux.valoareEnergetica += nrCalorii;
		}
		return aux;
	}

	//Operator ++ preincrementare --- adauga un nou gramaj,un nou pret, dublandu-l pe ultimul.
	Suplimente operator++()
	{
		Suplimente aux = *this;
		if (this->nrGramaje > 0)
		{
			this->nrGramaje++;
			delete[] this->gramaj;
			delete[] this->preturi;
			this->gramaj = new float[this->nrGramaje];
			this->preturi = new float[this->nrGramaje];
			for (int i = 0; i < aux.nrGramaje; i++)
			{
				this->gramaj[i] = aux.gramaj[i];
				this->preturi[i] = aux.preturi[i];
			}
			this->gramaj[this->nrGramaje-1] = this->gramaj[aux.nrGramaje - 1] * 2;
			this->preturi[this->nrGramaje - 1] = this->preturi[aux.nrGramaje - 1] * 2;
		}
		return *this;
	}

	//Operator ++ postincrementare --- adauga un nou gramaj, dublandu-l pe ultimul.
	Suplimente operator++(int)
	{
		Suplimente aux = *this;
		if (aux.nrGramaje > 0)
		{
			aux.nrGramaje++;
			delete[] aux.gramaj;
			delete[] aux.preturi;
			aux.gramaj = new float[aux.nrGramaje];
			aux.preturi = new float[aux.nrGramaje];
			for (int i = 0; i < this->nrGramaje; i++)
			{
				aux.gramaj[i] = this->gramaj[i];
				aux.preturi[i] = this->preturi[i];
			}
			aux.gramaj[aux.nrGramaje - 1] = aux.gramaj[this->nrGramaje - 1] * 2;
			aux.preturi[aux.nrGramaje - 1] = aux.preturi[this->nrGramaje - 1] * 2;
 		}
		return aux;
	}

	//Operator cast la string
	operator string()
	{
		return this->nume;
	}

	//Operator cast la float - valoareEnergetica
	operator float()
	{
		return this->valoareEnergetica;
	}

	//Operator negatie - sterge gramajele
	Suplimente operator!()
	{
		Suplimente aux = *this;
		delete[] aux.gramaj;
		delete[] aux.preturi;
		aux.gramaj = NULL;
		aux.preturi = NULL;
		aux.nrGramaje = 0;
		return aux;
	}

	//Operator < - compara valoarea energetica
	bool operator<(const Suplimente& s)
	{
		if (this->valoareEnergetica < s.valoareEnergetica)
			return true;
		else
			return false;
	}
	//Operator > - compara valoarea energetica
	bool operator>(const Suplimente& s)
	{
		if (this->valoareEnergetica > s.valoareEnergetica)
			return true;
		else
			return false;
	}

	//Operator == compara valoarea energetica
	bool operator==(const Suplimente& s)
	{
		if (this->valoareEnergetica == s.valoareEnergetica)
			return true;
		else
			return false;
	}

	//Getter
	const int getIdProdus() { return this->idProdus; }

	static int getBasicId() { return basicId; }

	string getNume() { return this->nume; }

	float getValoareEnergetica() { return this->valoareEnergetica; }

	float getGrasimi() { return this->grasimi; }

	float getCarbohidrati() { return this->carbohidrati; }

	float getProteine() { return this->proteine; }

	int getNrGramaje() { return this->nrGramaje; }

	float* getGramaj()
	{ 
		/*if (this->gramaj != NULL && this->nrGramaje > 0)
		{
			return gramaj;
		}
		else throw new exception("Nu exista tipuri de gramaje.");*/
		return gramaj;
	}

	float* getPreturi()
	{
		return preturi;
	}
	//Setter
	static void setBasicId(int id) { if (id >= 0) basicId = id; }

	void setNume(string nume)
	{
		if (this->nume != nume)
		{
			this->nume = nume;
		}
		else
			cout << "Deja acest obiect este denumit asa.";
	}

	void setValoareEnergetica(float val)
	{
		if (val >= 0)
			this->valoareEnergetica = val;
		else
			cout << "Valoarea energetica nu poate fi mai mica decat 0.";
	}

	void setGrasimi(float grasimi)
	{
		if (grasimi > 0)
			this->grasimi = grasimi;
		else
			cout << "Grasimile nu pot fi mai mici decat 0.";
	}

	void setCarbohidrati(float carbo)
	{
		if (carbo > 0)
			this->carbohidrati = carbo;
		else
			cout << "Carbohidratii nu pot fi mai mici decat 0";
	}

	void setProteine(float proteine)
	{
		if (proteine > 0)
			this->proteine = proteine;
		else
			cout << "Proteinele nu pot fi mai mici decat 0";
	}

	void setNrGramaje(int nr)
	{
		if (nr > 0)
		{
			this->nrGramaje = nr;
		}
		if (nr == 0)
		{
			this->nrGramaje = 0;
			this->gramaj = NULL;
			this->preturi = NULL;
		}
		if(nr < 0)
			throw new exception("Nu poti avea un nr de gramaje mai mic ca 0");
	}

	void setGramaj(int nrGramaje, float* gramaj) 
	{
		if (nrGramaje > 0 && gramaj != NULL)
		{
			delete[] this->gramaj;
			this->gramaj = new float[nrGramaje];
			for (int i = 0; i < nrGramaje; i++)
			{
				this->gramaj[i] = gramaj[i];
			}
		}
	}

	void setPreturi(int nrPreturi, float* preturi)
	{
		if (nrPreturi > 0 && preturi != NULL)
		{
			delete[] this->preturi;
			this->preturi = new float[nrPreturi];
			for (int i = 0; i < nrPreturi; i++)
			{
				this->preturi[i] = preturi[i];
			}
		}
	}

	friend ostream& operator<<(ostream& out, const Suplimente& s);
	friend istream& operator>>(istream& in, Suplimente& s);
};

ostream& operator<<(ostream& out, const Suplimente& s)
{
	out << "\n Id Produs: " << s.idProdus;
	out << "\n Denumire: " << s.nume;
	out << "\n Valoare energetica: " << s.valoareEnergetica<<" kcal";
	out << "\n Grasimi: " << s.grasimi << " g";
	out << "\n Carbohidrati: " << s.carbohidrati << " g";
	out << "\n Proteine: " << s.proteine << " g";
	out << "\n Lista gramaje: ";
	if (s.gramaj != NULL && s.nrGramaje > 0)
	{
		for (int i = 0; i < s.nrGramaje; i++)
		{
			out << s.gramaj[i] << " ";
		}
		cout << " (grame)";
	}
	else
		out << " - ";
	cout << "\n Lista preturi: ";
	if (s.preturi != NULL && s.nrGramaje > 0)
	{
		for (int i = 0; i < s.nrGramaje; i++)
		{
			out << s.preturi[i] << " ";
		}
		cout << " (lei)";
	}
	else
		out << " - ";
	return out;
}
istream& operator>>(istream& in, Suplimente& s)
{
	cout << "\n Introduceti denumire produs: ";
	in >> s.nume;
	cout << " \n Introduceti valoare energetica: ";
	in >> s.valoareEnergetica;
	cout << "\n Introduceti grasimi: ";
	in >> s.grasimi;
	cout << "\n Introduceti carbohidrati: ";
	in >> s.carbohidrati;
	cout << "\n Introduceti proteine: ";
	in >> s.proteine;
	cout << "\n Introduceti numarul de gramaje disponibile: ";
	in >> s.nrGramaje;
	delete[] s.gramaj;
	delete[] s.preturi;
	if (s.nrGramaje > 0)
	{
		s.gramaj = new float[s.nrGramaje];
		s.preturi = new float[s.nrGramaje];
		for (int i = 0; i < s.nrGramaje; i++)
		{
			cout << "\n Introduceti gramajul cu numarul "<< i+1 <<" : ";
			in >> s.gramaj[i];
			cout << endl;
			cout << "\n Introduceti pretul gramajului cu numarul " << i + 1 << " : ";
			in >> s.preturi[i];
			cout << endl;
		}
	}
	else
	{
		s.nrGramaje = 0;
		s.gramaj = NULL;
		s.preturi = NULL;
	}
	return in;
}

enum TipProteina
{
	Whey = 1, Izolat = 2
};

class Proteine : public Suplimente
{
private:

	TipProteina tip = TipProteina::Whey;
	int nrArome = 0;
	string* arome = NULL;

public:

	//Constructor default
	Proteine() :Suplimente()
	{
	}

	//Constructor cu parametrii
	Proteine(string nume, float valoareEnergetica, float grasimi, float carbohidrati, float proteine, int nrGramaje, float* gramaj, float* preturi, TipProteina tip, int nrArome, string* arome):Suplimente(nume,valoareEnergetica,grasimi,carbohidrati,proteine,nrGramaje,gramaj,preturi)
	{
		this->tip = tip;
		if (arome != NULL && nrArome > 0)
		{
			this->arome = new string[nrArome];
			this->nrArome = nrArome;
			for (int i = 0; i < nrArome; i++)
			{
				this->arome[i] = arome[i];
			}
		}
		else
		{
			this->arome = NULL;
			this->nrArome = 0;
		}
	}

	//Constructor cu parametrii 2
	Proteine(Suplimente s, TipProteina tip, int nrArome, string* arome) :Suplimente(s)
	{
		this->tip = tip;
		if (arome != NULL && nrArome > 0)
		{
			this->arome = new string[nrArome];
			this->nrArome = nrArome;
			for (int i = 0; i < nrArome; i++)
			{
				this->arome[i] = arome[i];
			}
		}
		else
		{
			this->arome = NULL;
			this->nrArome = 0;
		}
	}

	//Constructor copiere
	Proteine(const Proteine& p) :Suplimente(p)
	{
		this->tip = p.tip;
		if (p.arome != NULL && p.nrArome > 0)
		{
			this->arome = new string[p.nrArome];
			this->nrArome = p.nrArome;
			for (int i = 0; i < this->nrArome; i++)
			{
				this->arome[i] = p.arome[i];
			}
		}
		else
		{
			this->arome = NULL;
			this->nrArome = 0;
		}
	}

	//Operator =
	Proteine& operator=(const Proteine& p)
	{
		Suplimente::operator=(p);
		this->tip = p.tip;
		if (p.arome != NULL && p.nrArome > 0)
		{
			this->arome = new string[p.nrArome];
			this->nrArome = p.nrArome;
			for (int i = 0; i < this->nrArome; i++)
			{
				this->arome[i] = p.arome[i];
			}
		}
		else
		{
			this->arome = NULL;
			this->nrArome = 0;
		}
		return *this;
	}

	//Destructor
	~Proteine()
	{
		delete[] arome;
	}

	//Operator indexare[]
	string& operator[](int index)
	{
		return this->arome[index];
	}

	//Operator + 
	Proteine operator+ (int nrArome)
	{
		Proteine aux = *this;
		if (nrArome > 0)
		{
			aux.nrArome += nrArome;
			delete[] aux.arome;
			int a = this->nrArome;
			aux.arome = new string[aux.nrArome];
			for (int i = 0; i < this->nrArome; i++)
				aux.arome[i] = this->arome[i];
			for (int i = a; i < aux.nrArome; i++)
				aux.arome[i] = "N/A";
		}
		return aux;
	}

	//Operator ++ preincrementare -- Adauga o noua aroma 
	Proteine operator++()
	{
		Proteine aux = *this;
		if (this->nrArome > 0)
		{
			this->nrArome++;
			delete[] this->arome;
			for (int i = 0; i < aux.nrArome; i++)
			{
				this->arome[i] = aux.arome[i];
			}
			this->arome[this->nrArome - 1] = "Aroma noua necunoscuta";
		}
		return *this;
	}

	//Operator ++ postincrementare -- Adauga o noua aroma
	Proteine operator++(int)
	{
		Proteine aux = *this;
		if (aux.nrArome > 0)
		{
			aux.nrArome++;
			delete[] aux.arome;
			aux.arome = new string[aux.nrArome];
			for (int i = 0; i < this->nrArome; i++) 
			{
				aux.arome[i] = this->arome[i];
			}
			aux.arome[aux.nrArome - 1] = "Aroma noua necunoscuta";
		}
		return aux;
	}

	//Operator cast la string
	operator string()
	{
		return this->nume;
	}

	//Operator cast la float
	operator float()
	{
		return this->valoareEnergetica;
	}

	//Operator negatie - sterge aromele
	Proteine operator!()
	{
		Proteine aux = *this;
		delete[] aux.arome;
		aux.nrArome = 0;
		return aux;
	}

	// Operator < - compara valoarea energetica
	bool operator<(const Proteine& p)
	{
		if (this->valoareEnergetica < p.valoareEnergetica)
			return true;
		else
			return false;
	}

	//Operator == 
	bool operator==(const Proteine& p)
	{
		if (this->valoareEnergetica == p.valoareEnergetica)
			return true;
		else
			return false;
	}

	//Getter
	int getNrArome()
	{
		return this->nrArome;
	}

	string* getArome()
	{
		return this->arome;
	}

	//Setter
	void setNrArome(int nr)
	{
		if (nr > 0)
		{
			this->nrArome = nr;
		}
	}

	void setArome(int nr, string* arome)
	{
		if (nr > 0 && arome != NULL)
		{
			delete[] this->arome;
			this->arome = new string[nr];
			for (int i = 0; i < nr; i++)
			{
				this->arome[i] = arome[i];
			}
		}
	}

	friend ostream& operator<<(ostream& out, const Proteine& p)
	{
		out << (Suplimente)p;
		out << "\n Tip proteina : ";
		switch (p.tip)
		{
		case 1:
			cout << " Whey";
			break;
		case 2: 
			cout << " Izolat";
			break;
		default:
			cout << " N/A";
			break;
		}
		if (p.arome != NULL && p.nrArome > 0)
		{
			out << "\n Arome: ";
			for (int i = 0; i < p.nrArome; i++)
			{
				out << p.arome[i] << " ";
			}
		}
		return out;
	}
	friend istream& operator>>(istream& in, Proteine& p)
	{
		int tip;
		cout << "\n Introduceti denumire produs: ";
		in >> p.nume;
		cout << " \n Introduceti valoare energetica: ";
		in >> p.valoareEnergetica;
		cout << "\n Introduceti grasimi: ";
		in >> p.grasimi;
		cout << "\n Introduceti carbohidrati: ";
		in >> p.carbohidrati;
		cout << "\n Introduceti proteine: ";
		in >> p.proteine;
		cout << "\n Introduceti numarul de gramaje disponibile: ";
		in >> p.nrGramaje;
		delete[] p.gramaj;
		delete[] p.preturi;
		if (p.nrGramaje > 0)
		{
			p.gramaj = new float[p.nrGramaje];
			p.preturi = new float[p.nrGramaje];
			for (int i = 0; i < p.nrGramaje; i++)
			{
				cout << "\n Introduceti gramajul cu numarul " << i + 1 << " : ";
				in >> p.gramaj[i];
				cout << endl;
				cout << "\n Introduceti pretul gramajului cu numarul " << i + 1 << " : ";
				in >> p.preturi[i];
				cout << endl;
			}
		}
		else
		{
			p.nrGramaje = 0;
			p.gramaj = NULL;
			p.preturi = NULL;
		}
		cout << "\n Introduceti tipul de proteina: 1 = Whey, 2 = Izolat : ";
		in >> tip;
		switch (tip)
		{
		case 1:
			p.tip = TipProteina::Whey;
			break;
		case 2:
			p.tip = TipProteina::Izolat;
			break;
		default:
			p.tip = TipProteina::Izolat;
			break;
		}
		cout << "\n Introduceti numarul de arome: ";
		in >> p.nrArome;
		delete[] p.arome;
		if (p.nrArome > 0)
		{
			p.arome = new string[p.nrArome];
			for (int i = 0; i < p.nrArome; i++)
			{
				cout << "\n Introduceti aroma: ";
				in >> p.arome[i];
				cout << endl;
			}
		}
		else
		{
			p.nrArome = 0;
			p.arome = NULL;
		}
		return in;
	}
}; 

enum TipCarbo
{
	AbsortieLenta = 1, AbsortieRapida = 2
};

class Carbohidrati : public Suplimente
{

private:

	TipCarbo tip = TipCarbo::AbsortieLenta;
	int nrArome = 0;
	string* arome = NULL;

public:
	//Constructor default
	Carbohidrati():Suplimente()
	{
	}

	//Constructor cu parametrii
	Carbohidrati(string nume, float valoareEnergetica, float grasimi, float carbohidrati, float proteine, int nrGramaje, float* gramaj, float* preturi, TipCarbo tip, int nrArome, string* arome) :Suplimente(nume, valoareEnergetica, grasimi, carbohidrati, proteine, nrGramaje, gramaj, preturi)
	{
		this->tip = tip;
		if (arome != NULL && nrArome > 0)
		{
			this->arome = new string[nrArome];
			this->nrArome = nrArome;
			for (int i = 0; i < nrArome; i++)
			{
				this->arome[i] = arome[i];
			}
		}
		else
		{
			this->arome = NULL;
			this->nrArome = 0;
		}
	}

	//Constructor cu parametrii 2
	Carbohidrati(Suplimente s, TipCarbo tip, int nrArome, string* arome) :Suplimente(s)
	{
		this->tip = tip;
		if (arome != NULL && nrArome > 0)
		{
			this->arome = new string[nrArome];
			this->nrArome = nrArome;
			for (int i = 0; i < nrArome; i++)
			{
				this->arome[i] = arome[i];
			}
		}
		else
		{
			this->arome = NULL;
			this->nrArome = 0;
		}
	}

	//Constructor copiere
	Carbohidrati(const Carbohidrati& c) :Suplimente(c)
	{
		this->tip = c.tip;
		if (c.arome != NULL && c.nrArome > 0)
		{
			this->arome = new string[c.nrArome];
			this->nrArome = c.nrArome;
			for (int i = 0; i < this->nrArome; i++)
			{
				this->arome[i] = c.arome[i];
			}
		}
		else
		{
			this->arome = NULL;
			this->nrArome = 0;
		}
	}

	//Operator =
	Carbohidrati& operator=(const Carbohidrati& c)
	{
		Suplimente::operator=(c);
		this->tip = c.tip;
		if (c.arome != NULL && c.nrArome > 0)
		{
			this->arome = new string[c.nrArome];
			this->nrArome = c.nrArome;
			for (int i = 0; i < this->nrArome; i++)
			{
				this->arome[i] = c.arome[i];
			}
		}
		else
		{
			this->arome = NULL;
			this->nrArome = 0;
		}
		return *this;
	}

	//Destructor
	~Carbohidrati()
	{
		delete[] this->arome;
	}

	string& operator[](int index)
	{
		return this->arome[index];
	}

	//Operator + 
	Carbohidrati operator+ (int nrArome)
	{
		Carbohidrati aux = *this;
		if (nrArome > 0)
		{
			aux.nrArome += nrArome;
			delete[] aux.arome;
			int a = this->nrArome;
			aux.arome = new string[aux.nrArome];
			for (int i = 0; i < this->nrArome; i++)
				aux.arome[i] = this->arome[i];
			for (int i = a; i < aux.nrArome; i++)
				aux.arome[i] = "N/A";
		}
		return aux;
	}

	//Operator ++ preincrementare -- Adauga o noua aroma 
	Carbohidrati operator++()
	{
		Carbohidrati aux = *this;
		if (this->nrArome > 0)
		{
			this->nrArome++;
			delete[] this->arome;
			for (int i = 0; i < aux.nrArome; i++)
			{
				this->arome[i] = aux.arome[i];
			}
			this->arome[this->nrArome - 1] = "Aroma noua necunoscuta";
		}
		return *this;
	}

	//Operator ++ postincrementare -- Adauga o noua aroma
	Carbohidrati operator++(int)
	{
		Carbohidrati aux = *this;
		if (aux.nrArome > 0)
		{
			aux.nrArome++;
			delete[] aux.arome;
			aux.arome = new string[aux.nrArome];
			for (int i = 0; i < this->nrArome; i++)
			{
				aux.arome[i] = this->arome[i];
			}
			aux.arome[aux.nrArome - 1] = "Aroma noua necunoscuta";
		}
		return aux;
	}

	//Operator cast la string
	operator string()
	{
		return this->nume;
	}

	//Operator cast la float
	operator float()
	{
		return this->valoareEnergetica;
	}

	//Operator negatie - sterge aromele
	Carbohidrati operator!()
	{
		Carbohidrati aux = *this;
		delete[] aux.arome;
		aux.nrArome = 0;
		return aux;
	}

	// Operator < - compara valoarea energetica
	bool operator<(const Carbohidrati& p)
	{
		if (this->valoareEnergetica < p.valoareEnergetica)
			return true;
		else
			return false;
	}

	//Operator == 
	bool operator==(const Carbohidrati& p)
	{
		if (this->valoareEnergetica == p.valoareEnergetica)
			return true;
		else
			return false;
	}

	//Getter
	int getNrArome()
	{
		return this->nrArome;
	}

	string* getArome()
	{
		return this->arome;
	}

	//Setter
	void setNrArome(int nr)
	{
		if (nr > 0)
		{
			this->nrArome = nr;
		}
	}

	void setArome(int nr, string* arome)
	{
		if (nr > 0 && arome != NULL)
		{
			delete[] this->arome;
			this->arome = new string[nr];
			for (int i = 0; i < nr; i++)
			{
				this->arome[i] = arome[i];
			}
		}
	}

	friend ostream& operator<<(ostream& out, const Carbohidrati& c)
	{
		out << (Suplimente)c;
		out << "\n Tip carbohidrati : ";
		switch (c.tip)
		{
		case 1:
			cout << " Absortie lenta";
			break;
		case 2:
			cout << " Absortie rapida";
		default:
			cout << " N/A";
			break;
		}
		if (c.arome != NULL && c.nrArome > 0)
		{
			out << "\n Arome: ";
			for (int i = 0; i < c.nrArome; i++)
			{
				out << c.arome[i] << ", ";
			}
		}
		return out;
	}
	friend istream& operator>>(istream& in, Carbohidrati& c)
	{
		int tip;
		cout << "\n Introduceti denumire produs: ";
		in >> c.nume;
		cout << " \n Introduceti valoare energetica: ";
		in >> c.valoareEnergetica;
		cout << "\n Introduceti grasimi: ";
		in >> c.grasimi;
		cout << "\n Introduceti carbohidrati: ";
		in >> c.carbohidrati;
		cout << "\n Introduceti proteine: ";
		in >> c.proteine;
		cout << "\n Introduceti numarul de gramaje disponibile: ";
		in >> c.nrGramaje;
		delete[] c.gramaj;
		delete[] c.preturi;
		if (c.nrGramaje > 0)
		{
			c.gramaj = new float[c.nrGramaje];
			c.preturi = new float[c.nrGramaje];
			for (int i = 0; i < c.nrGramaje; i++)
			{
				cout << "\n Introduceti gramajul cu numarul " << i + 1 << " : ";
				in >> c.gramaj[i];
				cout << endl;
				cout << "\n Introduceti pretul gramajului cu numarul " << i + 1 << " : ";
				in >> c.preturi[i];
				cout << endl;
			}
		}
		else
		{
			c.nrGramaje = 0;
			c.gramaj = NULL;
			c.preturi = NULL;
		}
		cout << "\n Introduceti tipul de carbo: 1 = Absortie lenta, 2 = Absortie rapida : ";
		in >> tip;
		switch (tip)
		{
		case 1:
			c.tip = TipCarbo::AbsortieLenta;
			break;
		case 2:
			c.tip = TipCarbo::AbsortieRapida;
			break;
		default:
			c.tip = TipCarbo::AbsortieLenta;
			break;
		}
		cout << "\n Introduceti numarul de arome: ";
		in >> c.nrArome;
		delete[] c.arome;
		if (c.nrArome > 0)
		{
			c.arome = new string[c.nrArome];
			for (int i = 0; i < c.nrArome; i++)
			{
				cout << "\n Introduceti aroma: ";
				in >> c.arome[i];
				cout << endl;
			}
		}
		else
		{
			c.nrArome = 0;
			c.arome = NULL;
		}
		return in;
	}
};

enum TipAmino
{
	AminoComplecsi = 1, BCA = 2, EAA = 3, Arginina = 4, Glutamina = 5, Altii = 6
};


class Aminoacizi : public Suplimente 
{
private:

	TipAmino categorie = TipAmino::AminoComplecsi;
	string tip[50] = {};
	int nrTip = 0;

public:
	//Constructor default
	Aminoacizi() :Suplimente()
	{
	}

	//Constructor cu parametrii
	Aminoacizi(string nume, float valoareEnergetica, float grasimi, float carbohidrati, float proteine, int nrGramaje, float* gramaj, float* preturi, TipAmino categorie, string tip[], int nrTip) :Suplimente(nume, valoareEnergetica, grasimi, carbohidrati, proteine, nrGramaje, gramaj, preturi)
	{
		this->categorie = categorie;
		if (nrTip > 0 && nrTip < 50 && tip)
		{
			this->nrTip = nrTip;

			for (int i = 0; i < this->nrTip; i++)
			{
				this->tip[i] = tip[i];
			}
		}
	}

	//Constructor cu parametrii 2
	Aminoacizi(Suplimente s, TipAmino categorie, string tip[], int nrTip):Suplimente(s)
	{
		this->categorie = categorie;
		if (nrTip > 0 && nrTip < 50 && tip)
		{
			this->nrTip = nrTip;

			for (int i = 0; i < this->nrTip; i++)
			{
				this->tip[i] = tip[i];
			}
		}
	}

	//Constructor de copiere
	Aminoacizi(const Aminoacizi& a) :Suplimente(a)
	{
		this->categorie = a.categorie;
		if (a.nrTip > 0 && a.nrTip < 50 && a.tip)
		{
			this->nrTip = a.nrTip;
			for (int i = 0; i < this->nrTip; i++)
			{
				this->tip[i] = a.tip[i];
			}
		}
	}

	//Operator =
	Aminoacizi& operator=(const Aminoacizi& a)
	{
		Suplimente::operator=(a);
		this->categorie = a.categorie;
		if (a.nrTip > 0 && a.nrTip < 50 && a.tip)
		{
			this->nrTip = a.nrTip;
			for (int i = 0; i < this->nrTip; i++)
			{
				this->tip[i] = a.tip[i];
			}
		}
		return *this;
	}

	//Destructor
	~Aminoacizi()
	{

	}

	//operator [] index
	string& operator[](int index)
	{
		if(index >=0 && index < 50)
		{ 
			return this->tip[index];
		}
	}

	//operator + 
	Aminoacizi operator+(float nrCalorii)
	{
		Aminoacizi aux = *this;
		if (nrCalorii >= 0)
			aux.valoareEnergetica += nrCalorii;
		return aux;
	}

	//Operator ++ preincrementare --- adauga un nou gramaj,un nou pret, dublandu-l pe ultimul.
	Aminoacizi operator++()
	{
		Aminoacizi aux = *this;
		if (this->nrGramaje > 0)
		{
			this->nrGramaje++;
			delete[] this->gramaj;
			delete[] this->preturi;
			this->gramaj = new float[this->nrGramaje];
			this->preturi = new float[this->nrGramaje];
			for (int i = 0; i < aux.nrGramaje; i++)
			{
				this->gramaj[i] = aux.gramaj[i];
				this->preturi[i] = aux.preturi[i];
			}
			this->gramaj[this->nrGramaje - 1] = this->gramaj[aux.nrGramaje - 1] * 2;
			this->preturi[this->nrGramaje - 1] = this->preturi[aux.nrGramaje - 1] * 2;
		}
		return *this;
	}

	//Operator ++ postincrementare --- adauga un nou gramaj, dublandu-l pe ultimul.
	Aminoacizi operator++(int)
	{
		Aminoacizi aux = *this;
		if (aux.nrGramaje > 0)
		{
			aux.nrGramaje++;
			delete[] aux.gramaj;
			delete[] aux.preturi;
			aux.gramaj = new float[aux.nrGramaje];
			aux.preturi = new float[aux.nrGramaje];
			for (int i = 0; i < this->nrGramaje; i++)
			{
				aux.gramaj[i] = this->gramaj[i];
				aux.preturi[i] = this->preturi[i];
			}
			aux.gramaj[aux.nrGramaje - 1] = aux.gramaj[this->nrGramaje - 1] * 2;
			aux.preturi[aux.nrGramaje - 1] = aux.preturi[this->nrGramaje - 1] * 2;
		}
		return aux;
	}

	//Operator cast la string
	operator string()
	{
		return this->nume;
	}

	//Operator cast la float - valoareEnergetica
	operator float()
	{
		return this->valoareEnergetica;
	}

	//Operator negatie - sterge gramajele
	Aminoacizi operator!()
	{
		Aminoacizi aux = *this;
		delete[] aux.gramaj;
		delete[] aux.preturi;
		aux.gramaj = NULL;
		aux.preturi = NULL;
		aux.nrGramaje = 0;
		return aux;
	}

	//Operator < - compara valoarea energetica
	bool operator<(const Aminoacizi& s)
	{
		if (this->valoareEnergetica < s.valoareEnergetica)
			return true;
		else
			return false;
	}

	//Operator == compara valoarea energetica
	bool operator==(const Aminoacizi& s)
	{
		if (this->valoareEnergetica == s.valoareEnergetica)
			return true;
		else
			return false;
	}
	//Getter
	string* getTip()
	{
		string* tip = new string[this->nrTip];
		for (int i = 0; i < this->nrTip; i++)
		{
			tip[i] = this->tip[i];
		}
		return tip;
	}
	//Setter
	void setTip(string tip[50])
	{
		if (this->nrTip > 0)
		{
		for (int i = 0; i < this->nrTip; i++)
			this->tip[i] = tip[i];
		}
	}
	friend ostream& operator<<(ostream& out, const Aminoacizi& p)
	{
		out << (Suplimente)p;
		out << "\n Tip aminoacid : ";
		switch (p.categorie)
		{
		case 1:
			out << " Aminoacid complex";
			break;
		case 2:
			out << " BCAA";
			break;
		case 3:
			out << " EAA";
			break;
		case 4:
			out << " Arginina";
			break;
		case 5:
			out << " Glutamina";
			break;
		case 6: 
			out << " Altii";
			break;
		default:
			out << " N/A";
			break;
		}
		out << " \n Numarul de tipuri de administrare: " << p.nrTip;

		if (p.nrTip > 0 && p.nrTip < 50 && p.tip)
		{
			out << "\n Tipuri administrare: ";
			for (int i = 0; i < p.nrTip; i++)
			{
				out << p.tip[i] << " ";
			}
		}
		return out;
	}
	friend istream& operator>>(istream& in, Aminoacizi& c)
	{
		int categorie;
		cout << "\n Introduceti denumire produs: ";
		in >> c.nume;
		cout << " \n Introduceti valoare energetica: ";
		in >> c.valoareEnergetica;
		cout << "\n Introduceti grasimi: ";
		in >> c.grasimi;
		cout << "\n Introduceti carbohidrati: ";
		in >> c.carbohidrati;
		cout << "\n Introduceti proteine: ";
		in >> c.proteine;
		cout << "\n Introduceti numarul de gramaje disponibile: ";
		in >> c.nrGramaje;
		delete[] c.gramaj;
		delete[] c.preturi;
		if (c.nrGramaje > 0)
		{
			c.gramaj = new float[c.nrGramaje];
			c.preturi = new float[c.nrGramaje];
			for (int i = 0; i < c.nrGramaje; i++)
			{
				cout << "\n Introduceti gramajul cu numarul " << i + 1 << " : ";
				in >> c.gramaj[i];
				cout << endl;
				cout << "\n Introduceti pretul gramajului cu numarul " << i + 1 << " : ";
				in >> c.preturi[i];
				cout << endl;
			}
		}
		else
		{
			c.nrGramaje = 0;
			c.gramaj = NULL;
			c.preturi = NULL;
		}
		cout << "\n Introduceti tipul de aminoacid";
		cout << "\n 1. Amino Complecsi 2. BCA 3. EAA 4.Arginita 5.Glutamina 6. Altii: ";
		in >> categorie;
		switch (categorie)
		{
		case 1:
			c.categorie = TipAmino::AminoComplecsi;
			break;
		case 2:
			c.categorie = TipAmino::BCA;
			break;
		case 3:
			c.categorie = TipAmino::EAA;
			break;
		case 4:
			c.categorie = TipAmino::Arginina;
			break;
		case 5:
			c.categorie = TipAmino::Glutamina;
			break;
		case 6:
			c.categorie = TipAmino::Altii;
			break;
		default:
			c.categorie = TipAmino::Altii;
			break;
		}
		cout << "\n Introduceti nr de tipuri de administrare( Maxim 50) : ";
		in >> c.nrTip;
		
		if (c.nrTip > 0 && c.nrTip < 50 && c.tip)
		{
			for (int i = 0; i < c.nrTip; i++)
			{
				cout << "\n Introduceti tipul "<< i+1 <<" de administrare: ";
				in >> c.tip[i];
				cout << endl;
			}
		}
		return in;
	}
};

enum TipCreatina
{
	Monohidrata = 1, Multicomponenta = 2
};

class Creatina : public Suplimente
{
private:

	TipCreatina categorie = TipCreatina::Monohidrata;
	string tip[50] = {};
	int nrTip = 0;

public:
	//Constructor default
	Creatina() :Suplimente()
	{
	}
	//Constructor cu parametrii
	Creatina(string nume, float valoareEnergetica, float grasimi, float carbohidrati, float proteine, int nrGramaje, float* gramaj, float* preturi, TipCreatina categorie, string tip[],int nrTip) :Suplimente(nume, valoareEnergetica, grasimi, carbohidrati, proteine, nrGramaje, gramaj, preturi)
	{
		this->categorie = categorie;
		if (nrTip > 0 && nrTip < 50 && tip)
		{
			this->nrTip = nrTip;
			for (int i = 0; i <this->nrTip ; i++)
			{
				this->tip[i] = tip[i];
			}
		}
	}
	//Constructor cu parametrii 2
	Creatina(Suplimente s, TipCreatina categorie, string tip[]) :Suplimente(s)
	{
		this->categorie = categorie;
		if (nrTip > 0 && nrTip < 50 && tip)
		{
			this->nrTip = nrTip;
			for (int i = 0; i < this->nrTip; i++)
			{
				this->tip[i] = tip[i];
			}
		}
	}
	//Constructor de copiere
	Creatina(const Creatina& a) :Suplimente(a)
	{
		this->categorie = a.categorie;
		if (a.nrTip > 0 && a.nrTip < 50 && a.tip)
		{
			this->nrTip = a.nrTip;
			for (int i = 0; i < this->nrTip; i++)
			{
				this->tip[i] = a.tip[i];
			}
		}
	}
	//Operator =
	Creatina& operator=(const Creatina& a)
	{
		Suplimente::operator=(a);
		this->categorie = a.categorie;
		if (a.nrTip > 0 && a.nrTip < 50 && a.tip)
		{
			this->nrTip = a.nrTip;
			for (int i = 0; i < this->nrTip; i++)
			{
				this->tip[i] = a.tip[i];
			}
		}
		return *this;
	}
	//Destructor
	~Creatina()
	{

	}
	//operator [] index
	string& operator[](int index)
	{
		if (index >= 0 && index < 50)
		{
			return this->tip[index];
		}
	}
	//operator + 
	Creatina operator+(float nrCalorii)
	{
		Creatina aux = *this;
		if (nrCalorii >= 0)
			aux.valoareEnergetica += nrCalorii;
		return aux;
	}
	//Operator ++ preincrementare --- adauga un nou gramaj,un nou pret, dublandu-l pe ultimul.
	Creatina operator++()
	{
		Creatina aux = *this;
		if (this->nrGramaje > 0)
		{
			this->nrGramaje++;
			delete[] this->gramaj;
			delete[] this->preturi;
			this->gramaj = new float[this->nrGramaje];
			this->preturi = new float[this->nrGramaje];
			for (int i = 0; i < aux.nrGramaje; i++)
			{
				this->gramaj[i] = aux.gramaj[i];
				this->preturi[i] = aux.preturi[i];
			}
			this->gramaj[this->nrGramaje - 1] = this->gramaj[aux.nrGramaje - 1] * 2;
			this->preturi[this->nrGramaje - 1] = this->preturi[aux.nrGramaje - 1] * 2;
		}
		return *this;
	}

	//Operator ++ postincrementare --- adauga un nou gramaj, dublandu-l pe ultimul.
	Creatina operator++(int)
	{
		Creatina aux = *this;
		if (aux.nrGramaje > 0)
		{
			aux.nrGramaje++;
			delete[] aux.gramaj;
			delete[] aux.preturi;
			aux.gramaj = new float[aux.nrGramaje];
			aux.preturi = new float[aux.nrGramaje];
			for (int i = 0; i < this->nrGramaje; i++)
			{
				aux.gramaj[i] = this->gramaj[i];
				aux.preturi[i] = this->preturi[i];
			}
			aux.gramaj[aux.nrGramaje - 1] = aux.gramaj[this->nrGramaje - 1] * 2;
			aux.preturi[aux.nrGramaje - 1] = aux.preturi[this->nrGramaje - 1] * 2;
		}
		return aux;
	}
	//Operator cast la string
	operator string()
	{
		return this->nume;
	}

	//Operator cast la float - valoareEnergetica
	operator float()
	{
		return this->valoareEnergetica;
	}

	//Operator negatie - sterge gramajele
	Creatina operator!()
	{
		Creatina aux = *this;
		delete[] aux.gramaj;
		delete[] aux.preturi;
		aux.gramaj = NULL;
		aux.preturi = NULL;
		aux.nrGramaje = 0;
		return aux;
	}

	//Operator < - compara valoarea energetica
	bool operator<(const Creatina& s)
	{
		if (this->valoareEnergetica < s.valoareEnergetica)
			return true;
		else
			return false;
	}

	//Operator == compara valoarea energetica
	bool operator==(const Creatina& s)
	{
		if (this->valoareEnergetica == s.valoareEnergetica)
			return true;
		else
			return false;
	}
	//Getter
	string* getTip()
	{
		string* tip = new string[this->nrTip];
		for (int i = 0; i < this->nrTip; i++)
		{
			tip[i] = this->tip[i];
		}
		return tip;
	}
	//Setter
	void setTip(string tip[50])
	{
		if (this->nrTip > 0)
		{
			for (int i = 0; i < this->nrTip; i++)
				this->tip[i] = tip[i];
		}
	}
	friend ostream& operator<<(ostream& out, const Creatina& p)
	{
		out << (Suplimente)p;
		out << "\n Tip creatina : ";
		switch (p.categorie)
		{
		case 1:
			out << " Monohidrata";
			break;
		case 2:
			out << " Multicomponenta";
			break;
		default:
			out << " N/A";
			break;
		}
		out << "\n Numarul de tipuri de administrare: ";
		out << p.nrTip;
		if (p.nrTip > 0 && p.nrTip < 50 && p.tip)
		{
			out << "\n Tipuri administrare: ";
			for (int i = 0; i < p.nrTip; i++)
			{
				out << p.tip[i] << " ";
			}
		}
		return out;
	}
	friend istream& operator>>(istream& in, Creatina& c)
	{
		int categorie;
		cout << "\n Introduceti denumire produs: ";
		in >> c.nume;
		cout << " \n Introduceti valoare energetica: ";
		in >> c.valoareEnergetica;
		cout << "\n Introduceti grasimi: ";
		in >> c.grasimi;
		cout << "\n Introduceti carbohidrati: ";
		in >> c.carbohidrati;
		cout << "\n Introduceti proteine: ";
		in >> c.proteine;
		cout << "\n Introduceti numarul de gramaje disponibile: ";
		in >> c.nrGramaje;
		delete[] c.gramaj;
		delete[] c.preturi;
		if (c.nrGramaje > 0)
		{
			c.gramaj = new float[c.nrGramaje];
			c.preturi = new float[c.nrGramaje];
			for (int i = 0; i < c.nrGramaje; i++)
			{
				cout << "\n Introduceti gramajul cu numarul " << i + 1 << " : ";
				in >> c.gramaj[i];
				cout << endl;
				cout << "\n Introduceti pretul gramajului cu numarul " << i + 1 << " : ";
				in >> c.preturi[i];
				cout << endl;
			}
		}
		else
		{
			c.nrGramaje = 0;
			c.gramaj = NULL;
			c.preturi = NULL;
		}
		cout << "\n Introduceti tipul de creatina ";
		cout << "\n 1. Monohidrata 2.Multicomponenta :";
		in >> categorie;
		switch (categorie)
		{
		case 1:
			c.categorie = TipCreatina::Monohidrata;
			break;
		case 2:
			c.categorie = TipCreatina::Multicomponenta;
		default:
			c.categorie = TipCreatina::Monohidrata;
			break;
		}
		cout << "\n Introduceti nr de tipuri de administrare( Maxim 50) : ";
		in >> c.nrTip;
		cout << "\n Introduceti tipurile : ";
		if (c.nrTip > 0 && c.nrTip < 50 && c.tip)
		{
			for (int i = 0; i < c.nrTip; i++)
			{
				in >> c.tip[i];
				cout << endl;
			}
		}
		return in;
	}
};


class Imbracaminte
{

private:

	static int basicId;
	const int idProdus;
	string marca;
	string culoare;
	int anAparitie;
	int nrMarimi;
	float* marimi;
	float* preturi;

public:

	//Constructor default
	Imbracaminte() : idProdus(++basicId + 500), marca("N/A"), culoare("N/A"), anAparitie(0),nrMarimi(0), marimi(NULL), preturi(NULL)
	{
	}

	//Constructor cu parametrii
	Imbracaminte(string marca, string culoare, int anAparitie, int nrMarimi, float* marimi, float* preturi) : idProdus(++basicId + 500)
	{

		this->marca = marca;
		this->culoare = culoare;
		this->anAparitie = anAparitie;
		if (nrMarimi != 0 && marimi != NULL)
		{
			this->nrMarimi = nrMarimi;
			this->marimi = new float[nrMarimi];
			for (int i = 0; i < this->nrMarimi; i++)
				this->marimi[i] = marimi[i];
		}
		else
		{
			this->nrMarimi = 0;
			this->marimi = NULL;
		}
		if (nrMarimi != 0 && preturi != NULL)
		{
			this->nrMarimi = nrMarimi;
			this->preturi = new float[nrMarimi];
			for (int i = 0; i < this->nrMarimi; i++)
				this->preturi[i] = preturi[i];
		}
		else
		{
			this->nrMarimi = 0;
			this->preturi = NULL;
		}

	}

	//Constructor copiere
	Imbracaminte(const Imbracaminte& s) : marca(s.marca), culoare(s.culoare), anAparitie(s.anAparitie), idProdus(++basicId + 500)
	{
		if (s.marimi != NULL && s.nrMarimi > 0)
		{
			this->marimi = new float[s.nrMarimi];
			this->nrMarimi = s.nrMarimi;
			for (int i = 0; i < this->nrMarimi; i++)
			{
				this->marimi[i] = s.marimi[i];
			}
		}
		else
		{
			this->marimi = NULL;
			this->nrMarimi = 0;
		}
		if (s.preturi != NULL && s.nrMarimi > 0)
		{
			this->preturi = new float[s.nrMarimi];
			this->nrMarimi = s.nrMarimi;
			for (int i = 0; i < this->nrMarimi; i++)
			{
				this->preturi[i] = s.preturi[i];
			}
		}
		else
		{
			this->preturi = NULL;
			this->nrMarimi = 0;
		}
	}

	//Operator =
	Imbracaminte& operator=(const Imbracaminte& s)
	{
		this->marca = s.marca;
		this->culoare = s.culoare;
		this->anAparitie = s.anAparitie;
		delete[] this->marimi;
		delete[] this->preturi;
		if (s.marimi != NULL && nrMarimi > 0)
		{
			this->marimi = new float[s.nrMarimi];
			this->nrMarimi = s.nrMarimi;
			for (int i = 0; i < this->nrMarimi; i++)
			{
				this->marimi[i] = s.marimi[i];
			}
		}
		else
		{
			this->marimi = NULL;
			this->nrMarimi = 0;
		}
		if (s.preturi != NULL && nrMarimi > 0)
		{
			this->preturi = new float[s.nrMarimi];
			this->nrMarimi = s.nrMarimi;
			for (int i = 0; i < this->nrMarimi; i++)
			{
				this->preturi[i] = s.preturi[i];
			}
		}
		else
		{
			this->preturi = NULL;
			this->nrMarimi = 0;
		}
	}

	//Destructor
	~Imbracaminte()
	{
		delete[] marimi;
		delete[] preturi;
	}

	//Operator indexare []
	float& operator[](int index)
	{
		return this->marimi[index];
	}

	//Operator +
	Imbracaminte operator+(int ani)
	{
		Imbracaminte aux = *this;
		if (ani >= 0)
		{
			aux.anAparitie += ani;
		}
		return aux;
	}

	//Operator ++ preincrementare --- adauga o noua marime, un nou pret, dublandu-l pe ultimul.
	Imbracaminte operator++()
	{
		Imbracaminte aux = *this;
		if (this->nrMarimi > 0)
		{
			this->nrMarimi++;
			delete[] this->marimi;
			delete[] this->preturi;
			this->marimi= new float[this->nrMarimi];
			this->preturi = new float[this->nrMarimi];
			for (int i = 0; i < aux.nrMarimi; i++)
			{
				this->marimi[i] = aux.marimi[i];
				this->preturi[i] = aux.preturi[i];
			}
			this->marimi[this->nrMarimi - 1] = this->marimi[aux.nrMarimi - 1] * 2;
			this->preturi[this->nrMarimi - 1] = this->preturi[aux.nrMarimi - 1] * 2;
		}
		return *this;
	}

	//Operator ++ postincrementare --- adauga o noua marime, un nou pret, dublandu-l pe ultimul.
	Imbracaminte operator++(int)
	{
		Imbracaminte aux = *this;
		if (aux.nrMarimi > 0)
		{
			aux.nrMarimi++;
			delete[] aux.marimi;
			delete[] aux.preturi;
			aux.marimi = new float[aux.nrMarimi];
			aux.preturi = new float[aux.nrMarimi];
			for (int i = 0; i < this->nrMarimi; i++)
			{
				aux.marimi[i] = this->marimi[i];
				aux.preturi[i] = this->preturi[i];
			}
			aux.marimi[aux.nrMarimi- 1] = aux.marimi[this->nrMarimi - 1] * 2;
			aux.preturi[aux.nrMarimi - 1] = aux.preturi[this->nrMarimi - 1] * 2;
		}
		return aux;
	}

	//Operator cast la string
	operator string()
	{
		return this->marca;
	}

	//Operator cast la int
	operator int()
	{
		return this->anAparitie;
	}

	//operator negatie - sterge marimi, preturi
	Imbracaminte operator!()
	{
		Imbracaminte aux = *this;
		delete[] aux.marimi;
		delete[] aux.preturi;
		aux.marimi = NULL;
		aux.preturi = NULL;
		aux.nrMarimi = 0;
		return aux;
	}

	//operator < - compara anii aparitiei
	bool operator<(const Imbracaminte& s)
	{
		if (this->anAparitie < s.anAparitie)
			return true;
		else
			return false;
	}

	//operator == compara anii aparitiei
	bool operator==(const Imbracaminte& s)
	{
		if (this->anAparitie == s.anAparitie)
			return true;
		else
			return false;
	}

	//Getter
	const int getIdProdus() { return this->idProdus; }

	static int getBasicId() { return basicId; }

	string getMarca() { return this->marca; }

	string getCuloare() { return this->culoare; }

	int getAnAparitie() { return this->anAparitie; }

	int getNrMarimi() { return this->nrMarimi; }

	float* getMarimi() { return marimi; }

	float* getPreturi() { return preturi; }

	//Setter
	static void setBasicId(int id) { if (id >= 0) basicId = id; }

	void setMarca(string marca)
	{
		if (this->marca != marca)
		{
			this->marca = marca;
		}
		else
			cout << "Deja acest obiect are setata aceasta marca.";
	}

	void setCuloare(string culoare)
	{
		if (this->culoare != culoare)
		{
			this->culoare = culoare;
		}
		else
			cout << "Deja acest obiect are setata aceasta culoare.";
	}

	void setAnAparitie(int an)
	{
		if (an > 0)
			this->anAparitie = an;
		else
			cout << "Nu exista acesta an";
	}

	void setNrMarimi(int nr)
	{
		if (nr > 0)
		{
			this->nrMarimi = nr;
		}
		if (nr == 0)
		{
			this->nrMarimi = 0;
			this->marimi = NULL;
			this->preturi = NULL;
		}
		if (nr < 0)
			throw new exception("Nu poti avea un nr de marimi mai mic ca 0");
	}

	void setMarimi(int nrMarimi, float* marimi)
	{
		if (nrMarimi > 0 && marimi != NULL)
		{
			delete[] this->marimi;
			this->marimi = new float[nrMarimi];
			for (int i = 0; i < nrMarimi; i++)
			{
				this->marimi[i] = marimi[i];
			}
		}
	}

	void setPreturi(int nrPreturi, float* preturi)
	{
		if (nrPreturi > 0 && preturi != NULL)
		{
			delete[] this->preturi;
			this->preturi = new float[nrPreturi];
			for (int i = 0; i < nrPreturi; i++)
			{
				this->preturi[i] = preturi[i];
			}
		}
	}

	friend ostream& operator<<(ostream& out, const Imbracaminte& s);
	friend istream& operator>>(istream& in, Imbracaminte& s);
};

ostream& operator<<(ostream& out, const Imbracaminte& s)
{
	out << "\n Id Produs: " << s.idProdus;
	out << "\n Marca: " << s.marca;
	out << "\n Culoare: " << s.culoare;
	out << "\n An aparitie: " << s.anAparitie;
	out << "\n Lista marimi: ";
	if (s.marimi != NULL && s.nrMarimi > 0)
	{
		for (int i = 0; i < s.nrMarimi; i++)
		{
			out << s.marimi[i] << " ";
		}
		cout << " ";
	}
	else
		out << " - ";
	cout << "\n Lista preturi: ";
	if (s.preturi != NULL && s.nrMarimi > 0)
	{
		for (int i = 0; i < s.nrMarimi; i++)
		{
			out << s.preturi[i] << " ";
		}
		cout << " (lei)";
	}
	else
		out << " - ";
	return out;
}

istream& operator>>(istream& in, Imbracaminte& s)
{
	cout << "\n Introduceti marca produs: ";
	in >> s.marca;
	cout << "\n Introduceti culoare produs: ";
	in >> s.culoare;
	cout << "\n Introduceti an aparitie: ";
	in >> s.anAparitie;
	cout << "\n Introduceti numarul de marimi disponibile: ";
	in >> s.nrMarimi;
	delete[] s.marimi;
	delete[] s.preturi;
	if (s.nrMarimi > 0)
	{
		s.marimi = new float[s.nrMarimi];
		s.preturi = new float[s.nrMarimi];
		for (int i = 0; i < s.nrMarimi; i++)
		{
			cout << "\n Introduceti marimea cu numarul " << i + 1 << " : ";
			in >> s.marimi[i];
			cout << endl;
			cout << "\n Introduceti pretul marimii cu numarul " << i + 1 << " : ";
			in >> s.preturi[i];
			cout << endl;
		}
	}
	else
	{
		s.nrMarimi = 0;
		s.marimi = NULL;
		s.preturi = NULL;
	}
	return in;
}

class Incaltaminte
{

private:

	static int basicId;
	const int idProdus;
	string marca;
	string culoare;
	int anAparitie;
	int nrMarimi;
	float* marimi;
	float* preturi;

public:

	//Constructor default
	Incaltaminte() : idProdus(++basicId + 1000), marca("N/A"), culoare("N/A"), anAparitie(0), nrMarimi(0), marimi(NULL), preturi(NULL)
	{
	}

	//Constructor cu parametrii
	Incaltaminte(string marca, string culoare, int anAparitie, int nrMarimi, float* marimi, float* preturi) : idProdus(++basicId + 1000)
	{

		this->marca = marca;
		this->culoare = culoare;
		this->anAparitie = anAparitie;
		if (nrMarimi != 0 && marimi != NULL)
		{
			this->nrMarimi = nrMarimi;
			this->marimi = new float[nrMarimi];
			for (int i = 0; i < this->nrMarimi; i++)
				this->marimi[i] = marimi[i];
		}
		else
		{
			this->nrMarimi = 0;
			this->marimi = NULL;
		}
		if (nrMarimi != 0 && preturi != NULL)
		{
			this->nrMarimi = nrMarimi;
			this->preturi = new float[nrMarimi];
			for (int i = 0; i < this->nrMarimi; i++)
				this->preturi[i] = preturi[i];
		}
		else
		{
			this->nrMarimi = 0;
			this->preturi = NULL;
		}

	}

	//Constructor copiere
	Incaltaminte(const Incaltaminte& s) : marca(s.marca), culoare(s.culoare), anAparitie(s.anAparitie), idProdus(++basicId + 1000)
	{
		if (s.marimi != NULL && s.nrMarimi > 0)
		{
			this->marimi = new float[s.nrMarimi];
			this->nrMarimi = s.nrMarimi;
			for (int i = 0; i < this->nrMarimi; i++)
			{
				this->marimi[i] = s.marimi[i];
			}
		}
		else
		{
			this->marimi = NULL;
			this->nrMarimi = 0;
		}
		if (s.preturi != NULL && s.nrMarimi > 0)
		{
			this->preturi = new float[s.nrMarimi];
			this->nrMarimi = s.nrMarimi;
			for (int i = 0; i < this->nrMarimi; i++)
			{
				this->preturi[i] = s.preturi[i];
			}
		}
		else
		{
			this->preturi = NULL;
			this->nrMarimi = 0;
		}
	}

	//Operator =
	Incaltaminte& operator=(const Incaltaminte& s)
	{
		this->marca = s.marca;
		this->culoare = s.culoare;
		this->anAparitie = s.anAparitie;
		delete[] this->marimi;
		delete[] this->preturi;
		if (s.marimi != NULL && nrMarimi > 0)
		{
			this->marimi = new float[s.nrMarimi];
			this->nrMarimi = s.nrMarimi;
			for (int i = 0; i < this->nrMarimi; i++)
			{
				this->marimi[i] = s.marimi[i];
			}
		}
		else
		{
			this->marimi = NULL;
			this->nrMarimi = 0;
		}
		if (s.preturi != NULL && nrMarimi > 0)
		{
			this->preturi = new float[s.nrMarimi];
			this->nrMarimi = s.nrMarimi;
			for (int i = 0; i < this->nrMarimi; i++)
			{
				this->preturi[i] = s.preturi[i];
			}
		}
		else
		{
			this->preturi = NULL;
			this->nrMarimi = 0;
		}
	}

	//Destructor
	~Incaltaminte()
	{
		delete[] marimi;
		delete[] preturi;
	}

	//Operator indexare []
	float& operator[](int index)
	{
		return this->marimi[index];
	}

	//Operator +
	Incaltaminte operator+(int ani)
	{
		Incaltaminte aux = *this;
		if (ani >= 0)
		{
			aux.anAparitie += ani;
		}
		return aux;
	}

	//Operator ++ preincrementare --- adauga o noua marime, un nou pret, dublandu-l pe ultimul.
	Incaltaminte operator++()
	{
		Incaltaminte aux = *this;
		if (this->nrMarimi > 0)
		{
			this->nrMarimi++;
			delete[] this->marimi;
			delete[] this->preturi;
			this->marimi = new float[this->nrMarimi];
			this->preturi = new float[this->nrMarimi];
			for (int i = 0; i < aux.nrMarimi; i++)
			{
				this->marimi[i] = aux.marimi[i];
				this->preturi[i] = aux.preturi[i];
			}
			this->marimi[this->nrMarimi - 1] = this->marimi[aux.nrMarimi - 1] * 2;
			this->preturi[this->nrMarimi - 1] = this->preturi[aux.nrMarimi - 1] * 2;
		}
		return *this;
	}

	//Operator ++ postincrementare --- adauga o noua marime, un nou pret, dublandu-l pe ultimul.
	Incaltaminte operator++(int)
	{
		Incaltaminte aux = *this;
		if (aux.nrMarimi > 0)
		{
			aux.nrMarimi++;
			delete[] aux.marimi;
			delete[] aux.preturi;
			aux.marimi = new float[aux.nrMarimi];
			aux.preturi = new float[aux.nrMarimi];
			for (int i = 0; i < this->nrMarimi; i++)
			{
				aux.marimi[i] = this->marimi[i];
				aux.preturi[i] = this->preturi[i];
			}
			aux.marimi[aux.nrMarimi - 1] = aux.marimi[this->nrMarimi - 1] * 2;
			aux.preturi[aux.nrMarimi - 1] = aux.preturi[this->nrMarimi - 1] * 2;
		}
		return aux;
	}

	//Operator cast la string
	operator string()
	{
		return this->marca;
	}

	//Operator cast la int
	operator int()
	{
		return this->anAparitie;
	}

	//operator negatie - sterge marimi, preturi
	Incaltaminte operator!()
	{
		Incaltaminte aux = *this;
		delete[] aux.marimi;
		delete[] aux.preturi;
		aux.marimi = NULL;
		aux.preturi = NULL;
		aux.nrMarimi = 0;
		return aux;
	}

	//operator < - compara anii aparitiei
	bool operator<(const Incaltaminte& s)
	{
		if (this->anAparitie < s.anAparitie)
			return true;
		else
			return false;
	}

	//operator == compara anii aparitiei
	bool operator==(const Incaltaminte& s)
	{
		if (this->anAparitie == s.anAparitie)
			return true;
		else
			return false;
	}

	//Getter
	const int getIdProdus() { return this->idProdus; }

	static int getBasicId() { return basicId; }

	string getMarca() { return this->marca; }

	string getCuloare() { return this->culoare; }

	int getAnAparitie() { return this->anAparitie; }

	int getNrMarimi() { return this->nrMarimi; }

	float* getMarimi() { return marimi; }

	float* getPreturi() { return preturi; }

	//Setter
	static void setBasicId(int id) { if (id >= 0) basicId = id; }

	void setMarca(string marca)
	{
		if (this->marca != marca)
		{
			this->marca = marca;
		}
		else
			cout << "Deja acest obiect are setata aceasta marca.";
	}

	void setCuloare(string culoare)
	{
		if (this->culoare != culoare)
		{
			this->culoare = culoare;
		}
		else
			cout << "Deja acest obiect are setata aceasta culoare.";
	}

	void setAnAparitie(int an)
	{
		if (an > 0)
			this->anAparitie = an;
		else
			cout << "Nu exista acesta an";
	}

	void setNrMarimi(int nr)
	{
		if (nr > 0)
		{
			this->nrMarimi = nr;
		}
		if (nr == 0)
		{
			this->nrMarimi = 0;
			this->marimi = NULL;
			this->preturi = NULL;
		}
		if (nr < 0)
			throw new exception("Nu poti avea un nr de marimi mai mic ca 0");
	}

	void setMarimi(int nrMarimi, float* marimi)
	{
		if (nrMarimi > 0 && marimi != NULL)
		{
			delete[] this->marimi;
			this->marimi = new float[nrMarimi];
			for (int i = 0; i < nrMarimi; i++)
			{
				this->marimi[i] = marimi[i];
			}
		}
	}

	void setPreturi(int nrPreturi, float* preturi)
	{
		if (nrPreturi > 0 && preturi != NULL)
		{
			delete[] this->preturi;
			this->preturi = new float[nrPreturi];
			for (int i = 0; i < nrPreturi; i++)
			{
				this->preturi[i] = preturi[i];
			}
		}
	}

	friend ostream& operator<<(ostream& out, const Incaltaminte& s);
	friend istream& operator>>(istream& in, Incaltaminte& s);
};

ostream& operator<<(ostream& out, const Incaltaminte& s)
{
	out << "\n Id Produs: " << s.idProdus;
	out << "\n Marca: " << s.marca;
	out << "\n Culoare: " << s.marca;
	out << "\n An aparitie: " << s.anAparitie;
	out << "\n Lista marimi: ";
	if (s.marimi != NULL && s.nrMarimi > 0)
	{
		for (int i = 0; i < s.nrMarimi; i++)
		{
			out << s.marimi[i] << " ";
		}
		cout << " ";
	}
	else
		out << " - ";
	cout << "\n Lista preturi: ";
	if (s.preturi != NULL && s.nrMarimi > 0)
	{
		for (int i = 0; i < s.nrMarimi; i++)
		{
			out << s.preturi[i] << " ";
		}
		cout << " (lei)";
	}
	else
		out << " - ";
	return out;
}

istream& operator>>(istream& in, Incaltaminte& s)
{
	cout << "\n Introduceti marca produs: ";
	in >> s.marca;
	cout << "\n Introduceti culoare produs: ";
	in >> s.culoare;
	cout << "\n Introduceti an aparitie: ";
	in >> s.anAparitie;
	cout << "\n Introduceti numarul de marimi disponibile: ";
	in >> s.nrMarimi;
	delete[] s.marimi;
	delete[] s.preturi;
	if (s.nrMarimi > 0)
	{
		s.marimi = new float[s.nrMarimi];
		s.preturi = new float[s.nrMarimi];
		for (int i = 0; i < s.nrMarimi; i++)
		{
			cout << "\n Introduceti marimea cu numarul " << i + 1 << " : ";
			in >> s.marimi[i];
			cout << endl;
			cout << "\n Introduceti pretul marimii cu numarul " << i + 1 << " : ";
			in >> s.preturi[i];
			cout << endl;
		}
	}
	else
	{
		s.nrMarimi = 0;
		s.marimi = NULL;
		s.preturi = NULL;
	}
	return in;
}

class Clienti
{

protected:

	string nume;
	const int idClient;

private:

	static int basicId;
	int nrComenzi;
	int* comenzi;
	float* valoareComanda;

public:
	string toString()
	{
		stringstream ss;
		ss << this->nrComenzi;
		string s = this->nume + " " + ss.str();
		cout << " testam " << this->nrComenzi << " " << ss.str() << endl;
		return s;
	}

	//Constructor default
	Clienti(): idClient(++basicId),nume("N/A"), nrComenzi(0),comenzi(NULL),valoareComanda(NULL)
	{}

	//Constructor cu parametrii
	Clienti(string nume, int nrComenzi, int* comenzi, float* valoareComanda) :idClient(++basicId)
	{
		this->nume = nume;
		if (nrComenzi > 0 && comenzi != NULL)
		{
			this->nrComenzi = nrComenzi;
			this->comenzi = new int[this->nrComenzi];
			this->valoareComanda = new float[this->nrComenzi];
			for (int i = 0; i < this->nrComenzi; i++)
			{
				this->comenzi[i] = comenzi[i];
				this->valoareComanda[i] = valoareComanda[i];
			}
		}
		else if (nrComenzi > 0 && comenzi == NULL)
		{
			this->nrComenzi = nrComenzi;
			this->comenzi = NULL;
			this->valoareComanda = NULL;
		}
		else
		{
			this->nrComenzi = 0;
			this->comenzi = NULL;
			this->valoareComanda = NULL;
		}

	}

	//Constructor copiere
	Clienti(const Clienti& c) :idClient(++basicId),nume(c.nume)
	{
		if (c.nrComenzi > 0 && c.comenzi != NULL)
		{
			this->nrComenzi = c.nrComenzi;
			this->comenzi = new int[this->nrComenzi];
			this->valoareComanda = new float[this->nrComenzi];
			for (int i = 0; i < this->nrComenzi; i++)
			{
				this->comenzi[i] = c.comenzi[i];
				this->valoareComanda[i] = c.valoareComanda[i];
			}
		}
		else
		{
			this->nrComenzi = 0;
			this->comenzi = NULL;
			this->valoareComanda = NULL;
		}
	}

	//Operator =
	Clienti& operator=(const Clienti& c)
	{
		this->nume = c.nume;
		if (c.nrComenzi > 0 && c.comenzi != NULL)
		{
			this->nrComenzi = c.nrComenzi;
			delete[] this->comenzi;
			delete[] this->valoareComanda;
			this->comenzi = new int[this->nrComenzi];
			this->valoareComanda = new float[this->nrComenzi];
			for (int i = 0; i < this->nrComenzi; i++)
			{
				this->comenzi[i] = c.comenzi[i];
				this->valoareComanda[i] = c.valoareComanda[i];
			}
		}
		else
		{
			this->nrComenzi = 0;
			this->comenzi = NULL;
			this->valoareComanda = NULL;
		}
		return *this;
	}

	//Destructor
	~Clienti()
	{
		delete[] this->comenzi;
		delete[] this->valoareComanda;
	}

	//Operator indexare []
	int& operator[](int index)
	{
		return this->comenzi[index];
	}

	//Operator ++ preincrementare --- adauga o noua comanda, un nou pret, dublandu-l pe ultimul.
	Clienti operator++()
	{
		Clienti aux = *this;
		if (this->nrComenzi > 0)
		{
			this->nrComenzi++;
			delete[] this->comenzi;
			delete[] this->valoareComanda;
			this->comenzi = new int[this->nrComenzi];
			this->valoareComanda = new float[this->nrComenzi];
			for (int i = 0; i < aux.nrComenzi; i++)
			{
				this->comenzi[i] = aux.comenzi[i];
				this->valoareComanda[i] = aux.valoareComanda[i];
			}
			this->comenzi[this->nrComenzi - 1] = this->comenzi[aux.nrComenzi - 1] * 2;
			this->valoareComanda[this->nrComenzi - 1] = this->valoareComanda[aux.nrComenzi - 1] * 2;
		}
		return *this;
	}

	//Operator ++ postincrementare --- adauga o noua comanda, un nou pret, dublandu-l pe ultimul.
	Clienti operator++(int)
	{
		Clienti aux = *this;
		if (aux.nrComenzi > 0)
		{
			aux.nrComenzi++;
			delete[] aux.comenzi;
			delete[] aux.valoareComanda;
			aux.comenzi = new int[aux.nrComenzi];
			aux.valoareComanda = new float[aux.nrComenzi];
			for (int i = 0; i < this->nrComenzi; i++)
			{
				aux.comenzi[i] = this->comenzi[i];
				aux.valoareComanda[i] = this->valoareComanda[i];
			}
			aux.comenzi[aux.nrComenzi - 1] = aux.comenzi[this->nrComenzi - 1] * 2;
			aux.valoareComanda[aux.nrComenzi - 1] = aux.valoareComanda[this->nrComenzi - 1] * 2;
		}
		return aux;
	}

	//Getter
	string getNume()
	{
		return this->nume;
	}

	int getNrComenzi()
	{
		return this->nrComenzi;
	}

	int* getComenzi()
	{
		return this->comenzi;
	}

	float* getValoareComanda()
	{
		return this->valoareComanda;
	}

	//Setter
	void setNume(string nume)
	{
		if (nume != "")
		{
			this->nume = nume;
		}
	}

	void setNrComenzi(int nr)
	{
		if (nr > 0) 
		{
			this->nrComenzi = nr;
		}
		if (nr == 0)
		{
			this->nrComenzi = 0;
			this->comenzi = NULL;
			this->valoareComanda = NULL;
		}
		if (nr < 0)
			throw new exception("Nu poti avea un nr de marimi mai mic ca 0");
	}

	void setComenzi(int nrComenzi, int* comenzi)
	{
		if (nrComenzi > 0 && comenzi != NULL)
		{
			delete[] this->comenzi;
			this->comenzi = new int[nrComenzi];
			for (int i = 0; i < nrComenzi; i++)
			{
				this->comenzi[i] = comenzi[i];
			}
		}
	}

	void setValoareComanda(int nrComenzi, float* valoareComanda)
	{
		if (nrComenzi > 0 && valoareComanda != NULL)
		{
			delete[] this->valoareComanda;
			this->comenzi = new int[nrComenzi];
			for (int i = 0; i < nrComenzi; i++)
			{
				this->valoareComanda[i] = valoareComanda[i];
			}
		}
	}

	friend ostream& operator<<(ostream& out, const Clienti& c)
	{
		out << "\n Id Client: " << c.idClient;
		out << "\n Nume client: " << c.nume;
		out << "\n Lista comenzi: ";
		if (c.comenzi != NULL && c.nrComenzi > 0)
		{
			for (int i = 0; i < c.nrComenzi; i++)
			{
				out << c.comenzi[i] << " ";
			}
			cout << " ";
		}
		else
			out << " - ";
		cout << "\n Valoare comenzi: ";
		if (c.valoareComanda != NULL && c.nrComenzi > 0)
		{
			for (int i = 0; i < c.nrComenzi; i++)
			{
				out << c.valoareComanda[i] << " ";
			}
			cout << " (lei)";
		}
		else
			out << " - ";
		return out;
	}
	friend istream& operator>>(istream& in, Clienti& c)
	{
		cout << "\n Introduceti nume client: ";
		in >> c.nume;
		cout << "\n Introduceti numarul de comenzi: ";
		in >> c.nrComenzi;
		delete[] c.comenzi;
		delete[] c.valoareComanda;
		if (c.nrComenzi > 0)
		{
			c.comenzi= new int[c.nrComenzi];
			c.valoareComanda = new float[c.nrComenzi];
			for (int i = 0; i < c.nrComenzi; i++)
			{
				cout << "\n Introduceti comanda cu numarul " << i + 1 << " : ";
				in >> c.comenzi[i];
				cout << endl;
				cout << "\n Introduceti pretul comenzii cu numarul " << i + 1 << " : ";
				in >> c.valoareComanda[i];
				cout << endl;
			}
		}
		else
		{
			c.nrComenzi = 0;
			c.comenzi = NULL;
			c.valoareComanda = NULL;
		}
		return in;
	}
};

class CadouPromotional {

private:

	string denumire = "N/A";
	float pret = 0;

public:

	// Constructor default
	CadouPromotional()
	{
	}

	//Constructor cu parametrii
	CadouPromotional(string denumire, float pret)
	{
		this->denumire = denumire;
		this->pret = pret;
	}

	//Constructor copiere
	CadouPromotional(const CadouPromotional& c)
	{
		this->denumire = c.denumire;
		this->pret = c.pret;
	}

	//Operator =
	CadouPromotional& operator=(const CadouPromotional& c)
	{
		this->denumire = c.denumire;
		this->pret = c.pret;
		return *this;
	}

	friend ostream& operator<<(ostream& out, const CadouPromotional& c)
	{
		out << "\nDenumire: " << c.denumire << ", pret: " << c.pret<<" lei";
		return out;
	}

	friend istream& operator>>(istream& in, CadouPromotional& c)
	{
		cout << "\nIntroduceti denumire: ";
		in >> c.denumire;
		cout << "Introduceti pret: ";
		in >> c.pret;
		return in;
	}
};

class ListaCadouriPromotionale : Clienti
{
	//vector alocat dinamic de pointeri de tip Cadou
	CadouPromotional** listaCadouri = NULL;
	int nrCadouri = 0;

public:

	//Constructor Default
	ListaCadouriPromotionale()
	{
	}

	//Constructor cu parametrii
	ListaCadouriPromotionale(char* nume, CadouPromotional listaCadouri[], int nrCadouri)
	{
		this->nume = nume;
		if (listaCadouri != NULL && nrCadouri > 0)
		{
			this->nrCadouri = nrCadouri;
			this->listaCadouri = new CadouPromotional * [this->nrCadouri];
			for (int i = 0; i < this->nrCadouri; i++)
			{
				this->listaCadouri[i] = new CadouPromotional(listaCadouri[i]);
			}
		}
	}

	//Constructor cu parametrii
	ListaCadouriPromotionale(string nume, CadouPromotional** listaCadouri, int nrCadouri)
	{
		this->nume = nume;
		if (listaCadouri != NULL && nrCadouri > 0)
		{
			this->nrCadouri = nrCadouri;
			this->listaCadouri = new CadouPromotional * [this->nrCadouri];
			for (int i = 0; i < this->nrCadouri; i++)
			{
				this->listaCadouri[i] = new CadouPromotional(*listaCadouri[i]);
			}
		}
	}
	//Constructor de copiere
	ListaCadouriPromotionale(const ListaCadouriPromotionale& w)
	{
		this->nume = w.nume;
		if (listaCadouri != NULL && w.nrCadouri > 0)
		{
			this->nrCadouri = w.nrCadouri;
			this->listaCadouri = new CadouPromotional * [this->nrCadouri];
			for (int i = 0; i < this->nrCadouri; i++)
			{
				this->listaCadouri[i] = new CadouPromotional(*w.listaCadouri[i]);
			}
		}
	}
	//Operator =
	ListaCadouriPromotionale& operator=(const ListaCadouriPromotionale& w)
	{
		for (int i = 0; i < this->nrCadouri; i++)
			delete this->listaCadouri[i];
		delete[] this->listaCadouri;

		this->nume = w.nume;
		if (listaCadouri != NULL && w.nrCadouri > 0)
		{
			this->nrCadouri = w.nrCadouri;
			this->listaCadouri = new CadouPromotional * [this->nrCadouri];
			for (int i = 0; i < this->nrCadouri; i++)
			{
				this->listaCadouri[i] = new CadouPromotional(*w.listaCadouri[i]);
			}
		}
		return *this;
	}

	//Destructor
	~ListaCadouriPromotionale()
	{
		for (int i = 0; i < this->nrCadouri; i++)
			delete this->listaCadouri[i];
		delete[] this->listaCadouri;
	}

	friend istream& operator>>(istream& in, ListaCadouriPromotionale& w)
	{
		for (int i = 0; i < w.nrCadouri; i++)
			delete w.listaCadouri[i];
		delete[] w.listaCadouri;

		cout << "\nIntroduceti nume: ";
		in >> w.nume;
		cout << "Introduceti nr cadouri: ";
		in >> w.nrCadouri;
		if (w.nrCadouri > 0)
		{
			w.listaCadouri = new CadouPromotional * [w.nrCadouri];
			for (int i = 0; i < w.nrCadouri; i++)
			{
				CadouPromotional c;
				in >> c;
				w.listaCadouri[i] = new CadouPromotional(c);
			}
		}
		else
		{
			w.listaCadouri = NULL;
			w.nrCadouri = 0;
		}
		return in;
	}

	friend ostream& operator<<(ostream& out, const ListaCadouriPromotionale& w)
	{
		out << "\n----------------------------------";
		out << "\nNume detinator: " << w.nume;
		out << "\nNr Cadouri: " << w.nrCadouri;
		out << "\nLista cadouri: ";
		if (w.listaCadouri != NULL)
		{
			for (int i = 0; i < w.nrCadouri; i++)
				out << *w.listaCadouri[i];
		}
		out << "\n----------------------------------";
		return out;
	}
};


class FileReader
{
public:

	string fileName;
	ifstream myFile;
	FileReader(string fileName)
	{
		this->fileName = fileName;
	}

	void Reader()
	{
		string myText;
		vector<string> txtVector;
		myFile.open(this->fileName);
		while (getline(myFile, myText))
		{

		}
		myFile.close();
	}
	vector<Clienti> ReadClienti()
	{
		vector<Clienti> clientiCititi;
		vector<string> txtVector;
		vector<string> names;
		vector<int> nrComenzi;
		string myText;
		myFile.open(this->fileName);
		while (getline(myFile, myText))
		{
			txtVector = this->split(myText, ',');
			if (txtVector.size() != 2)
			{
				cout << "Format necorespunzator" << endl;
			}
			stringstream ss;
			int aux;
			ss << txtVector[1];
			ss >> aux;
			nrComenzi.push_back(aux);
			names.push_back(txtVector[0]);
			clientiCititi.push_back(Clienti());
		}
		for(int i=0; i < clientiCititi.size(); i++) 
		{
			clientiCititi[i].setNume(names[i]);
			clientiCititi[i].setNrComenzi(nrComenzi[i]);
		}
		myFile.close();
		return clientiCititi;
	}
	vector<string> split(string text, char delim) {
		string line;
		vector<string> vec;
		stringstream ss(text);
		while (getline(ss, line, delim)) {
			vec.push_back(line);
		}
		return vec;
	}

	void readBinaryFile() {
		ifstream myBinaryFile(this->fileName, ios::binary);
		while (myBinaryFile) {
			char c;
			myBinaryFile.get(c);
			if (myBinaryFile) {
				cout << c << endl;
			}
		}
		myBinaryFile.close();
		myBinaryFile.open(this->fileName, ios::binary | ios::in | ios::out | ios::trunc);
		myBinaryFile.close();
	}
};

class FileWritter
{

public:
	string fileName;

	FileWritter(string fileName)
	{
		this->fileName = fileName;
	}

	void writeBinaryFile(vector<Clienti> clienti) {
		ofstream myBinaryFile(this->fileName, ios::binary | ios::in | ios::out | ios::trunc);
		for (int i = 0; i < clienti.size(); i++)
		{
			myBinaryFile << clienti[i].getNume();
		}
		myBinaryFile.close();
	}

};

class FilesGetter
{
public:

	vector<string> filesName;
	FilesGetter(vector<string> filesName)
	{
		this->filesName = filesName;
	}
	vector<Clienti> citireClienti()
	{
		FileReader fr(filesName[0]);
		return fr.ReadClienti();
	}

	void writeBinaryFile(string binaryFileName, vector<Clienti> clienti)
	{
		FileWritter fw(binaryFileName);
		fw.writeBinaryFile(clienti);
	}

	void readBinaryFile(string binaryFileName)
	{
		FileReader fr(binaryFileName);
		fr.readBinaryFile();
	}
};

class MeniuAplicatie
{

public:
	int nr;

	void AfisareMeniu()
	{
		cout << "\n Alegeti una dintre urmatoarele optiuni: "<<endl;
		cout << " 1. Exit"<<endl;
		cout << " 2. Afisare lista clienti"<<endl;
		cout << " 3. Scriere lista clienti in fisier binar" << endl;
		cout << " 4. Citire lista clienti din fisier binar" << endl;
		
	}

	void Verificare(int nr)
	{
		if (nr > 4 || nr < 1)
		{
			cout << "Optiunea nu exista! " << endl;
		}
		
	}
	void ExecutieComanda(int nr, FilesGetter fg)
	{
		switch (nr)
		{
			case 1:
			{
				exit(1);
				break;
			}
			case 2:
			{
				vector<Clienti> clienti = fg.citireClienti();
				for (int i = 0; i < clienti.size(); i++)
				{
					cout << clienti[i].getNume() << " " << clienti[i].getNrComenzi() << endl;
				}
				break;
			}
			case 3:
			{
				vector<Clienti> clienti = fg.citireClienti();
				fg.writeBinaryFile("binary.dat", clienti);
				break;
			}
			case 4:
			{
				fg.readBinaryFile("binary.dat");
				break;
			}
		}
	}
	 

};

int Suplimente::basicId = 0;
int Imbracaminte::basicId = 0;
int Incaltaminte::basicId = 0;
int Clienti::basicId = 100;

int main(int argc, char* argv[])
{
	float gramaj[] = { 3,4,5 };
	float preturi[] = { 100, 200, 300 };
	Suplimente s("Whey Protein", 100, 100, 100, 100, 3, gramaj, preturi);
	//cout << s;
	cout << "\n *******************************"<<endl;

	Suplimente s2 = s;

	
	vector<string> allArgs(argv, argv + argc);
	vector<string> oa(allArgs.begin() + 1, allArgs.end());
	FilesGetter fg(oa);

	//if (s2 > s)
	//	cout << "\n Adevarat";
	//else
	//	cout << "\n Fals";

	//if (s2 < s)
	//	cout << "\n Adevarat";
	//else
	//	cout << "\n Fals";


	//// Preincrementeare, posincrementare
	//s = ++s2;
	//cout << s;
	//cout << "\n *******************************";
	//cout << s2;
	//cout << "\n *******************************";

	//s = s2++;
	//cout << s;
	//cout << "\n *******************************";
	//cout << s2;
	//cout << "\n *******************************";

	string arome[] = { "capsuni", "ciocolata" };
	Proteine p("Whey Protein", 100, 100, 100, 100, 3, gramaj, preturi, TipProteina::Whey, 2, arome);
	cout << p;
	Proteine p2 = p;
	//p2 = p + 2;
	cout << "\n *******************************";
	cout << p2;

	string tip[50] = { "pastile", "pudra" };


	cout << "\n *******************************";
	//cout << p2;
	//Aminoacizi a("Amino Plus", 100, 100, 100, 100, 3, gramaj, preturi, TipAmino::BCA, tip,2);
	/*Aminoacizi a;
	cin >> a;
	cout << a;*/

	/*Creatina c("Crapure", 100, 100, 100, 100, 3, gramaj, preturi, TipCreatina::Monohidrata, tip, 2);
	cout << c;
	Creatina c2;
	c2 = c;
	cout << "\n *******************************";
	c2.setNume("Crapure Pure");
	cout << c2;*/
	float marimi[] = { 34,35,36 };

	Imbracaminte trening("Adidas", "Albastru", 2012, 3, marimi, preturi);
	cout << trening;


	Incaltaminte pantof("Adidas", "Verde", 2019, 3, marimi, preturi);
	cout << pantof;

	int comenzi[] = { 100,101,102 };
	float valoareComenzi[] = { 200, 300 ,400 };

	Clienti client1("Marian", 3, comenzi, valoareComenzi);
	cout << client1;
	cout << "\n *******************************";
	Clienti client2;
	client2 = client1;
	cout << client2;

	cout << "\n *******************************";
	CadouPromotional c1("Monstra Proteina Whey", 100);
	CadouPromotional c2("Monstra Proteina Izolat", 150);
	CadouPromotional c3("Monstra Creatina Monohidrata", 50);
	CadouPromotional** lc = new CadouPromotional * [3]{ &c1, &c2, &c3 };
	ListaCadouriPromotionale l("Mirel", lc, 3);
	cout << l<<endl;
	MeniuAplicatie m;
	while (1) 
	{
		m.AfisareMeniu();
		int optiuneIndex;
		cin >> optiuneIndex;
		m.Verificare(optiuneIndex);
		m.ExecutieComanda(optiuneIndex, fg);
	}

}