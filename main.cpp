#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct Problema
{
    string IdProblema;
    string Specializare;
    int oraSosire;
    int durata;
    int prioritate;

    bool operator<(const Problema &other) const
    {
        if (this->oraSosire != other.oraSosire)
            return this->oraSosire > other.oraSosire;
        if (this->prioritate != other.prioritate)
            return this->prioritate < other.prioritate;
        return this->durata > other.durata;
    }
};

struct Doctor
{
    string IdDoctor;
    int nrSpecializari;
    vector<string> specializari;
    int program = 9;
    vector<pair<string, int> > solved_problems;
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
    priority_queue<Problema> pq;
    for (int i = 0; i < nr_probleme; i++)
    {
        inFile >> probleme[i].IdProblema >> probleme[i].Specializare >> probleme[i].oraSosire >> probleme[i].durata >>
                probleme[i].prioritate;
        pq.push(probleme[i]);
    }

    int nr_doctori;
    inFile >> nr_doctori;
    vector<Doctor> doctori(nr_doctori);
    for (int i = 0; i < nr_doctori; i++)
    {
        inFile >> doctori[i].IdDoctor >> doctori[i].nrSpecializari;
        for (int j = 0; j < doctori[i].nrSpecializari; j++)
        {
            string s;
            inFile >> s;
            doctori[i].specializari.push_back(s);
        }
    }

    inFile.close();

    while (!pq.empty())
    {
        const Problema p = pq.top(); // !!COPYING AND REFERENCING GIVE DIFFERENT RESULTS!!
        pq.pop();
        if (p.oraSosire + p.durata > 17)
            continue;
        auto it = find_if(begin(doctori), end(doctori), [&p](const Doctor &d)
        {
            bool found_specializare = false;
            for (const auto &spec: d.specializari)
                if (spec == p.Specializare)
                    found_specializare = true;
            return found_specializare && d.program <= p.oraSosire;
        });
        if (it != end(doctori))
        {
            it->solved_problems.emplace_back(p.IdProblema, p.oraSosire);
            it->program = p.oraSosire + p.durata;
        }
    }

    for (const auto &d: doctori)
    {
        if (!d.solved_problems.empty())
        {
            cout << d.IdDoctor << " " << d.solved_problems.size() << " ";
            for (const auto &s_p: d.solved_problems)
                cout << s_p.first << " " << s_p.second << " ";
            cout << endl;
        }
    }
    return 0;
}
