#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct Problema
{
    string IdProblema;
    string Specializare;
};

struct Doctor
{
    string IdDoctor;
    string Specializare;
};

int main()
{
    ifstream inFile("input.txt");

    int nr_probleme;
    inFile >> nr_probleme;
    vector<Problema> probleme(nr_probleme);
    for (int i = 0; i < nr_probleme; i++)
    {
        inFile >> probleme[i].IdProblema >> probleme[i].Specializare;
    }

    int nr_doctori;
    inFile >> nr_doctori;
    vector<Doctor> doctori(nr_doctori);
    for (int i = 0; i < nr_doctori; i++)
    {
        inFile >> doctori[i].IdDoctor >> doctori[i].Specializare;
    }

    for (const auto& p : probleme)
    {
        auto it = find_if(begin(doctori), end(doctori), [&p](const Doctor& d) {return p.Specializare == d.Specializare; });
        if (it != end(doctori))
            cout << p.IdProblema << " Acceptat\n";
        else
            cout << p.IdProblema << " Respins\n";
    }
    return 0;
}