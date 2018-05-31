#ifndef PRODUS_H_INCLUDED
#define PRODUS_H_INCLUDED

#include <string>


using namespace std;

/*
----------------------------------------------------
Cuprins:
    Clasa Produs
    Clasa Faina
    Clasa Bere
    Clasa Vin_Varsat
    Clasa Vin_de_Soi
    Clasa Cartofi
    Clasa Jucarii
    Produs_Factory
----------------------------------------------------
*/

class Produs
{
protected:
    //string nume = NULL;
    enum
    {
        vag,
        bucata,
        greutate, //kg
        volum
    }masura;
    double pret; //pe unitatea de masura
    double cost; //pret in functie de cantitate
    double cantitate; //introdusa de client
    static double cantitate_vanduta;
    static double bani_incasati;

public:
    Produs(){pret=0, cost=0;}
    virtual ~Produs(){} //cred ca trebuie eliberat doar numele
    //virtual void CalcMasura()=0;
    void Set_Masura(string mas)
    {
        if(mas == "bucata")
            masura = bucata;
        if(mas == "greutate")
            masura = greutate;
        if(mas == "volum")
            masura = volum;
        if(mas == "vag")
            masura = vag;
    }
    string Get_Masura()
    {
        if(masura==1)
            return "bucata";
        if(masura == 2)
            return "greutate";
        if(masura == 3)
            return "volum";
        if(masura == 0)
            return "vag";
    }

    static void Add_Vandut(double cantit, double price)
    {
        cantitate_vanduta += cantit;
        bani_incasati += price;
    }
    static double Get_CantitateVanduta(){return cantitate_vanduta;}
    static double Get_PretTotal(){return bani_incasati;}
    void Set_Cantitate(double cantit) {cantitate = cantit;}
    double Get_Cantitate() {return cantitate;}
    double Get_Pret() { return pret; }
    //virtual double Set_Cost()=0;
    //double Get_Cost_Total(int cantitate) { return cantitate * pret;}
    void Set_Cost(){cost = cantitate*pret;}
    double Get_Cost() {return cost;}
    virtual istream &read(istream&) = 0;
    virtual ostream &print(ostream&) = 0;
};

double Produs::cantitate_vanduta = 0;
double Produs::bani_incasati = 0;


class Faina: public Produs
{
protected:
    enum
    {
        vag,
        calitate_1,
        calitate_2,
        calitate_3
    }calitate;
    //static double cantitate_vanduta; ///de fapt cere numarul total si pretul total (nu cont tipul obiectelor vandute ci doar totalul
    //static double bani_incasati;  ///daca voia specific modifcam in vectorul stoc cu variabilele statice
public:
    Faina(){masura = greutate;}
    Faina(double p, string tip_faina) //constructor pt inventar
    {
        pret = p;
        /*switch(tip)
        {
            case 0: calitate = vag;
            case 1: calitate = calitate_1;
            case 2: calitate = calitate_2;
            case 3: calitate = calitate_3;
        }*/
        if(tip_faina == "vag")
        {
            calitate = vag;
        }
        if(tip_faina == "calitate_1")
        {
            calitate = calitate_1;
        }
        if(tip_faina == "calitate_2")
        {
            calitate = calitate_2;
        }
        if(tip_faina == "calitate_3")
        {
            calitate = calitate_3;
        }

        masura = greutate;
    }
    ~Faina(){}
    string Get_Calitate()
    {
        switch(calitate)
        {
            case 0: return "vag";
            case 1: return "calitate_1";
            case 2: return "calitate_2";
            case 3: return "calitate_3";
            default: return "";
        }
    }

    istream &read(istream& in)
    {
        string quality;
        in>>quality;
        if(quality == "vag")
            calitate = vag;
        if(quality == "calitate_1")
            calitate = calitate_1;
        if(quality == "calitate_2")
            calitate = calitate_2;
        if(quality == "calitate_3")
            calitate = calitate_3;
        in>>cantitate;
        in>>pret;
        return in;
    }

    ostream &print(ostream& out)
    {
        out<<Get_Calitate()<<endl;
        out<<pret<<endl;
        return out;
    }
};

//double Faina::cantitate_vanduta = 0;
//double Faina::bani_incasati = 0;

class Bere: public Produs
{
protected:
    string brand;
    string tip_bere;
    /*enum
    {
        vag,
        blonda,
        bruna
    }tip_bere;*/

public:
    Bere(){masura = bucata;}
    Bere(double p, string nume, string tip)
    {
        pret = p;
        brand = nume;
        tip_bere = tip;
        masura = bucata;
    }
    ~Bere() {brand.clear(), tip_bere.clear();}

    void Set_Brand(string nume) {brand = nume;}
    string Get_Brand() { return brand; }
    void Set_Tip(string tipulet) {tip_bere = tipulet;}
    string Get_Tip() { return tip_bere; }

    istream &read(istream& in)
    {
        in>>brand;
        in>>tip_bere;
        in>>cantitate;
        in>>pret;
        return in;
    }

    ostream &print(ostream& out)
    {
        out<<brand<<endl;
        out<<tip_bere<<endl;
        out<<pret<<endl;
        return out;
    }
};


class Vin_Varsat: public Produs
{
protected:
    string tip_vin;
    /*enum
    {
        vag,
        rosu_sec,
        alb_sec
    }tip_vin;*/

public:
    Vin_Varsat(){masura = volum;}
    Vin_Varsat(double p, string tip)
    {
        pret = p;
        tip_vin = tip;
        /*switch(tip)
        {
            case 0: tip_vin = vag;
            case 1: tip_vin = rosu_sec;
            case 2: tip_vin = alb_sec;
        }*/
        masura = volum;
    }

    string Get_Tip() { return tip_vin; }

    istream &read(istream& in)
    {
        in>>tip_vin;
        in>>cantitate;
        in>>pret;
        return in;
    }
    ostream &print(ostream& out)
    {
        out<<tip_vin<<endl;
        out<<pret<<endl;
        return out;
    }
};


template <class T> class Pereche //frumos ar fi fost sa fie doua tipuri de clase in template
{
protected:
    T brand_vin;
    T tip_vin;
public:
    Pereche(){brand_vin = "", tip_vin = "";}
    Pereche(T nume, T tip)
    {
        brand_vin = nume;
        tip_vin = tip;
    }
    void Set_Nume(string nume) {brand_vin = nume;}
    void Set_Tip(string tip) {tip_vin = tip;}
    T Get_Nume() { return brand_vin; }
    T Get_Tip() { return tip_vin; }

    friend istream& operator >>(istream &in, Pereche<T> &pairr)
    {
        in>>pairr.brand_vin>>pairr.tip_vin;
        return in;
    }
   Pereche<T>& operator=(const Pereche<T>& pairr)
    {
        //verificam autoatribuirea dar mai trebuie implementat si operator== pt asta
        this->brand_vin = pairr.brand_vin;
        (*this).tip_vin = pairr.tip_vin;
    }
    friend ostream& operator <<(ostream &out, const Pereche<T> &pairr)
    {
        out<<pairr.brand_vin<<endl;
        out<<pairr.tip_vin<<endl;
        return out;
    }
};

class Vin_de_Soi: public Produs
{
protected:
    //brand si tip au numere echivalente pt vinuri echivalente
    /*enum
    {
        brand_vag,
        Cabernet_Savignon,
        Merlot,
        Savignon_Blanc,
        Chardonnay
    }brand_vin;

    enum
    {
        tip_vag,
        rosu_sec,
        rosu_dulce,
        alb_dulce

    }tip_vin_de_soi;*/

    /*enum
    {
        tara_vaga,
        Franta,
        Argentina,
        Chile,
        Australia
    }tara_origine_vin;*/
    typedef Pereche <string> Vin;
    Vin vin_soi;
    string tara_origine;
    int an;

public:
    Vin_de_Soi(){masura = bucata;}
    Vin_de_Soi(double p, string nume, string tipp, string tara, int anul)
    {
        pret = p;
        vin_soi.Set_Nume( nume );
        vin_soi.Set_Tip( tipp );
        tara_origine = tara;
        an = anul;
        masura = bucata;
        /*switch(vin)
        {
            case 0:
                brand_vin = brand_vag;
                tip_vin_de_soi = tip_vag;
            case 1:
                brand_vin = Cabernet_Savignon;
                tip_vin_de_soi = rosu_sec;
            case 2:
                brand_vin = Merlot;
                tip_vin_de_soi = rosu_dulce;
            case 3:
                brand_vin = Savignon_Blanc;
                tip_vin_de_soi = alb_dulce;
            case 4:
                brand_vin = Chardonnay;
                tip_vin_de_soi = alb_dulce;
        }
        switch(origine)
        {
            case 0: tara_origine_vin = tara_vaga;
            case 1: tara_origine_vin = Franta;
            case 2: tara_origine_vin = Argentina;
            case 3: tara_origine_vin = Chile;
            case 4: tara_origine_vin = Australia;
        }*/
    }
    int Get_An() {return an;}
    ///string Get_Brand_Vin_Soi() {return vin.Get_Nume();}
    ///string Get_Tip_Vin_Soi() {return vin.Get_Tip();}
    string Get_Tara_Origine() {return tara_origine;}
    istream &read(istream& in)
    {
        in>>vin_soi;
        in>>tara_origine;
        in>>an;
        in>>cantitate;
        in>>pret;
        return in;
    }
    ostream &print(ostream& out)
    {
        out<<vin_soi<<endl;
        out<<tara_origine<<endl;
        out<<an<<endl;
        out<<pret<<endl;
        return out;
    }
};


class Cartofi: public Produs
{
protected:
    /*enum
    {
        vag,
        rosii,
        albi
    }tip_cartofi;*/
    string tip_cartofi;

public:
    Cartofi(){masura = greutate;}
    Cartofi(double p, string tip)
    {
        pret = p;
        tip_cartofi = tip;
        /*switch(tip)
        {
            case 0: tip_cartofi = vag;
            case 1: tip_cartofi = rosii;
            case 2: tip_cartofi = albi;
        }*/
        masura = greutate; //kg
    }
    string Get_Tip_Cartofi() {return tip_cartofi;}
    istream &read(istream& in)
    {
        in>>tip_cartofi;
        in>>cantitate;
        in>>pret;
        return in;
    }
    ostream &print(ostream& out)
    {
        out<<tip_cartofi<<endl;
        out<<pret<<endl;
        return out;
    }
};


class Jucarii: public Produs
{
protected:
    string nume_jucarie;

public:
    Jucarii(){masura = bucata;}
    Jucarii(double p, string nume)
    {
        p = pret;
        nume_jucarie = nume;
        masura = bucata;
    }
    ~Jucarii(){}
    void Set_Nume_Jucarie(string name) {nume_jucarie = name;}
    string Get_Nume_Jucarie() {return nume_jucarie;}
    istream &read(istream& in)
    {
        in>>nume_jucarie;
        in>>cantitate;
        in>>pret;
        return in;
    }
    ostream &print(ostream& out)
    {
        out<<nume_jucarie<<endl;
        out<<pret<<endl;
        return out;
    }
};



enum tip_produs
{
    Ffaina,
    Bbere,
    Vvin_Varsat,
    Vvin_de_Soi,
    Ccartofi,
    Jjucarii
};

class Produs_Factory
{
public:
    static Produs* Get_Produs(tip_produs prod)
    {
        {
            Produs *produsul;
            switch(prod)
            {
                case Ffaina:
                    produsul = new Faina();
                    break;
                case Bbere:
                    produsul = new Bere();
                    break;
                case Vvin_Varsat:
                    produsul = new Vin_Varsat();
                    break;
                case Vvin_de_Soi:
                    produsul = new Vin_de_Soi();
                    break;
                case Ccartofi:
                    produsul = new Cartofi();
                    break;
                case Jjucarii:
                    produsul = new Jucarii();
                    break;

            }
            return produsul;
        }
    }

};





#endif
