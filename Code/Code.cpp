#include <iostream>
#include <vector>
using namespace std;


class AntBehavior {
public:
    virtual void performActions(int& workers, int& warriors, int& ticks) = 0;
    virtual ~AntBehavior() {}
};

class KillerAnts : public AntBehavior {
public:
    void performActions(int& workers, int& warriors, int& ticks) override {
        ticks += 1;
        warriors += 1;
    }
};

class PansyAnts : public AntBehavior {
public:
    void performActions(int& workers, int& warriors, int& ticks) override {
        ticks += 1;
        workers += 1;
    }
};


class AntFarm {
private:
    char species[50];
    int workers;
    int warriors;
    int restingRooms;
    int ticksAlive;
    AntBehavior* behavior; 

public:
    AntFarm(const char* species, int workers, int warriors, int restingRooms)
        : workers(workers), warriors(warriors), restingRooms(restingRooms), ticksAlive(0), behavior(nullptr) {
        int i;
        for (i = 0; species[i] != '\0' && i < 49; i++) {
            this->species[i] = species[i];
        }
        this->species[i] = '\0';

        if (compareSpecies("Killer")) {
            behavior = new KillerAnts();
        } else if (compareSpecies("Pansy")) {
            behavior = new PansyAnts();
        }
    }

    ~AntFarm() {
        delete behavior; 
    }

    bool compareSpecies(const char* other) const {
        for (int i = 0; i < 50; i++) {
            if (species[i] != other[i])
                return false;
            if (species[i] == '\0' && other[i] == '\0')
                return true;
        }
        return false;
    }

    void performTickActions() {
        if (behavior) {
            behavior->performActions(workers, warriors, ticksAlive);
        }
        cout << "AntFarm of species " << species << " is performing actions.\n";
        cout << "Workers: " << workers << ", Warriors: " << warriors << ", Resting Rooms: " << restingRooms << "\n";
    }

    void getSummary() const {
        cout << "Species: " << species << "\n";
        cout << "Workers: " << workers << "\n";
        cout << "Warriors: " << warriors << "\n";
        cout << "Resting Rooms: " << restingRooms << "\n";
        cout << "Ticks alive: " << ticksAlive << "\n";
    }
};


class Meadow {
private:
    static Meadow* instance;
    vector<AntFarm*> farms; 
    Meadow() {} 

public:
    static Meadow* getInstance() {
        if (!instance)
            instance = new Meadow();
        return instance;
    }

    void addFarm(AntFarm* farm) {
        farms.push_back(farm);
    }

    void simulateTick() {
        cout << "Simulating a tick in the meadow:\n";
        for (AntFarm* farm : farms) {
            farm->performTickActions();
        }
    }

    void getFarmSummary(int farmIndex) {
        if (farmIndex < 1 || farmIndex > farms.size()) {
            cout << "Invalid farm ID.\n";
        } else {
            farms[farmIndex - 1]->getSummary();
        }
    }

    ~Meadow() {
        for (AntFarm* farm : farms)
            delete farm; 
    }
};

Meadow* Meadow::instance = nullptr;

int main() {
    Meadow* meadow = Meadow::getInstance();
    char command[100];

    cout << "Welcome to the Ant Farm Simulation!\n";

    while (true) {
        cout << "Enter command: ";
        cin.getline(command, sizeof(command));

        if (command[0] == 's' && command[1] == 'p' && command[2] == 'a' && command[3] == 'w' && command[4] == 'n') {
            char species[50];
            sscanf(command + 6, "%s", species);
            AntFarm* farm = new AntFarm(species, 10, 5, 2);
            meadow->addFarm(farm);
            cout << "Spawned " << species << " AntFarm.\n";
        } else if (command[0] == 't' && command[1] == 'i' && command[2] == 'c' && command[3] == 'k') {
            meadow->simulateTick();
        } else if (command[0] == 's' && command[1] == 'u' && command[2] == 'm' && command[3] == 'm' && command[4] == 'a' && command[5] == 'r' && command[6] == 'y') {
            int farmIndex;
            sscanf(command + 8, "%d", &farmIndex);
            meadow->getFarmSummary(farmIndex);
        } else if (command[0] == 'e' && command[1] == 'x' && command[2] == 'i' && command[3] == 't') {
            break;
        } else {
            cout << "Unknown command.\n";
        }
    }

    delete meadow; 

    return 0;
}
