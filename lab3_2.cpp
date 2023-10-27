#include <iostream>
#include <cstdlib>
#include <string.h>

using namespace std;

class Student
{
private:
    string fname;
    string lname;
    string CNP;
    int birth_year;

    string faculty_name;
    int faculty_founding_year;

public:
    void set_student_data(string fname, string lname, int birth_year, string CNP, string faculty_name, int founding_year)
    {
        this->fname = fname;
        this->lname = lname;
        this->birth_year = birth_year;
        this->CNP = CNP;
        this->faculty_name = faculty_name;
        this->faculty_founding_year = founding_year;
    }

    string get_student_fname()
    {
        return this->fname;
    }

    string get_student_lname()
    {
        return this->lname;
    }

    int get_student_birth_year()
    {
        return this->birth_year;
    }

    string get_student_CNP()
    {
        return this->CNP;
    }

    string get_faculty()
    {
        return this->faculty_name;
    }

    int get_founding_year()
    {
        return this->faculty_founding_year;
    }

    string gender_by_CNP()
    {
        char identifier = this->get_student_CNP()[0];

        if (identifier == '1' || identifier == '5')
        {
            return "male student \n";
        }

        if (identifier == '2' || identifier == '6')
        {
            return "female student \n";
        }

        else
            return "idk man";
    }

    /// deja am un getter care face asta,
    /// dar in cerinta este o metoda
    int student_age()
    {
        return (this->birth_year);
    }

    int year_gap()
    {
        return (abs((this->faculty_founding_year) - this->birth_year));
    }
};

int main()
{
    Student *MyStudent1 = new Student();
    Student *MyStudent2 = new Student();

    MyStudent1->set_student_data("Ion", "Popescu", 2000, "1930806378260", "ACS", 1967);
    MyStudent2->set_student_data("Maria", "Popescu", 2001, "2931110326224", "ACS", 1967);

    cout << MyStudent1->gender_by_CNP();
    cout << MyStudent2->gender_by_CNP();

    cout << MyStudent1->year_gap() << "\n";
    cout << MyStudent2->year_gap();

    return 0;
}
