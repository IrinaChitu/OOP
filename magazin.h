#ifndef MAGAZIN_H_INCLUDED
#define MAGAZIN_H_INCLUDED

#include "produs.h"


#include <vector>

using namespace std;
//class Produs;

class Magazin //singleton
{
private:
    static Magazin *instance;
    vector <Produs*> stoc;
    Magazin();
    ~Magazin(){}
public:
    static Magazin *Get_Instance()
    {
        if( instance == NULL )
        {
            instance = new Magazin();
        }
        return instance;
    }
    void Ad_Elem(Produs *ob)
    {
        stoc.push_back(ob);
    }

    /*void Afisare() //mai trebuie convertit inainte de afisare
    {
        for(auto prod: stoc)
        {
            (*prod).print(cout);
            cout<<endl;
        }
    }*/
    /*void Resize(int n)
    {
        stoc.resize(n+1);
    }
    void Add_Elem(Faina *obiect)
    {
        stoc.push_back(obiect);
    }
    void Add_Elem(Bere *obiect)
    {
        stoc.push_back(obiect);
    }
    void Add_Elem(Vin_Varsat *obiect)
    {
        stoc.push_back(obiect);
    }
    void Add_Elem(Vin_de_Soi *obiect)
    {
        stoc.push_back(obiect);
    }
    void Add_Elem(Cartofi *obiect)
    {
        stoc.push_back(obiect);
    }
    void Add_Elem(Jucarii *obiect)
    {
        stoc.push_back(obiect);
    }*/

};


Magazin* Magazin::instance=NULL;
Magazin::Magazin(){}





#endif // MAGAZIN_H_INCLUDED
