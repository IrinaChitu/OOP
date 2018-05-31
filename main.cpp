#include <iostream>
#include <fstream>


#include "magazin.h"
#include "client.h"

using namespace std;

ifstream fin("date.in");
ofstream fout("date.out");

///vezi cand atribui tipul unui produs in constructor ca dai cu enum
///nu uita ca poate da cerinte vagi clientul deci sa faci constructor si fara param (eventual da-le valori din alea de nu trebuie neaparat citite
///^i-am pus in enum vag



int main()
{
    int n, de_cumparat;
    fin>>n; //nr cumparatori
    Magazin* stoc = Magazin::Get_Instance();

    //initializam stocul cu toate tipurile de produse, pt a fi mai usor sa cautam dupa cel mai scump obiect cand e vaga cerinta
    ///introduc manual preturile, puteau fi citite si dintr un fisier separat
    ///pt a arata cu acuratete cum functioneaza trebuiau introduse mult mai multe date, am introdus minimul necesar
    ///si acum ca e de tip produs dupa pt merge sa fie orice fel de produs derivat vreau eu :D
    Produs* pt = new Faina(2, "calitate_1");
    (*stoc).Ad_Elem( pt );
    pt = new Faina(4, "calitate_1");
    (*stoc).Ad_Elem( pt );
    pt = new Faina(6, "calitate_1");
    (*stoc).Ad_Elem( pt );

    ///trebuie sa dau delete la pt dar imi sterge si obiectul din vector...
    pt=NULL;
    delete pt;

    ///nu merge tot cu pt desi am dat delete
    Bere* pt2 = new Bere(9, "Silva", "blonda");
    stoc->Ad_Elem(pt2);
    pt2 = new Bere(10, "Heineken", "bruna");
    stoc->Ad_Elem(pt2);
    pt2 = new Bere(8, "Ursus", "bruna");
    stoc->Ad_Elem(pt2);
    pt2 = new Bere(16, "Efes", "blonda");
    stoc->Ad_Elem(pt2);
    pt2=NULL;
    delete pt2;


    Vin_Varsat* pt3 = new Vin_Varsat(17, "rosu_sec");
    stoc->Ad_Elem(pt3);
    pt3 = new Vin_Varsat(16, "alb_sec");
    stoc->Ad_Elem(pt3);
    pt3=NULL;
    delete pt3;


    //Vin_de_Soi vinut(25, "Cabernet_Savignon", "rosu_sec", "Franta", 2000);

    Vin_de_Soi* pt4 = new Vin_de_Soi(25, "Cabernet_Savignon", "rosu_sec", "Franta", 2000);
    stoc->Ad_Elem(pt4);
    pt4 = new Vin_de_Soi(29, "Merlot", "rosu_dulce", "Argentina", 2005);
    stoc->Ad_Elem(pt4);
    pt4 = new Vin_de_Soi(31, "Savignon_Blanc", "alb_dulce", "Chile", 2003);
    stoc->Ad_Elem(pt4);
    pt4 = new Vin_de_Soi(45, "Chardonnay", "alb_dulce", "Australia", 1998);
    stoc->Ad_Elem(pt4);
    pt4=NULL;
    delete pt4;

    Cartofi* pt5 = new Cartofi(13, "rosii");
    stoc->Ad_Elem(pt5);
    pt5 = new Cartofi(14, "albi");
    stoc->Ad_Elem(pt5);
    pt5=NULL;
    delete pt5;

    Jucarii* pt6 = new Jucarii(20, "Masina");
    stoc->Ad_Elem(pt6);
    pt6 = new Jucarii(34, "Tren");
    stoc->Ad_Elem(pt6);
    pt6=NULL;
    delete pt6;

    //stoc->Afisare();

    int i, j;
    for(j=1; j<=n; j++) //pt fiecare cumparator
    {
        fin>>de_cumparat; //nr obiecte
        Client* lista_de_cumparaturi = Client::Get_Instance();
        for(i=1; i<=de_cumparat; i++)
        {
            ///mai trebuie in cazul in care e vag sa dau search prin obiecte si sa il iau pe cel mai scump
            string nume_produs;
            fin>>nume_produs;
            //modificam cantitate_vanduta si bani_incasati la fiecare obiect adaugat
            if(nume_produs == "Faina")
            {
                Produs *pt_produs = Produs_Factory::Get_Produs(Ffaina);
                Faina* pt_temp = static_cast<Faina*>(pt_produs);
                (*pt_temp).read(fin);
                ///aici am fi modificat daca voiam fiecare tip de element vandut
                ///^in variabilele statice din produsele din stoc
                (*lista_de_cumparaturi).Ad_Elem( pt_temp );

            }
            if(nume_produs == "Bere")
            {
                Produs *pt_produs = Produs_Factory::Get_Produs(Bbere);
                Bere* pt_temp = static_cast<Bere*>(pt_produs);
                (*pt_temp).read(fin);
                (*lista_de_cumparaturi).Ad_Elem( pt_temp );
            }
            if(nume_produs == "VinVarsat")
            {
                Produs *pt_produs = Produs_Factory::Get_Produs(Vvin_Varsat);
                Vin_Varsat* pt_temp = static_cast<Vin_Varsat*>(pt_produs);
                (*pt_temp).read(fin);
                (*lista_de_cumparaturi).Ad_Elem( pt_temp );
            }
            if(nume_produs == "VindeSoi")
            {
                Produs *pt_produs = Produs_Factory::Get_Produs(Vvin_de_Soi);
                Vin_de_Soi* pt_temp = static_cast<Vin_de_Soi*>(pt_produs);
                (*pt_temp).read(fin);
                (*lista_de_cumparaturi).Ad_Elem( pt_temp );
            }
            if(nume_produs == "Cartofi")
            {
                Produs *pt_produs = Produs_Factory::Get_Produs(Ccartofi);
                Cartofi* pt_temp = static_cast<Cartofi*>(pt_produs);
                (*pt_temp).read(fin);
                (*lista_de_cumparaturi).Ad_Elem( pt_temp );
            }
            if(nume_produs == "Jucarii")
            {
                Produs *pt_produs = Produs_Factory::Get_Produs(Jjucarii);
                Jucarii* pt_temp = static_cast<Jucarii*>(pt_produs);
                (*pt_temp).read(fin);
                (*lista_de_cumparaturi).Ad_Elem( pt_temp );
            }
        }
        double price = lista_de_cumparaturi->Get_Pret_Lista();
        cout<<"Costul total este: "<<price;
        cout<<endl<<"Sunteti de acord?"<<endl;
        string raspuns;
        cin>>raspuns;
        if(raspuns == "Da")
        {
            ///cumparatorul e de acord cu lista si se ia din stoc
            Produs::Add_Vandut(de_cumparat, price);
        }
        if(raspuns == "Nu")
            ///cumparatorul nu va mai achizitiona produsele
            continue;
        lista_de_cumparaturi->Clear();
        fin.get();
    }

    cout<<Produs::Get_CantitateVanduta()<<endl;
    cout<<Produs::Get_PretTotal()<<endl;



}
