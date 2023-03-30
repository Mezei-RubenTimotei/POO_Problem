#include <iostream>
#include <list>
#include <fstream>

using namespace std;

ifstream fin("in.txt");
ofstream fout("out.txt");

class Decoratiune{
    int inaltime, serie;
    float pret;
public:
    Decoratiune(int inaltime , int serie, float pret){
        this -> inaltime = inaltime;
        this -> serie = serie;
        this -> pret = pret;
    }
    virtual void Afisare(){
        cout << "-----------------------------" << endl;
        cout << "Inaltime : " << inaltime << endl;
        cout << "Serie : " << serie << endl;
        cout << "Pret :" << pret << endl;
    }
    virtual void Scriere()
    {
        fout << "-----------------------------" << endl;
        fout << "Inaltime : " << inaltime << endl;
        fout << "Serie : " << serie << endl;
        fout << "Pret :" << pret << endl;
    }
    int get_serie()
    {
        return serie;
    }
    virtual string Autor(){
        return "";
    }
    virtual string get_denumire(){
        return "";
    }
    void modificarePret(float pret_nou)
    {
        this -> pret = pret_nou;
    }

};

enum Material{
    lemn,
    bronz,
    lut
};
string MaterialText[] = {"lemn" ,"bronz" , "lut"};

class Statueta : public Decoratiune{
    Material material;
    string autor;
public:
    Statueta(int inaltime,int serie, float pret, Material material , string autor):Decoratiune(inaltime,serie,pret){
        this -> material = material;
        this -> autor = autor;
    }
    void Afisare(){
        Decoratiune :: Afisare();
        cout << "Material : " << MaterialText[material] << endl;
        cout << "Autor : " << autor << endl;
        cout << "-----------------------------" << endl;
    }
    void Scriere(){
        Decoratiune :: Scriere();
        fout << "Material : " << MaterialText[material] << endl;
        fout << "Autor : " << autor << endl;
        fout << "-----------------------------" << endl;
    }
    string Autor(){
        return autor;
    }

};

enum Tip{
    tufa,
    copaci
};

string TipText[] = {"tufa","copaci"};

class Arbust : public Decoratiune{
    Tip tip;
    string denumire;
public :
    Arbust(int inaltime,int serie,float pret,Tip tip,string denumire):Decoratiune(inaltime,serie,pret)
    {
        this -> tip = tip;
        this -> denumire = denumire;
    }
    void Afisare(){
        Decoratiune :: Afisare();
        cout << "Tip : " << TipText[tip] << endl;
        cout << "Denumire : " << denumire << endl;
        cout << "-----------------------------" << endl;
    }
    void Scriere(){
        Decoratiune :: Scriere();
        fout << "Tip : " << TipText[tip] << endl;
        fout << "Denumire : " << denumire << endl;
        fout << "-----------------------------" << endl;
    }
    string get_denumire()
    {
        return denumire;
    }
};

istream& operator >> (istream& in , Statueta *&c)
{
    int serie,inaltime,nr;
    float pret;
    string autor;
    cout << "Seria : ";
    cin >> serie;
    cout << "Inaltime : ";
    cin >> inaltime;
    cout << "Pret : ";
    cin >> pret;
    cout << "Autor : ";
    cin >> autor;
    cout << "0-lemn ,1-bronz ,2-lut : ";
    cin >> nr;
    c = new Statueta(inaltime,serie,pret,(Material)nr,autor);
    return in;
}

istream& operator >> (istream& in , Arbust *&d)
{
    int serie,inaltime,nr;
    float pret;
    string den;
    cout << "Seria : ";
    cin >> serie;
    cout << "Inaltime : ";
    cin >> inaltime;
    cout << "Pret : ";
    cin >> pret;
    cout << "Denumire : ";
    cin >> den;
    cout << "0 - tufa , 1 - copaci";
    cin >> nr;
    d = new Arbust(inaltime,serie,pret,(Tip)nr,den);
    return in;
}

ifstream& operator >> (ifstream& in , Statueta *&c)
{
    int serie,inaltime,nr;
    float pret;
    string autor;
    fin >> serie;
    fin >> inaltime;
    fin >> pret;
    fin >> autor;
    fin >> nr;
    c = new Statueta(inaltime,serie,pret,(Material)nr,autor);
    return in;
}

ifstream& operator >> (ifstream& in , Arbust *&d)
{
    int serie,inaltime,nr;
    float pret;
    string den;
    fin >> serie;
    fin >> inaltime;
    fin >> pret;
    fin >> den;
    fin >> nr;
    d = new Arbust(inaltime,serie,pret,(Tip)nr,den);
    return in;
}

void AdaugareManuala(int cat, list <Decoratiune*> &decoratii)
{
    Decoratiune *deco = NULL;
    Statueta *c = NULL;
    Arbust *d = NULL;
    if(cat == 0)
        cin >> c, deco = c;
    if(cat == 1)
        cin >> d, deco = d;
    if(deco != NULL)
        decoratii.push_back(deco);
}

void AdaugareFisier(list <Decoratiune*> &decoratii)
{
    Decoratiune *deco = NULL;
    Statueta *c = NULL;
    Arbust *d = NULL;
    int cat;
    while(fin >> cat)
    {
        if(cat == 0)
            cin >> c, deco = c;
        if(cat == 1)
            cin >> d, deco = d;
        if(deco != NULL)
            decoratii.push_back(deco);
    }
}

void ScriereFisier(list <Decoratiune*> decoratii)
{
    for (auto i = decoratii.begin(); i != decoratii.end(); i++) {
        (*i) -> Scriere();
    }
}

void Afisare(list <Decoratiune*> decoratii)
{
    for (auto i = decoratii.begin(); i != decoratii.end(); i++) {
        (*i) -> Afisare();
    }
}

void Cautare(list <Decoratiune*> decoratii)
{
    string denumire;
    cout << "Cauta denumirea arbustului : ";
    cin >> denumire;
    for (auto i = decoratii.begin(); i != decoratii.end(); i++) {
        if((*i) -> get_denumire() == denumire)
            (*i) -> Afisare();
    }
}

void Stergere(list <Decoratiune*> &decoratii)
{
    int serie;
    cout << "Cauta serie : ";
    cin >> serie;
    for (auto i = decoratii.begin(); i != decoratii.end(); i++) {
        if((*i) -> get_serie() == serie){
            decoratii.erase(i);
            break;
        }
    }
}

void ModificarePret(list <Decoratiune*> &decoratii){

    float pret;
    string autor;
    cout << "Autorul statuetei cautat :";
    cin >> autor;
    cout << "Pretul nou";
    cin >> pret;
    for (auto i = decoratii.begin(); i != decoratii.end(); i++) {
        if((*i) -> Autor().compare(autor) == 0){
            (*i) -> modificarePret(pret);
        }
    }

}


int main() {

    int op,cat;
    list <Decoratiune*> decoratii;

    do{
        cout << "0.Iesire" << endl;
        cout << "1.Adaugare manauala" << endl;
        cout << "2.Adaugare in fisier" << endl;
        cout << "3.Scriere in fisier" << endl;
        cout << "4.Afisare" << endl;
        cout << "5.Cautare dupa serie" << endl;
        cout << "6.Stergere dupa serie" << endl;
        cout << "7.Modificare pret dupa autorul statuetei" << endl;

        cout << "Optiunea dvs este :";
        cin >> op;

        switch(op)
        {
            case 0:
                exit(0);
            case 1:
                cout << "0 - Statueta , 1 - Arbust";
                while(1){
                    cin >> cat;
                    if(cat == 0 || cat == 1)
                        break;
                    else
                        cout << "Trebuie sa alegi intre 0 sau 1!";
                }
                AdaugareManuala(cat,decoratii);
                break;
            case 2:
                AdaugareFisier(decoratii);
                break;
            case 3:
                ScriereFisier(decoratii);
                break;
            case 4:
                Afisare(decoratii);
                break;
            case 5:
                Cautare(decoratii);
                break;
            case 6:
                Stergere(decoratii);
                break;
            case 7:
                ModificarePret(decoratii);
                break;
            default :
                cout << endl;
                cout << "Optiune gresita!" << endl;
        }
    }while(op != 0);


    return 0;
}
