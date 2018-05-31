#ifndef CLIENT_H_INCLUDED
#define CLIENT_H_INCLUDED

#include "produs.h"


#include <vector>
//class Produs;

class Client //singleton
{
private:
    static Client *instance;
    vector <Produs*> stoc;
    Client();
    ~Client()
    {
        instance = NULL;
    }
public:
    static Client *Get_Instance()
    {
        if( instance == NULL )
        {
            instance = new Client();
        }
        return instance;
    }
    void Ad_Elem(Produs *ob)
    {
        stoc.push_back(ob);
    }
    void Clear()
    {
        for(auto prod: stoc)
            delete prod;
        stoc.clear();
        instance = NULL;
    }
    double Get_Pret_Lista()
    {
        double total=0;
        for(auto prod: stoc)
        {
            (*prod).Set_Cost();
            total += prod->Get_Cost();
        }
        return total;
    }
};


Client* Client::instance=NULL;
Client::Client(){}





#endif // MAGAZIN_H_INCLUDED

