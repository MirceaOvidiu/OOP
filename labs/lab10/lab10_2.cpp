#include <iostream>

///Facade

using namespace std;

class Processor {
public:
    void freeze() { std::cout << "Processor freeze\n"; }
    void jump(long position) { std::cout << "Jump to position " << position << "\n"; }
    void execute() { std::cout << "Processor execute\n"; }
};

class Memory {
public:
    void load(long position, char* data) {
        std::cout << "Load from position " << position << " data: " << data << "\n";
    }
};

class HardDrive {
public:
    char* read(long lba, int size) {
        return new char('d'); // doar pt exemplu
    }
};

class Computer {
private:
    Processor* processor;
    Memory* memory;
    HardDrive* hardDrive;
public:
    Computer() {
        processor = new Processor();
        memory = new Memory();
        hardDrive = new HardDrive();
    }
    void startComputer() {
        processor->freeze();
        memory->load(1000, hardDrive->read(1000, 200));
        processor->jump(1000);
        processor->execute();
    }
};

int main() {
    Computer* computer = new Computer();
    computer->startComputer();
    delete computer;
    return 0;
}
/*pros and cons
 pros:
    - se aplica principiul Demeter, fiecare obiect/functie interactioneaza
    strict cu ce are nevoie si "stie" doar ce il priveste in mod direct
    - nr minim al dependentelor
    - principiu bun pentru secure design
    - simplitate

cons:
 - layer extra intre client si subsistem, poate scadea
 performanta
 - inflexibil la scalare
*/