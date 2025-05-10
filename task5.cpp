#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

// Base class for all users (Civilian or Manager)
class User {
protected:
    string name;
    string role;
public:
    virtual void showDetails() = 0; // Pure virtual function
    virtual ~User() = default; // Virtual destructor
};

// Manager class (inherits User)
class Manager : public User {
private:
    string password = "admin123"; // Default password
public:
    Manager(string n) {
        name = n;
        role = "Manager";
    }

    bool verifyPassword() {
        string enteredPassword;
        cout << "Enter password: ";
        cin >> enteredPassword;
        if (enteredPassword == this->password) {
            cout << "Password verified!" << endl;
            return true;
        } else {
            cout << "Incorrect password!" << endl;
            return false;
        }
    }

    void showDetails() override {
        cout << "Welcome, Manager " << name << "!" << endl;
    }

    void viewCityStatus() const {
        cout << "\nDetailed City Status:\n";
        cout << "Eco-Points: 1200" << endl;
        cout << "Energy Usage: 15,000 kWh/day" << endl;
        cout << "Water Usage: 30,000 liters/day" << endl;
        cout << "Total Pollution Level: Low" << endl;
        cout << "Green Initiatives: 80% recycling, 60% solar power" << endl;
    }

    void viewBuildingStatus() const {
        cout << "\nBuilding Status:\n";
        cout << "Building: Office Tower" << endl;
        cout << "Status: Fully Operational" << endl;
        cout << "Energy Usage: 2500 kWh/day" << endl;
        cout << "Water Usage: 500 liters/day" << endl;
    }

    void upgradeBuilding(const string& building) {
        cout << "\nUpgrading " << building << "..." << endl;
        cout << "Energy Efficiency improved by 10%" << endl;
    }

    // Implement the addResource function
    void addResource(const string& resource, double amount) {
        cout << "\nAdding " << amount << " units of " << resource << "..." << endl;
        cout << resource << " added successfully!" << endl;
    }

    void removeResource(const string& resource, double amount) {
        cout << "\nRemoving " << amount << " units of " << resource << "..." << endl;
        cout << resource << " removed successfully!" << endl;
    }

    void viewPollutionLevels() const {
        cout << "\nPollution Levels:\n";
        cout << "Air Quality: Good" << endl;
        cout << "Water Quality: Excellent" << endl;
        cout << "Noise Levels: Low" << endl;
    }

    // File Handling Operations
    void saveDataToFile(const string& filename, const string& data) {
        ofstream file(filename, ios::app);
        if (!file){
        cerr << "file not found";
        return;
        }
        else if (file.is_open()) {
            file << data << endl;
            file.close();
            cout << "Data saved to " << filename << " successfully!" << endl;
        } else {
            cout << "Failed to open file " << filename << endl;
        }
    }

    void updateDataInFile(const string& filename, const string& oldData, const string& newData) {
        ifstream file(filename);
        stringstream buffer;
        string line;
        bool found = false;

        while (getline(file, line)) {
            if (line == oldData) {
                buffer << newData << endl;
                found = true;
            } else {
                buffer << line << endl;
            }
        }

        file.close();

        if (found) {
            ofstream outFile(filename);
            outFile << buffer.str();
            outFile.close();
            cout << "Data updated successfully in " << filename << endl;
        } else {
            cout << "Data not found in " << filename << endl;
        }
    }

    void deleteDataFromFile(const string& filename, const string& data) {
        ifstream file(filename);
        stringstream buffer;
        string line;
        bool found = false;

        while (getline(file, line)) {
            if (line != data) {
                buffer << line << endl;
            } else {
                found = true;
            }
        }

        file.close();

        if (found) {
            ofstream outFile(filename);
            outFile << buffer.str();
            outFile.close();
            cout << "Data deleted successfully from " << filename << endl;
        } else {
            cout << "Data not found in " << filename << endl;
        }
    }
};

// Civilian class (inherits User)
class Civilian : public User {
public:
    Civilian(string n) {
        name = n;
        role = "Civilian";
    }

    void showDetails() override {
        cout << "Welcome, Civilian " << name << "!" << endl;
    }

    void viewCityStatus() const {
        cout << "\nCity Status:\n";
        cout << "Current Eco-Score: 500 points" << endl;
        cout << "Current Pollution Level: Moderate" << endl;
        cout << "Energy Efficiency: 80%" << endl;
    }

    void purchaseApartment() const {
        cout << "\nPurchasing Apartment...\n";
        cout << "Apartment purchased successfully!" << endl;
    }

    void useFacility() const {
        cout << "What facility would you like to use?" << endl;
        cout << "1. Gym\n2. Swimming Pool\n3. Park\n";
        int choice;
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "Using Gym...\n";
                break;
            case 2:
                cout << "Using Swimming Pool...\n";
                break;
            case 3:
                cout << "Using Park...\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }
    }

    void useTransportation() const {
        cout << "What transportation would you like to use?" << endl;
        cout << "1. Bus\n2. Train\n3. Car\n";
        int choice;
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "Using Bus...\n";
                break;
            case 2:
                cout << "Using Train...\n";
                break;
            case 3:
                cout << "Using Car...\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }
    }
};

// Main function demonstrating usage
int main() {
    string name;
    int choice;

    // Welcome message
    cout << "Welcome to the Smart Eco City Simulation Platform!" << endl;

    while (true) {
        // Role selection menu loop
        cout << "1. You are a civilian." << endl;
        cout << "2. You are the manager." << endl;
        cout << "Please choose an option (1 or 2): ";
        cin >> choice;

        // Ask for user name
        cout << "Please enter your name: ";
        cin >> name;

        if (choice == 1) {
            // Handle civilian role
            Civilian civilian(name);
            civilian.showDetails();

            // Civilian menu loop
            int civilianChoice;
            while (true) {
                cout << "\nWhat would you like to do?" << endl;
                cout << "1. View city status" << endl;
                cout << "2. Purchase apartment" << endl;
                cout << "3. Use facility (gym, pool, park)" << endl;
                cout << "4. Use transportation (bus, train, car)" << endl;
                cout << "5. Exit" << endl;
                cout << "Enter your choice: ";
                cin >> civilianChoice;

                if (civilianChoice == 1) {
                    civilian.viewCityStatus();
                } else if (civilianChoice == 2) {
                    civilian.purchaseApartment();
                } else if (civilianChoice == 3) {
                    civilian.useFacility();
                } else if (civilianChoice == 4) {
                    civilian.useTransportation();
                } else if (civilianChoice == 5) {
                    cout << "Goodbye, " << name << "! Exiting Civilian Mode." << endl;
                    break;
                } else {
                    cout << "Invalid choice. Please enter a number from 1 to 5." << endl;
                }
            }

            // Break out of the loop after civilian exits
            break;
        }
        else if (choice == 2) {
            // Handle manager role
            Manager manager(name);

            // Password validation for Manager
            if (manager.verifyPassword()) {
                manager.showDetails();

                // Manager menu loop
                int managerChoice;
                while (true) {
                    cout << "\nWhat would you like to do?" << endl;
                    cout << "1. View city status" << endl;
                    cout << "2. View building status" << endl;
                    cout << "3. Upgrade building" << endl;
                    cout << "4. Add or remove resources" << endl;
                    cout << "5. View pollution levels" << endl;
                    cout << "6. Save data" << endl;
                    cout << "7. Update data" << endl;
                    cout << "8. Delete data" << endl;
                    cout << "9. Exit" << endl;
                    cout << "Enter your choice: ";
                    cin >> managerChoice;

                    if (managerChoice == 1) {
                        manager.viewCityStatus();
                    } else if (managerChoice == 2) {
                        manager.viewBuildingStatus();
                    } else if (managerChoice == 3) {
                        string building;
                        cout << "Enter building name to upgrade: ";
                        cin >> building;
                        manager.upgradeBuilding(building);
                    } else if (managerChoice == 4) {
                        string resource;
                        double amount;
                        cout << "Enter resource name: ";
                        cin >> resource;
                        cout << "Enter amount to add/remove: ";
                        cin >> amount;
                        manager.addResource(resource, amount); // Modify resources
                    } else if (managerChoice == 5) {
                        manager.viewPollutionLevels();
                    } else if (managerChoice == 6) {
                        string data;
                        cout << "Enter data to save (e.g., building or resource data): ";
                        cin.ignore();
                        getline(cin, data);
                        manager.saveDataToFile("buildings.txt", data);  // Can change to other files as required
                    } else if (managerChoice == 7) {
                        string oldData, newData;
                        cout << "Enter data to update (old): ";
                        cin.ignore();
                        getline(cin, oldData);
                        cout << "Enter updated data: ";
                        getline(cin, newData);
                        manager.updateDataInFile("buildings.txt", oldData, newData);
                    } else if (managerChoice == 8) {
                        string dataToDelete;
                        cout << "Enter data to delete: ";
                        cin.ignore();
                        getline(cin, dataToDelete);
                        manager.deleteDataFromFile("buildings.txt", dataToDelete);
                    } else if (managerChoice == 9) {
                        cout << "Goodbye, " << name << "! Exiting Manager Mode." << endl;
                        break;
                    } else {
                        cout << "Invalid choice. Please enter a number from 1 to 9." << endl;
                    }
                }

                // Break out of the loop after manager exits
                break;
            } else {
                cout << "Incorrect password! Access denied.\n";
            }
        }
        else {
            cout << "Invalid choice. Please restart the simulation." << endl;
        }
    }

    return 0;
}
