#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

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

    if (!inFile)
    {
        cerr << "Fisierul de intrare nu poate fi deschis!" << endl;
        return EXIT_FAILURE;
    }

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

    inFile.close();

    for (const auto& p : probleme)
    {
        auto it = find_if(begin(doctori), end(doctori), [&p](const Doctor& d) {return p.Specializare == d.Specializare; });
        if (it != end(doctori))
        {
            cout << it->IdDoctor << " " << p.IdProblema << endl;
            doctori.erase(it);
        }
    }
    return 0;
}