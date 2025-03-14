#include <iostream>
#include<string>
#include <fstream>
#include<vector>
using namespace std;

// Sistem de gestionare a parcarii

class Vehicul
{
protected:
    string nr_inmatriculare;
    int ora_intrarii, ora_iesirii;

public:
    int TimpTotal(){
        return ora_iesirii - ora_intrarii;
    }

    virtual int CalculTarif(){
        return 0 * TimpTotal();
    }

    void setOraIntrarii(int ora_intrarii){
        this->ora_intrarii = ora_intrarii;
    }

    void setOraIesirii(int ora_iesirii){
        this->ora_iesirii = ora_iesirii;
    }

    void setNrInmatriculare(string nr_inmatriculare){
        this->nr_inmatriculare = nr_inmatriculare;
    }

    virtual string getTip(){ return "Vehicul";}

    void AfisareInfo(){
        cout << "Tip: " << getTip() << endl;
        cout << "Numar de inmatriculare: " << nr_inmatriculare << endl;
        cout << "Timp petrecut in parcare: " << TimpTotal() << " ore" << endl;
        cout << "Tarif total: " << CalculTarif() << " lei" << endl;
        cout << endl;
    }

};

class Masina: public Vehicul{  
public:
    int CalculTarif() override{ return 5 * Vehicul::TimpTotal(); }

    string getTip() override { return "Masina";}
};

class Motocicleta: public Vehicul{   
public:
    int CalculTarif() override{ return 3 * Vehicul::TimpTotal(); }

    string getTip() override { return "Motocicleta";}
};

class Camion: public Vehicul{
public:
    int CalculTarif() override { return 10 * Vehicul::TimpTotal();}

    string getTip() override { return "Camion";}
};

class Bicicleta: public Vehicul{
public:
    int CalculTarif() override { return (2 * Vehicul::TimpTotal() - 2) > 0 ? (2 * Vehicul::TimpTotal() - 2) : 0; }

    string getTip() override { return "Bicicleta"; }
};

int main(){
    
    string path = "vehicule.txt";
    ifstream fin(path);
    if (!fin.is_open()) {
        cout << "Eroare la deschiderea fisierului " << path << " !" << endl;
        return 1;
    }

    vector<Vehicul*> vehicule;
    string tip_vehicul, nr_inmatriculare;
    int ora_intrarii, ora_iesirii;
    

    while (fin >> tip_vehicul >> nr_inmatriculare >> ora_intrarii >> ora_iesirii)
    {
        Vehicul* vehicul = nullptr;

        if (tip_vehicul == "Masina"){
            vehicul = new Masina;
        }
        else if (tip_vehicul == "Motocicleta")
        {
            vehicul = new Motocicleta;
        }
        else if (tip_vehicul == "Camion")
        {
            vehicul = new Camion;
        }    
        else if (tip_vehicul == "Bicicleta")
        {
            vehicul = new Bicicleta;
        }     

        vehicul->setNrInmatriculare(nr_inmatriculare);
        vehicul->setOraIntrarii(ora_intrarii);
        vehicul->setOraIesirii(ora_iesirii);
        
        vehicule.push_back(vehicul);
    }

    for (auto v : vehicule)
    {
        v->AfisareInfo();
        delete v;
    }
    
    
    fin.close();

    return 0;
}