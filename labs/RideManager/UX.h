#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <regex>
#include <fstream>
#include <sstream>
#include "users.h"
#include "rides.h"

using namespace std;

class UX {
public:
    static std::vector<int> stringToVector(const std::string &input) {
        std::vector<int> result;
        std::istringstream iss(input);

        int encrypted_password_digit;
        while (iss >> encrypted_password_digit) {
            result.push_back(encrypted_password_digit);

            // Check for the space
            if (iss.peek() == ' ') {
                iss.ignore();  // Ignore the space
            }
        }

        return result;
    }

    static string login() {
        ///reading user data from file
        std::vector<loginUtils::USER> user_file = loginUtils::readUserData("user_db.csv");

        ///login phase utils
        string attempted_username, securityQuestionAnswer, attempted_password, user_decrypted_password;
        unsigned int user_index;
        string user_security_question;
        string user_security_answer;
        std::vector<int> user_encrypted_password;
        std::vector<int> user_condiments;
        string stringEncryptedPassword;
        std::pair<std::pair<int, int>, std::pair<int, int>> keyPair = std::make_pair(std::make_pair(0, 0),
                                                                                     std::make_pair(0, 0));

        ///start login phase
        cout << "Enter your username: ";
        cin >> attempted_username;

        ///used for search optimization
        user_index = loginUtils::getUserIndex(attempted_username, user_file);

        if (loginUtils::isUsernameUsed(attempted_username, user_file)) {
            cout << "User found" << endl;
            cout << "Enter password: ";
            cin >> attempted_password;
        } else {
            cout << "User not found" << endl;
            throw std::invalid_argument("login: user not found");
        }

        ///retrieving hash salts
        user_condiments = loginUtils::assignsUserCondiments(
                stoi(loginUtils::getUserSecurityQuestion(user_index, user_file)));

        ///regenerating key pair
        keyPair = Encryptor::generateKeyPair(user_condiments[0], user_condiments[1], user_condiments[2]);
        user_decrypted_password = Encryptor::decryptMessage(
                stringToVector(loginUtils::getUserEncryptedPassword(user_index, user_file)), keyPair.second);

        ///checking if the decrypted password is the same as the one entered
        if (user_decrypted_password == attempted_password) {
            cout << "Welcome back " << attempted_username << "!" << endl;
        } else {
            cout << "Login failed..." << endl;
            throw std::invalid_argument("login: wrong password");
        }

        return user_file[user_index].user_level;
    }

    static void register_user() {
        User new_user = User();
        new_user.setUserDetails();
        User::writeUser(new_user);
        /// new_user.print_user_details();
        std::cout << "User created successfully \n";
    }

    static void userMenu()
    {
        while (true)
        {
            unsigned int choice;
            cout << "1. Search rides" << endl;
            cout << "2. Book ride" << endl;
            cout << "3. Cancel ride" << endl;
            cout << "4. Exit" << endl;
            cin >> choice;

            if (choice == 4)
            {
                exit(0);
            }
            else
            {
                switch (choice)
                {
                case 1:
                    Ride::printRides(Ride::searchRides(Ride::getRides("rides_db.csv")));
                    break;
                case 2:
                    cout << "Book ride" << endl;
                    Ride::bookRide(Ride::chooseRide());
                    break;
                case 3:
                    cout << "Cancel ride" << endl;
                    Ride::cancelRide(Ride::chooseRide());
                    break;
                default:
                    throw(std::invalid_argument("userMenu: switch defaulted"));
                }
            }
        }
    };

    static void adminMenu() {
        while (true) {
            unsigned int choice;
            cout << "1. View rides" << endl;
            cout << "2. Add new ride" << endl;
            cout << "3. Delete ride" << endl;
            cout << "4. Create fresh admin account" << endl;
            cout << "5. Exit" << endl;
            cin >> choice;

            if (choice == 5) {
                exit(0);
            } else {
                switch (choice) {
                    case 1:
                        Ride::printRides(Ride::getRides("rides_db.csv"));
                        break;
                    case 2:
                        cout << "Add new ride" << endl;
                        Ride::registerRide();
                        break;
                    case 3:
                        cout << "Delete ride" << endl;
                        Ride::deleteRide(Ride::chooseRide());
                        break;
                    case 4:
                        cout << "Create fresh admin account" << endl;
                        Admin::register_fresh_admin();
                        break;
                    default:
                        throw(std::invalid_argument("adminMenu: switch defaulted"));
                }
            }
        }
    };

    static void startSession(const string &userLevel) {
        if (userLevel == "admin") {
            ///admin session
            adminMenu();
        } else if (userLevel == "user") {
            userMenu();
        }
    }

    static void startMenu() {
        std::cout << "Today is " << Ride::getTodayDate() << "\n" << std::endl;
        std::cout << "Session started... \n" << std::endl;
        while (true) {
            int choice;
            cout << "1. Login as existent user" << endl;
            cout << "2. Create user profile" << endl;
            cout << "3. Exit" << endl;
            cin >> choice;

            switch (choice) {
                case 1:
                    startSession(login());
                    break;
                case 2:
                    register_user();
                    break;
                case 3:
                    exit(0);
                default:
                    cout << "startMenu: switch defaulted" << endl;
                    break;
            }

            if (choice == 3) {
                break;
            }
        }
    }
};