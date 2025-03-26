#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct Problem
{
    string name;
    string skill;
    int arrival{};
    int duration{};
    int priority{};

    bool operator<(const Problem &other) const
    {
        if (this->arrival != other.arrival)
            return this->arrival > other.arrival;
        if (this->priority != other.priority)
            return this->priority < other.priority;
        return this->duration > other.duration;
    }
};

struct Doctor
{
    string name;
    int numSkills{};
    int workingHours = 9;
    vector<string> skills;
    vector<pair<string, int> > solvedProblems;
};

int main()
{
    ifstream fin("input4_bonus.txt");

    if (!fin)
    {
        cerr << "Fisierul de intrare nu poate fi deschis!" << endl;
        return EXIT_FAILURE;
    }

    int numProblems;
    fin >> numProblems;
    vector<Problem> problems(numProblems);
    priority_queue<Problem> pq;
    for (int i = 0; i < numProblems; i++)
    {
        fin >> problems[i].name >> problems[i].skill >> problems[i].arrival >> problems[i].duration >>
                problems[i].priority;
        pq.push(problems[i]);
    }

    int numDoctors;
    fin >> numDoctors;
    vector<Doctor> doctors(numDoctors);
    for (int i = 0; i < numDoctors; i++)
    {
        fin >> doctors[i].name >> doctors[i].numSkills;
        for (int j = 0; j < doctors[i].numSkills; j++)
        {
            string skill;
            fin >> skill;
            doctors[i].skills.push_back(skill);
        }
    }

    fin.close();

    while (!pq.empty())
    {
        const Problem currentProblem = pq.top();
        pq.pop();
        if (currentProblem.arrival + currentProblem.duration > 17)
            continue;
        auto it = find_if(begin(doctors), end(doctors), [&currentProblem](const Doctor &doc) {
            bool solvable = false;
            for (const auto &spec: doc.skills)
                if (spec == currentProblem.skill)
                {
                    solvable = true;
                    break;
                }
            return solvable && doc.workingHours <= currentProblem.arrival;
        });
        if (it != end(doctors))
        {
            it->solvedProblems.emplace_back(currentProblem.name, currentProblem.arrival);
            it->workingHours = currentProblem.arrival + currentProblem.duration;
        }
    }

    for (const auto &doc: doctors)
    {
        if (!doc.solvedProblems.empty())
        {
            cout << doc.name << " " << doc.solvedProblems.size() << " ";
            for (const auto &[name, arrival]: doc.solvedProblems)
                cout << name << " " << arrival << " ";
            cout << endl;
        }
    }
    return 0;
}
