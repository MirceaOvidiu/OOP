#include <iostream>
#include <string>
#include <vector>
#include <fstream>

class Singleton {
private:
    static Singleton* instance;
    
    // Private constructor to prevent instantiation
    Singleton() {}
    
public:
    static Singleton* getInstance() {
        if (instance == nullptr) {
            instance = new Singleton();
            std::cout << "error logging session started..." << std::endl << " (no whitespaces, only underscores)" << std::endl;
        }
        return instance;
    }

    void consoleLog() {
        std::string message;
        std::cout << "log error:" << std::endl;
        std::cin >> message;
        
        std::ofstream logFile;
        logFile.open("log.txt", std::ios::app);
        logFile << message << std::endl;
    }
};

// Initialize the static instance to nullptr
Singleton* Singleton::instance = nullptr;

int main() {
    Singleton::getInstance()->consoleLog();
    Singleton::getInstance()->consoleLog();
    Singleton::getInstance()->consoleLog();
    
    return 0;
}

/*Pros and cons:
Pro: 
-bun pentru actiuni secventiale, ce trebuiesc facute una dupa alta, NU simultan - motiv pt care am exemplificat pe un logger, care scrie secvential in fisiere 
-usor de folosit
Contra:
-greu de scalat
-poate deveni riscant in cazul in care exista multe dependente
-in anumite cazuri poate creste exponential complexitatea

*/
