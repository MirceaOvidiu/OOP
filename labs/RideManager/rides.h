//
// Created by Mircea on 12/8/2023.
//

#ifndef RIDEMANAGER_RIDES_H
#define RIDEMANAGER_RIDES_H

#include <string>
#include <utility>
#include <iomanip>
#include <chrono>

using namespace std;

class Ride {
public:
    string rideID;
    string startLocation;
    string endLocation;
    string date;
    string time;
    unsigned int availableSeats;
    unsigned int totalSeats;

    Ride() {
        rideID = "";
        startLocation = "";
        endLocation = "";
        date = "";
        time = "";
        availableSeats = 0;
        totalSeats = 0;
    }


    ///ride data validation functions
    static std::string getTodayDate() {
        // Get the current time
        auto currentTime = std::chrono::system_clock::now();
        std::time_t currentDate = std::chrono::system_clock::to_time_t(currentTime);

        // Convert the time to a tm struct
        std::tm *tmDate = std::localtime(&currentDate);

        // Format the date into "DD-MM-YY" string
        std::ostringstream oss;
        oss << std::setfill('0') << std::setw(2) << tmDate->tm_mday << "-"
            << std::setfill('0') << std::setw(2) << tmDate->tm_mon + 1 << "-"
            << std::setfill('0') << std::setw(2) << tmDate->tm_year + 1900;

        return oss.str();
    }

    static bool isDateInPast(const std::string& date) {
        int day, month, year;

        if (sscanf(date.c_str(), "%d-%d-%d", &day, &month, &year) != 3) {
            std::cerr << "Failed to parse the date." << std::endl;
            return false;
        }

        // Adjust month and year to be zero-based and years since 1900
        month -= 1;
        year -= 1900;

        // Set other time components to zero (hours, minutes, seconds)
        int hour = 0, min = 0, sec = 0;

        // Get the current time
        auto currentTime = std::chrono::system_clock::now();

        // Convert parsed date to time_point
        std::tm tmDate = {sec, min, hour, day, month, year, 0, 0, 0};
        auto enteredDate = std::chrono::system_clock::from_time_t(std::mktime(&tmDate));

        // Compare the dates
        return enteredDate < currentTime;
    }


    static bool rideIDValidity(const std::string &rideID) {
        std::regex rideIDRegex("^Ride(\\d+)$");
        return std::regex_match(rideID, rideIDRegex);
    }

    static bool rideIDExistence(const std::string &rideID) {
        ifstream rideFile;
        rideFile.open("rides_db.csv");
        string line;
        while (getline(rideFile, line)) {
            if (line.find(rideID) != string::npos) {
                return true;
            }
        }
        return false;
    }

    static bool locationValidity(const std::string &location) {
        std::regex locationRegex("^[a-zA-Z]+$");
        return std::regex_match(location, locationRegex);
    }

    static bool dateFormatValidity(const std::string &date) {
        std::regex dateRegex("^(0[1-9]|[12][0-9]|3[01])[-](0[1-9]|1[012])[-](19|20)\\d\\d$");
        return std::regex_match(date, dateRegex);
    }

    static bool timeFormatValidity(const std::string &time) {
        std::regex timeRegex("^(0[0-9]|1[0-9]|2[0-3]):[0-5][0-9]$");
        return std::regex_match(time, timeRegex);
    }

    void setStartLocation(string newStartLocation) {
        this->startLocation = std::move(newStartLocation);
    }

    void setEndLocation(string newEndLocation) {
        this->endLocation = std::move(newEndLocation);
    }

    void setDate(string newDate) {
        this->date = std::move(newDate);
    }

    void setTime(string newTime) {
        this->time = std::move(newTime);
    }

    void setAvailableSeats(unsigned int newAvailableSeats) {
        this->availableSeats = newAvailableSeats;
    }

    void setTotalSeats(unsigned int newTotalSeats) {
        this->totalSeats = newTotalSeats;
    }

    void setRideID(string newRideID) {
        this->rideID = std::move(newRideID);
    }

    ///getters
    [[nodiscard]] string getRideID() const {
        return this->rideID;
    }

    [[nodiscard]] string getStartLocation() const {
        return this->startLocation;
    }

    [[nodiscard]] string getEndLocation() const {
        return this->endLocation;
    }

    [[nodiscard]] string getDate() const {
        return this->date;
    }

    [[nodiscard]] string getTime() const {
        return this->time;
    }

    [[nodiscard]] unsigned int getAvailableSeats() const {
        return this->availableSeats;
    }

    [[nodiscard]] unsigned int getTotalSeats() const {
        return this->totalSeats;
    }

    ///ride data entry functions
    static string enterRideID() {
        string rideID;
        cout << "Enter ride ID as: (Ride{number}): ";
        cin >> rideID;

        while (true) {
            try {
                if (rideIDValidity(rideID)) {
                    std::cout << "Ride ID OK" << std::endl;
                    if(rideIDExistence(rideID)){
                        throw (std::invalid_argument("Ride ID already exists"));
                    }else{
                        cout << "Ride ID OK" << endl;
                        return rideID;
                    }
                }
            }
            catch (const std::invalid_argument &e) {
                std::cerr << e.what() << '\n';
                throw (std::invalid_argument("Invalid ride ID"));
            }
        }
    }

    static string enterStartLocation() {
        string newStartLocation;
        while (true) {
            try {
                cout << "Enter start location: ";
                cin >> newStartLocation;
                if (locationValidity(newStartLocation)) {
                    std::cout << "Start location OK" << std::endl;
                    return newStartLocation;
                }
            }
            catch (const std::invalid_argument &e) {
                std::cerr << e.what() << '\n';
                throw (std::invalid_argument("Invalid start location"));
            }
        }
    }

    static string enterEndLocation() {
        string newEndLocation;
        while (true) {
            try {
                cout << "Enter end location: ";
                cin >> newEndLocation;
                if (locationValidity(newEndLocation)) {
                    std::cout << "End location OK" << std::endl;
                    return newEndLocation;
                }
            }
            catch (const std::invalid_argument &e) {
                std::cerr << e.what() << '\n';
                throw (std::invalid_argument("Invalid end location"));
            }
        }
    }

    static string enterDate() {
        string newDate;
        while (true) {
            try {
                cout << "Enter date as DD-MM-YYYY: ";
                cin >> newDate;
                if (dateFormatValidity(newDate)) {
                    std::cout << "Ride date OK" << std::endl;
                    if (!isDateInPast(newDate)) {
                        std::cout << "Date OK" << std::endl;
                        return newDate;
                    }
                    if(isDateInPast(newDate)){
                        throw(std::invalid_argument("Date is in the past"));
                    }
                }
            } catch (const std::invalid_argument &e) {
                std::cerr << e.what() << '\n';
                throw (std::invalid_argument("Date was not set"));
            }
        }
    }

    static string enterTime() {
        string newTime;

        while (true) {
            try {
                cout << "Enter time as HH:MM: ";
                cin >> newTime;
                if (timeFormatValidity(newTime)) {
                    std::cout << "Time OK" << std::endl;
                    return newTime;
                }
            }
            catch (const std::invalid_argument &e) {
                std::cerr << e.what() << '\n';
                throw (std::invalid_argument("Invalid time"));
            }
        }
    }

    static unsigned int enterTotalSeats() {
        unsigned int newTotalSeats;
        while (true) {
            try {
                cout << "Enter total seats: ";
                cin >> newTotalSeats;
                if (newTotalSeats > 0) {
                    std::cout << "Total seats OK" << std::endl;
                    return newTotalSeats;
                }
            }
            catch (const std::invalid_argument &e) {
                std::cerr << e.what() << '\n';
                throw (std::invalid_argument("Invalid total seats"));
            }
        }
    }

    void enterRideDetails() {
        this->setRideID(enterRideID());
        this->setStartLocation(enterStartLocation());
        this->setEndLocation(enterEndLocation());
        this->setDate(enterDate());
        this->setTime(enterTime());
        this->setTotalSeats(enterTotalSeats());
        this->setAvailableSeats(this->getTotalSeats());
    }

    static std::vector<Ride> getRides(const std::string& filename) {
        std::vector<Ride> rides;
        std::ifstream inputFile(filename);

        if (!inputFile.is_open()) {
            std::cerr << "Error opening file: " << filename << std::endl;
            return rides;
        }

        std::string line;
        while (std::getline(inputFile, line)) {
            std::istringstream iss(line);
            Ride ride;

            // Read each token separated by commas
            std::getline(iss, ride.rideID, ',');
            std::getline(iss, ride.startLocation, ',');
            std::getline(iss, ride.endLocation, ',');
            std::getline(iss, ride.date, ',');
            std::getline(iss, ride.time, ',');
            iss >> ride.availableSeats;
            iss.ignore(); // Ignore the comma
            iss >> ride.totalSeats;
            rides.push_back(ride);
        }

        inputFile.close();
        return rides;
    }

    static void printRideDetails(unsigned int RideIndex, std::vector<Ride> ridesList) {
        cout << ridesList[RideIndex].getRideID() << "  "
            << ridesList[RideIndex].getStartLocation() << "  "
            << ridesList[RideIndex].getEndLocation() << "  "
            << ridesList[RideIndex].getDate() << "  "
            << ridesList[RideIndex].getTime() << "  "
            << ridesList[RideIndex].getAvailableSeats() << "  "
            << ridesList[RideIndex].getTotalSeats() << endl;
    }

    static void printRides(const std::vector<Ride>& rides)
    {
        ///3 is the first ride index
        for (int i = 3; i < rides.size(); ++i) {
            printRideDetails(i,rides);
        }
    }

    static std::vector<Ride> searchRides(const std::vector<Ride>& rides) {
        std::vector<Ride> filteredRides;
        std::string startLocation = enterStartLocation();
        std::string endLocation = enterEndLocation();

        for (const auto &ride: rides) {
            if (ride.startLocation == startLocation && ride.endLocation == endLocation) {
                filteredRides.push_back(ride);
            }
        }

        if (filteredRides.empty()) {
            std::cout << "No such rides found" << std::endl;
            return filteredRides;
        } else {
            cout << "Found rides matching your search: ";
            for (const auto &ride: filteredRides) {
                std::cout << ride.rideID << " ";
            }
            cout << endl;
            return filteredRides;
        }
    }

    static void writeRide(Ride &ride) {
        ofstream rideFile;
        rideFile.open("rides_db.csv", ios::app);
        rideFile << ride.getRideID() << "," << ride.getStartLocation() << "," << ride.getEndLocation() << ","
                 << ride.getDate() << "," << ride.getTime() << "," << ride.getAvailableSeats() << ","
                 << ride.getTotalSeats() << endl;
        rideFile.close();
    }

    static void registerRide() {
        Ride new_ride = Ride();
        new_ride.enterRideDetails();
        Ride::writeRide(new_ride);
        /// new_ride.print_ride_details();
        std::cout << "Ride created successfully \n";
    }

    static string chooseRide(){
        string rideID;
        cout << "Enter ride ID as: (Ride{number}): ";
        cin >> rideID;

        while (true) {
            try {
                if (rideIDValidity(rideID)) {
                    std::cout << "Ride ID OK" << std::endl;
                    if(rideIDExistence(rideID)){
                        cout << "Ride ID OK" << endl;
                        return rideID;
                    }else{
                        throw (std::invalid_argument("Ride ID does not exist"));
                    }
                }
            }
            catch (const std::invalid_argument &e) {
                std::cerr << e.what() << '\n';
                throw (std::invalid_argument("Invalid ride ID"));
            }
        }
    }

    static Ride copyRideByID(const string &rideID, const std::vector<Ride>& rides) {
        for (const auto &ride: rides) {
            if (ride.rideID == rideID) {
                return ride;
            }
        }
        throw (std::invalid_argument("Ride ID does not exist"));
    }

    static void deleteRide(const string &rideID) {
        ifstream rideFile;
        ofstream tempFile;
        rideFile.open("rides_db.csv");
        tempFile.open("temp.csv");
        string line;
        while (getline(rideFile, line)) {
            if (line.find(rideID) == string::npos) {
                tempFile << line << endl;
            }
        }
        rideFile.close();
        tempFile.close();
        remove("rides_db.csv");
        rename("temp.csv", "rides_db.csv");
    }

    static void bookRide(const string &rideID) {
        std::vector<Ride> rides = getRides("rides_db.csv");
        Ride copyRide = copyRideByID(rideID, rides);
        if (copyRide.availableSeats > 0) {
            copyRide.availableSeats = copyRide.availableSeats - 1;
            deleteRide(rideID);
            writeRide(copyRide);
            cout << "Ride booked successfully" << endl;
        } else {
            cout << "No available seats" << endl;
        }
    }

    static void cancelRide(const string &rideID) {
        std::vector<Ride> rides = getRides("rides_db.csv");
        Ride copyRide = copyRideByID(rideID, rides);
        if (copyRide.availableSeats < copyRide.totalSeats) {
            copyRide.availableSeats = copyRide.availableSeats + 1;
            deleteRide(rideID);
            writeRide(copyRide);
            cout << "Ride cancelled successfully" << endl;
        } else {
            cout << "No seats to cancel" << endl;
        }
    }
};

#endif //RIDEMANAGER_RIDES_H
