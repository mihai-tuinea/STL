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
    int durata;
};

struct Doctor
{
    string IdDoctor;
    string Specializare;
    int available_time = 8;
    vector<string> solved_problems;
};

int main()
{
    ifstream inFile("input4_bonus.txt");

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
        inFile >> probleme[i].IdProblema >> probleme[i].Specializare >> probleme[i].durata;
    }

    int nr_doctori;
    inFile >> nr_doctori;
    vector<Doctor> doctori(nr_doctori);
    for (int i = 0; i < nr_doctori; i++)
    {
        inFile >> doctori[i].IdDoctor >> doctori[i].Specializare;
    }

    inFile.close();

    for (const auto &p: probleme)
    {
        auto it = find_if(begin(doctori), end(doctori), [&p](const Doctor &d)
        {
            return p.Specializare == d.Specializare && d.available_time >= p.durata;
        });
        if (it != end(doctori))
        {
            it->solved_problems.push_back(p.IdProblema);
            it->available_time -= p.durata;
        }
    }

    for (const auto &d: doctori)
    {
        if (!d.solved_problems.empty())
        {
            cout << d.IdDoctor << " " << d.solved_problems.size() << " ";
            for (const auto &s_p: d.solved_problems)
                cout << s_p << " ";
            cout << endl;
        }
    }
    return 0;
}
