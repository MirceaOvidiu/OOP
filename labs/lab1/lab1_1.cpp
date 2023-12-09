#include <iostream>
#include <string>

using namespace std;

class Student
{
public:
    /// @brief personal data
    string name;
    string surname;
    string group;

    /// @brief extra
    std::string dsa_pros;
    std::string dsa_cons;
    std::string summer_activites;
    std::string future_plans;
};

int main()
{
    Student Me;
    /// data
    Me.name = "Mircea";
    Me.surname = "Dodi";
    Me.group = "321AC";

    /// extra
    Me.dsa_pros = R"(pro: 
    laboratoare concise, 
    informatiile din lab erau 
    cele necesare pt a intelege si aprofunda,
    accent pus pe cautat
    si inteles logic,
    intrebarile si colocviul de tip interviu,
    teme interesanta)";

    Me.dsa_cons = "contra: sincer, nu prea am ce sa reprosez";

    Me.summer_activites = R"(activitati pe vara: 
    am intrat putin in cybersec, atat blue team si red team
    (ex: kali, nmap, metasploit, msfvenom, wireshark),
    criptari de mesaje in python 
    si am inceput sa aprofundez ceea ce stiam in C# pt a face 2 proiecte
    (mic joc in Unity si unul .NET), ghidat de un curs pe udemy)";

    Me.future_plans = R"(planuri pe viitor: 
                sa gasesc practica dupa anul 2 momentan)";

    cout << Me.name << " " << Me.surname << " " << Me.group << "\n"
         << Me.dsa_pros << "\n"
         << Me.dsa_cons << "\n"
         << Me.future_plans << "\n"
         << Me.summer_activites;

    return 0;
}