#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

class Employee
{
protected:
    string status;

public:
    string name;
    Employee()
    {
        this->name = "NA";
        this->status = "NA";
    }
    Employee(string given_name, string given_status)
    {
        this->name = given_name;
        this->status = given_status;
    };

    void print_special_skills()
    {
        std::cout << "grew up with Bill Gates \n";
    }

    void years_of_experience()
    {
        std::cout << "years of experience: over 10 years \n";
    }

    void print_employee_details()
    {
        std::cout << "\n"
                  << this->name << ", " << this->status << "\n";
        print_special_skills();
        years_of_experience();
    }

    string get_name()
    {
        return this->name;
    }

    string get_status()
    {
        return this->status;
    }
};

class Junior : public Employee
{
public:
    Junior()
    {
        this->name = "NA";
        this->status = "NA";
    }
    Junior(string given_name, string given_status)
    {
        this->name = given_name;
        this->status = given_status;
    };

    void print_special_skills()
    {
        std::cout << "my special skill is: DELETE PROD \n";
    }

    void years_of_experience()
    {
        std::cout << "years of experience: usually one \n";
    }

    void print_employee_details()
    {
        std::cout << "\n"
                  << this->name << ", " << this->status << "\n";
        print_special_skills();
        years_of_experience();
    }
};

class Mid : public Junior
{
public:
    Mid()
    {
        this->name = "NA";
        this->status = "NA";
    }

    Mid(string given_name, string given_status)
    {
        this->name = given_name;
        this->status = given_status;
    };

    void print_special_skills()
    {
        std::cout << "my special skill is: git push -f \n";
    }

    void years_of_experience()
    {
        std::cout << "years of experience: 2 - 5 \n";
    }

    void print_employee_details()
    {
        std::cout << "\n"
                  << this->name << ", " << this->status << "\n";
        print_special_skills();
        years_of_experience();
    }
};

class Senior : public Mid
{
public:
    Senior(string given_name, string given_status)
    {
        this->name = given_name;
        this->status = given_status;
    }

    void print_special_skills()
    {
        std::cout << "my special skill is: answering stackoverflow questions \n";
    }

    void years_of_experience()
    {
        std::cout << "years of experience: more than 5 \n";
    }

    void print_employee_details()
    {
        std::cout << "\n"
                  << this->name << ", " << this->status << "\n";
        print_special_skills();
        years_of_experience();
    }
};

class Company
{

private:
    int profit;
    std::vector<std::string> employees{};

public:
    string name;
    string activity_domain;
    int employee_count = sizeof(employees);

    Company(string given_name, string given_activity_domain, int given_profit)
    {
        this->name = given_name;
        this->activity_domain = given_activity_domain;
        this->profit = given_profit;
    }

    void add_employee(string employee_name)
    {
        employees.push_back(employee_name);
    }

    void list_employees()
    {

        std::cout << "\n The employees are: ";
        for (std::vector<std::string>::size_type i = 0; i < employees.size(); i++)
            std::cout << employees[i] << " ";
    }
};

int main()
{
    Company MyCompany("BeerDefender", "CyberSec", 13494);
    Employee John("John", "Manager");
    MyCompany.add_employee(John.get_name());
    John.print_employee_details();

    Junior Mike("Mike", "junior");
    MyCompany.add_employee(Mike.get_name());
    Mike.print_employee_details();

    Mid Phil("Phil", "mid");
    MyCompany.add_employee(Phil.get_name());
    Phil.print_employee_details();

    Senior Chad("Chad", "senior");
    MyCompany.add_employee(Chad.get_name());
    Chad.print_employee_details();

    MyCompany.list_employees();

    return 0;
}