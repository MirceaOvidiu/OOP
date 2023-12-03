#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Book
{
public:
    string name;
    string author;
    string release_year;

    Book(string given_name, string given_author, string given_release_year)
    {
        this->name = given_name;
        this->author = given_author;
        this->release_year = given_release_year;
    }
};

class Reader
{
private:
    string name;
    vector<Book> borrowed_books;

public:
    friend class Library;

    void read_book(Book book)
    {
        cout << "Reader " << this->name << " is reading " << book.name << " by " << book.author << "\n";
    }

    Book borrow_book(Book book)
    {
        cout << "\n"
             << "Reader " << this->name << " has borrowed " << book.name << "\n";
        this->borrowed_books.push_back(book);
        return book;
    }

    Book return_book(Book Book)
    {
        for (long long unsigned int i = 0; i < this->borrowed_books.size(); i++)
        {

            if (this->borrowed_books[i].name == Book.name)
            {
                this->borrowed_books.erase(this->borrowed_books.begin() + i);
                cout << "\n"
                     << "Reader " << this->name << " has returned " << Book.name << "\n";
                break;
            }
        }

        return Book;
    }

    void print_books()
    {
        cout << "\n"
             << "Reader " << this->name << " has the following books: \n";
        for (long long unsigned i = 0; i < this->borrowed_books.size(); i++)
        {
            cout << this->borrowed_books[i].name << "\n";
        }
    }

    string get_name()
    {
        return this->name;
    }

    Reader(string given_name)
    {
        this->name = given_name;
        /// initializam vectorul de carti imprumutate ca fiind gol
        this->borrowed_books = vector<Book>();
    }

    friend void see_reader_books(Reader reader);
};

class Library
{
protected:
    vector<Reader> readers{};

public:
    string name;
    vector<Book> book_list{};

    Book add_book(Book book)
    {
        cout << "The book " << book.name << " was added to the library " << this->name << "\n";
        this->book_list.push_back(book);
        return book;
    }

    void add_reader(Reader reader)
    {
        this->readers.push_back(reader);
    }

    void greet_reader(Reader reader)
    {
        cout << "The library welcomes " << reader.name << "!\n";
    }

    Book give_book(Book book)
    {
        for (long long unsigned int i = 0; i < this->book_list.size(); i++)
        {
            if (this->book_list[i].name == book.name)
            {
                this->book_list.erase(this->book_list.begin() + i);
                break;
            }
        }

        return book;
    }

    Library(string library_name)
    {
        this->name = library_name;
        this->book_list = vector<Book>();
    }

    void print_book_stock(Library library)
    {
        cout << "\n"
             << "The library " << library.name << " has the following books: \n";
        for (long long unsigned int i = 0; i < library.book_list.size(); i++)
        {
            cout << library.book_list[i].name << "\n";
        }
    }

    friend void see_reader_books(Reader reader);
};

void see_reader_books(Reader reader)
{
    cout << "\n"
         << "Reader " << reader.name << " has the following books: \n";
    for (long long unsigned int i = 0; i < reader.borrowed_books.size(); i++)
    {
        cout << reader.borrowed_books[i].name << "\n";
    }
}

int main()
{
    Library library = Library("Biblioteca Hotel P16");

    Reader gigel = Reader("Gigel");
    Reader ion = Reader("Ion");

    Book lotr = Book("Lord of the Rings", "J.R.R Tolkien", "1921");
    Book dune = Book("Dune", "Frank Herbert", "1964");
    Book metro = Book("Metro 2033", "Dimitryi Glukhovsky", "2005");

    library.add_book(lotr);
    library.add_book(dune);
    library.add_book(metro);
    library.print_book_stock(library);
    library.add_reader(gigel);
    library.add_reader(ion);
    library.greet_reader(gigel);
    library.greet_reader(ion);

    library.give_book(gigel.borrow_book(lotr));
    library.give_book(gigel.borrow_book(dune));
    /// bibiloteca are acces la lista cu ce carti are gigel
    see_reader_books(gigel);
    gigel.read_book(lotr);
    gigel.read_book(dune);

    library.add_book(gigel.return_book(dune));
    library.add_book(gigel.return_book(lotr));

    library.print_book_stock(library);

    return 0;
}