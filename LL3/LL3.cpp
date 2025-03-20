#include <iostream>
#include<string>
#include <fstream>
#include<vector>
using namespace std;

// Sistem de gestionare a parcarii

class IVehicul {
    public:
        virtual int calculeazaTimp() const = 0;
        virtual double calculeazaTarif() const = 0;
        virtual ~IVehicul() {}
    };

class Vehicul: public IVehicul
{
protected:
    string nr_inmatriculare;
    int ora_intrarii, ora_iesirii;

public:
    int calculeazaTimp() const override { return ora_iesirii - ora_intrarii; }

    virtual double calculeazaTarif() const override { return 0 * calculeazaTimp(); }

    void setOraIntrarii(int ora_intrarii){ this->ora_intrarii = ora_intrarii; }

    void setOraIesirii(int ora_iesirii){ this->ora_iesirii = ora_iesirii; }

    void setNrInmatriculare(string nr_inmatriculare){ this->nr_inmatriculare = nr_inmatriculare; }

    virtual string getTip(){ return "Vehicul";}

    string getNrInmatriculare(){ return nr_inmatriculare; }


    void AfisareInfo(){
        cout << "Tip: " << getTip() << endl;
        cout << "Numar de inmatriculare: " << nr_inmatriculare << endl;
        cout << "Timp petrecut in parcare: " << calculeazaTimp() << " ore" << endl;
        cout << "Tarif total: " << calculeazaTarif() << " lei" << endl;
        cout << endl;
    }

};

class Masina: public Vehicul{  
public:
    Masina(){

    }

    Masina(string nr_inmatriculare, int ora_intrarii, int ora_iesirii){
        this->nr_inmatriculare = nr_inmatriculare;
        this->ora_intrarii = ora_intrarii;
        this->ora_iesirii = ora_iesirii;
    }

    double calculeazaTarif() const override { return 5 * Vehicul::calculeazaTimp(); }

    string getTip() override { return "Masina";}

};

class Motocicleta: public Vehicul{   
public:
    Motocicleta(){

    }

    Motocicleta(string nr_inmatriculare, int ora_intrarii, int ora_iesirii){
        this->nr_inmatriculare = nr_inmatriculare;
        this->ora_intrarii = ora_intrarii;
        this->ora_iesirii = ora_iesirii;
    }

    double calculeazaTarif() const override { return 3 * Vehicul::calculeazaTimp(); }

    string getTip() override { return "Motocicleta";}
};

class Camion: public Vehicul{
public:
    Camion(){

    }

    Camion(string nr_inmatriculare, int ora_intrarii, int ora_iesirii){
        this->nr_inmatriculare = nr_inmatriculare;
        this->ora_intrarii = ora_intrarii;
        this->ora_iesirii = ora_iesirii;
    }

    double calculeazaTarif() const override  { return 10 * Vehicul::calculeazaTimp();}

    string getTip() override { return "Camion";}
};

class Bicicleta: public Vehicul{
public:
    Bicicleta(){

    }

    Bicicleta(string nr_inmatriculare, int ora_intrarii, int ora_iesirii){
        this->nr_inmatriculare = nr_inmatriculare;
        this->ora_intrarii = ora_intrarii;
        this->ora_iesirii = ora_iesirii;
    }

    double calculeazaTarif() const override  { return (2 * Vehicul::calculeazaTimp() - 2) > 0 ? (2 * Vehicul::calculeazaTimp() - 2) : 0; }

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

    vehicule.push_back(new Masina("B123XYZ", 8, 12));
    vehicule.push_back(new Motocicleta("B987XYZ", 9, 11));
    vehicule.push_back(new Camion("B456XYZ", 7, 13));

    // for (auto v : vehicule)
    // {
    //     v->AfisareInfo();
    //     delete v;
    // }
    
    cout << " Tip\t\t" << "Nr. inmatriculare\t" << "Timpul petrecut\t\t" << "Tarif" << endl;
    cout << "-----------------------------------------------------------------------" << endl;
    int count = 1;
    for (auto vehicul : vehicule)
    {
        cout << count << ". " << vehicul->getTip() << "\t\t" << vehicul->getNrInmatriculare() << "\t\t"
         << vehicul->calculeazaTimp() << " ore\t\t\t" << vehicul->calculeazaTarif() << " lei" << endl;
        
        count++;
    }
    
    fin.close();

    return 0;
}