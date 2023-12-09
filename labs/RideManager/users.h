#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <fstream>
#include <sstream>
#include "encryptor.h"

using namespace std;

class loginUtils {
public:
    /// @brief This struct is used to store the user data read from the file.
    typedef struct user_data {
        string username;
        string email;
        string user_level;
        string user_group;
        string security_question;
        string security_answer;
        string encrypted_password;
    } USER;

    static vector<USER> readUserData(const string &filename) {
        vector<USER> users;  // Vector to store USER structs

        ifstream inputFile(filename);

        if (!inputFile.is_open()) {
            cerr << "Error opening the file." << endl;
            return users;
        }

        string line;
        while (getline(inputFile, line)) {
            istringstream iss(line);
            USER user;

            // Read each field from the CSV line
            getline(iss, user.username, ',');
            getline(iss, user.email, ',');
            getline(iss, user.user_level, ',');
            getline(iss, user.user_group, ',');
            getline(iss, user.security_question, ',');
            getline(iss, user.security_answer, ',');

            // Read the whole string for encrypted password
            getline(iss, user.encrypted_password, ',');

            // Add the populated USER struct to the vector
            users.push_back(user);
        }

        // Close the file after reading
        inputFile.close();

        return users;
    }

    /*
// Function to print users as a test
    static void printUsers(const vector<USER> &fileContent) {
        for (const auto &i: fileContent) {
            cout << "Username: " << i.username << endl;
            cout << "Email: " << i.email << endl;
            cout << "User Level: " << i.user_level << endl;
            cout << "User Group: " << i.user_group << endl;
            cout << "Security Question Index: " << i.security_question << endl;
            cout << "Security Question Answer: " << i.security_answer << endl;
            cout << "RSA Encrypted Password: " << i.encrypted_password << endl;
            cout << endl;
        }
    }
*/
    static bool isUsernameUsed(const string &username, const vector<loginUtils::USER> &fileContent) {
        bool doesUserExist = false;
        ///usernames are stored on column 0
        for (const auto &i: fileContent) {
            if (i.username == username) {
                doesUserExist = true;
                break;
            }
        }
        return doesUserExist;
    }

    static bool isEmailUsed(const string &email, const vector<loginUtils::USER> &fileContent) {
        bool isEmailUsed = false;
        ///emails are stored on column 1
        for (const auto &i: fileContent) {
            if (i.email == email) {
                isEmailUsed = true;
                break;
            }
        }
        return isEmailUsed;
    }

    static int getUserIndex(const string &username, const vector<loginUtils::USER> &fileContent) {
        int userIndex = 0;
        ///usernames are stored on column 0
        for (int i = 0; i < fileContent.size(); ++i) {
            if (fileContent[i].username == username) {
                userIndex = i;
                break;
            }
        }
        return userIndex;
    }

    static string getUserSecurityQuestion(unsigned int user_index, vector<loginUtils::USER> fileContent) {
        return (fileContent[user_index].security_question);
    }

    static string getUserEncryptedPassword(unsigned int user_index, vector<loginUtils::USER> fileContent) {
        return (fileContent[user_index].encrypted_password);
    }

    static std::vector<int> assignsUserCondiments(int chosen_security_question) {
        std::vector<int> condiments;
        switch (chosen_security_question) {
            case 1:
                condiments.push_back(17);
                condiments.push_back(19);
                condiments.push_back(23);
                break;
            case 2:
                condiments.push_back(19);
                condiments.push_back(23);
                condiments.push_back(29);
                break;
            case 3:
                condiments.push_back(23);
                condiments.push_back(29);
                condiments.push_back(31);
                break;
            default:
                cout << "no salt, no taste" << endl;
                break;
        }
        return condiments;
    }

};

class User {
public:
    string username;
    string email;
    string user_level;
    string user_group;

protected:
    /// @brief Salt, pepper and chilli are prime numbers, the seeds for the key,
    int salt;
    int pepper;
    int chilli;
    int security_question;
    string security_answer;
    std::pair<std::pair<int, int>, std::pair<int, int>> keys;
    std::vector<int> encrypted_password;

public:
    User() {
        this->username = "N/A";
        this->email = "N/A";
        this->user_level = "user";
        this->user_group = "user";
        this->salt = 0;
        this->pepper = 0;
        this->chilli = 0;
        this->security_question = 0;
        this->security_answer = "N/A";
        this->encrypted_password = {0};
        this->keys = std::make_pair(std::make_pair(0, 0), std::make_pair(0, 0));
    }

    static bool usernameValidity(const std::string &username) {
        std::regex pattern("^[a-zA-Z0-9]+$");
        if (!std::regex_match(username, pattern)) {
            std::cout << "Invalid username. Only numbers and letters are allowed." << std::endl;
        }
        return std::regex_match(username, pattern);
    }

    /// @brief Input validation functions, will be called in the enter_<user_data>() functions.
    ///        If all requirements are met, the setters will be called.
    static bool emailValidity(const std::string &email_address) {
        // define regex
        const std::regex pattern(("[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}"));
        // try to match the string with the regex
        return std::regex_match(email_address, pattern);
    }

    static bool password_validity(const std::string &password) {
        // define regex
        const std::regex pattern("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)[a-zA-Z\\d]{8,}$");
        // try to match the string with the regex
        return std::regex_match(password, pattern);
    }

private:
    /// setter functions
    /// @brief The setters are private because only an user should be able to modify his own data.
    ///        Otherwise, an admin could abusively modify the data of users.
    void set_username(string new_username) {
        this->username = std::move(new_username);
    }

    void set_email(string new_email) {
        this->email = std::move(new_email);
    }

    void set_security_answer(string new_security_answer) {
        this->security_answer = std::move(new_security_answer);
    }

    void set_security_question(int new_security_question) {
        this->security_question = new_security_question;
    }

    void set_encrypted_password(std::vector<int> new_encrypted_password) {
        this->encrypted_password = std::move(new_encrypted_password);
    }

    //@brief The getters are public because this data should be accessible to admin as well.
public:
    [[nodiscard]] string get_username() const {
        return this->username;
    }

    [[nodiscard]] string get_email() const {
        return this->email;
    }

    [[nodiscard]] string get_user_level() const {
        return this->user_level;
    }

    [[nodiscard]] string get_user_group() const {
        return this->user_group;
    }

    [[nodiscard]] int get_salt() const {
        return this->salt;
    }

    [[nodiscard]] int get_pepper() const {
        return this->pepper;
    }

    [[nodiscard]] int get_chilli() const {
        return this->chilli;
    }

    [[nodiscard]] int get_security_question() const {
        return this->security_question;
    }

    [[nodiscard]] string get_security_answer() const {
        return this->security_answer;
    }

    [[nodiscard]] std::vector<int> get_encrypted_password() const {
        return this->encrypted_password;
    }

    ///Keys will only be generated when needed, based on the security question index.
    ///So there is no need for storing them or accessing them, as storing them would be a security risk.

    /// Functions to enter user data which will be stored in the database via the setter functions.
    static string enter_username() {
        string temp_username;
        cout << "Only letters and numbers are allowed in the username, no spaces or special characters."
             << "\n"
             << "Enter username: ";
        cin >> temp_username;

        while (true) {
            try {
                if (usernameValidity(temp_username) &&
                    !loginUtils::isUsernameUsed(temp_username, loginUtils::readUserData("user_db.csv"))) {
                    std::cout << "...Username is valid" << std::endl;
                    break;
                }
            }
            catch (const std::invalid_argument &e) {
                std::cerr << e.what() << '\n';
                cout << "Enter username: ";
                cin >> temp_username;
            }
            break;
        }

        return temp_username;
    }

    static string enter_email() {
        string temp_email;
        cout << "Enter email: ";
        cin >> temp_email;

        while (true) {
            try {
                if (emailValidity(temp_email) &&
                    !loginUtils::isEmailUsed(temp_email, loginUtils::readUserData("user_db.csv"))) {
                    std::cout << "...Email is valid" << std::endl;
                    break;
                }
            }
            catch (const std::invalid_argument &e) {
                std::cerr << e.what() << '\n';
                cout << "Enter email: ";
                cin >> temp_email;
            }
            break;
        }

        return temp_email;
    }

    static int enterSecurityQuestion() {
        int choice;

        cout << "1. Who was in Paris?" << endl;
        cout << "2. Shaorma Wow or Shobo?" << endl;
        cout << "3. Golf, Passat or Logan?" << endl;

        cout << "Enter your choice: ";
        cin >> choice;

        if (choice < 1 || choice > 3)
            throw std::invalid_argument("Invalid choice");
        else
            return choice;
    }

    static string enterSecurityAnswer() {
        string temp_security_answer;
        cout << "Enter security answer: ";
        cin >> temp_security_answer;

        return temp_security_answer;
    }

    static string enterPassword() {
        string temp_password;
        string repeated_password;
        cout << "Enter password: ";
        cin >> temp_password;

        while (true) {
            try {
                password_validity(temp_password);
                if (password_validity(temp_password)) {
                    std::cout << "\nPassword is valid\n" << std::endl;
                }

                while (true) {
                    cout << "Repeat password: ";
                    cin >> repeated_password;
                    try {
                        if (repeated_password == temp_password) {
                            return temp_password;
                        } else {
                            throw std::invalid_argument("Passwords do not match");
                        }
                    } catch (const std::invalid_argument &e) {
                        std::cerr << e.what() << '\n';
                    }
                }
                // If the password is valid and the repeated password is identical, the loop breaks
            }
            catch (const std::invalid_argument &e) {
                std::cerr << e.what() << '\n';
            }
        }
    }

    void set_keys(std::pair<std::pair<int, int>, std::pair<int, int>> new_keys) {
        this->keys = new_keys;
    }

    /// @brief Salt, pepper and chilli are prime numbers, the seeds for the key,

    void salt_it(int new_salt) {
        this->salt = new_salt;
    }

    void pepper_it(int new_pepper) {
        this->pepper = new_pepper;
    }

    void chilli_it(int new_chilli) {
        this->chilli = new_chilli;
    }

    /// @brief Salt, pepper and chilli are prime numbers, the seeds for the key,
    ///        and their choice is based on the security question index.
    void condiment(int chosen_security_question) {
        switch (chosen_security_question) {
            case 1:
                this->salt_it(17);
                this->pepper_it(19);
                this->chilli_it(23);
                break;
            case 2:
                this->salt_it(19);
                this->pepper_it(23);
                this->chilli_it(29);
                break;
            case 3:
                this->salt_it(23);
                this->pepper_it(29);
                this->chilli_it(31);
                break;
            default:
                cout << "no salt, no taste" << endl;
                break;
        }
    }

    void setUserDetails() {
        this->set_username(User::enter_username());
        this->set_email(User::enter_email());
        this->set_security_question(User::enterSecurityQuestion());
        this->set_security_answer(User::enterSecurityAnswer());
        this->condiment(this->get_security_question());
        this->set_keys(Encryptor::generateKeyPair(this->get_salt(), this->get_pepper(), this->get_chilli()));
        this->set_encrypted_password(Encryptor::encryptMessage(User::enterPassword(), this->keys.first));
    }

    /* void printUserDetails() const {
        cout << "Username: " << this->get_username() << endl;
        cout << "Email: " << this->get_email() << endl;
        cout << "User level: " << this->get_user_level() << endl;
        cout << "User group: " << this->get_user_group() << endl;
        cout << "Salt: " << this->get_salt() << endl;
        cout << "Pepper: " << this->get_pepper() << endl;
        cout << "Chilli: " << this->get_chilli() << endl;
        cout << "Security question: " << this->get_security_question() << endl;
        cout << "Security answer: " << this->get_security_answer() << endl;
        cout << "Encrypted password: ";

        for (long long unsigned int i = 0; i < this->get_encrypted_password().size(); i++) {
            cout << this->get_encrypted_password()[i];
        }

        cout << endl;
    }
    */

    static void writeUser(const User &user) {
        ofstream user_file;
        user_file.open("user_db.csv", ios::app);

        user_file << user.username << ","
                  << user.email << ","
                  << user.user_level << ","
                  << user.user_group << ","
                  << user.security_question << ","
                  << user.security_answer << ",";

        for (int i: user.encrypted_password) {
            user_file << i << " ";
        }

        user_file << ",";
        user_file << endl;
    }
};

class Admin : public User {
public:
    string user_level = "admin";
    string user_group = "admin";

    /// @brief Creates a "fresh" admin account with default values.
    ///       The password is "admin" and the security question is 1  with the answer "N/A".
    ///       Is meant to be called by root only if wanted to create a new admin account.
    ///       After that, the freshly created admin will login and update his credentials.
    Admin() {
        this->username = "admin";
        this->email = "N/A";
        this->user_level = "admin";
        this->user_group = "admin";
        this->salt = 0;
        this->pepper = 0;
        this->chilli = 0;
        this->security_question = 1;
        this->security_answer = "N/A";
        ///default password generation for a fresh admin account
        this->keys = Encryptor::generateKeyPair(17, 19, 23);
        this->encrypted_password = Encryptor::encryptMessage("admin", this->keys.first);
    }

    ///writeUser override for writing admin data to the file
    static void writeUser(const Admin &admin) {
        ofstream user_file;
        user_file.open("user_db.csv", ios::app);

        user_file << admin.username << ","
                  << admin.email << ","
                  << admin.user_level << ","
                  << admin.user_group << ","
                  << admin.security_question << ","
                  << admin.security_answer << ",";

        for (int i: admin.encrypted_password) {
            user_file << i << " ";
        }

        user_file << ",";
        user_file << endl;
    }

    static void register_fresh_admin(){
        Admin freshAdmin = Admin();
        Admin::writeUser(freshAdmin);
    }
};
