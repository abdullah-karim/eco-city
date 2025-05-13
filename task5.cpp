#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class user {
protected:
    string name;
    string role;
public:
    user(string name, string role) {
        this->name = name;
        this->role = role;
    }
    virtual void showdetails() = 0; 
};

class civilian : public user {
public:
    civilian(string name, string role) : user(name, role) {}

    void showdetails() {
        cout << "Welcome " << name << endl;
    }

    // File handling to save civilian names
    void savename() {
        ofstream file("civilian.txt", ios::app);  // Open in append mode
        if (!file) {
            cout << "Error opening file!" << endl;
            return;
        }
        file << name << endl;  // Append name to the file
        file.close();
    }

    void view_city_status() {
        cout << "\nCity Status: " << endl;
        cout << "Current Eco-Score: 500 points" << endl;
        cout << "Current Pollution Level: Moderate" << endl;
        cout << "Energy Efficiency: 80%" << endl;
    }

    void trackCarbonFootprint() {
        double distanceTraveled, electricityUsageHours;
        cout << "Enter the total distance you traveled using your petrol/diesel car (in kilometers): ";
        cin >> distanceTraveled;
        cout << "Enter the number of hours you used electricity: ";
        cin >> electricityUsageHours;

        double carEmissionsPerKm = 0.2;  // kg CO2 per km for a petrol/diesel car
        double electricityEmissionsPerKWh = 0.4;  // kg CO2 per kWh for electricity

        double powerConsumptionPerHour = 1.0;  // 1 kWh per hour

        double carbonEmissionsFromTransport = distanceTraveled * carEmissionsPerKm;
        double carbonEmissionsFromElectricity = electricityUsageHours * powerConsumptionPerHour * electricityEmissionsPerKWh;

        double totalCarbonEmissions = carbonEmissionsFromTransport + carbonEmissionsFromElectricity;

        cout << "Carbon emissions from transportation: " << carbonEmissionsFromTransport << " kg CO2" << endl;
        cout << "Carbon emissions from electricity usage: " << carbonEmissionsFromElectricity << " kg CO2" << endl;
        cout << "Total carbon emissions: " << totalCarbonEmissions << " kg CO2" << endl;

        // File handling to save carbon footprint data
        ofstream outputFile("carbon_footprints.txt", ios::app);  // Open in append mode
        if (outputFile.is_open()) {
            outputFile << "Name: " << name << endl;
            outputFile << "Distance Traveled: " << distanceTraveled << " km\n";
            outputFile << "Electricity Usage: " << electricityUsageHours << " hours\n";
            outputFile << "Carbon Emissions from Transport: " << carbonEmissionsFromTransport << " kg CO2\n";
            outputFile << "Carbon Emissions from Electricity Usage: " << carbonEmissionsFromElectricity << " kg CO2\n";
            outputFile << "Total Carbon Emissions: " << totalCarbonEmissions << " kg CO2\n";
            outputFile << "-----------------------------------------------\n";
            outputFile.close();  // Close the file
            cout << "Your carbon footprint has been saved"<<endl;
        } else {
            cout << "Error opening file to save carbon footprint data.\n";
        }
    }

    // File handling to save facility usage data
    void useFacility() const {
        cout << "What facility would you like to use?" << endl;
        cout << "1. Gym\n2. Swimming Pool\n3. Park\n";
        int choice;
        cin >> choice;
        string facilityUsed;
        
        switch (choice) {
            case 1:
                cout << "Using Gym...\n";
                facilityUsed = "Gym";
                break;
            case 2:
                cout << "Using Swimming Pool...\n";
                facilityUsed = "Swimming Pool";
                break;
            case 3:
                cout << "Using Park...\n";
                facilityUsed = "Park";
                break;
            default:
                cout << "Invalid choice!\n";
                return;
        }

        // Save the facility usage data to a file
        ofstream file("facility_usage.txt", ios::app);  // Open in append mode
        if (file.is_open()) {
            file << "Facility used: " << facilityUsed << " by " << name << endl;
            file.close();
            cout << "Your facility usage has been recorded"<<endl;
        } else {
            cout << "Error opening file to save facility usage data.\n";
        }
    }

    // Function to plant a tree and track the number of trees planted
    void plantTree() {
        static int treesPlanted = 0;
        treesPlanted++;  

        cout << "Tree planted successfully!" << endl;
        cout << "Total trees planted: " << treesPlanted << endl;

        // File handling to save the tree planting data
        ofstream file("tree_planting_log.txt", ios::app);  // Open file in append mode
        if (file.is_open()) {
            file << "Tree planted. Total trees planted: " << treesPlanted << endl;
            file.close();
            cout << "Your tree planting effort has been saved"<<endl;
        } else {
            cout << "Error opening file to save tree planting data.\n";
        }
    }
};

class Manager : public user {
private:
    string password; // Default password
public:
    Manager(string name) : user(name, "Manager") {
        password = "admin123"; // Default password
    }

    void showdetails() {
        cout << "Welcome, Manager " << name << "!" << endl;
        saveNameToFile();  // Save manager's name to the file
    }

    void saveNameToFile() {
        ofstream file("manager_names2.txt", ios::app);
        if (!file) {
            cout << "Error opening file!" << endl;
            return;
        }
        file << name << endl;
        file.close();
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

    // Add Resource function to Manager class
    void addResource(const string& resource, double amount) {
        if (amount <= 0) {
            cout << "Error: Cannot add a non-positive amount of " << resource << "!\n";
            return;
        }

        cout << "\nAdding " << amount << " units of " << resource << ".\n";

        // Provide brief context for the resource being added
        if (resource == "Water") cout << "Water is essential for daily activities, agriculture, and ecosystems.\n";
        else if (resource == "Electricity") cout << "Electricity powers homes, industries, and devices.\n";
        else if (resource == "Gas") cout << "Gas is used for heating, cooking, and industrial processes.\n";
        else cout << "Resource: " << resource << " is being added for system improvement.\n";

        cout << resource << " added successfully!" << endl;

        // File handling to save the resource addition data
        ofstream logFile("resource_log.txt", ios::app);
        if (logFile) logFile << "Added " << amount << " units of " << resource << " to the system.\n";
        else cout << "Error: Unable to open log file.\n";
    }
};

int main() {
    string name;
    cout << "Welcome to the smart eco city simulation" << endl;
    cout << "Enter your name: " << endl;
    getline(cin, name);  // Get the full name of the user

    cout << "Welcome " << name << endl;
    cout << "Are you a user or a manager?" << endl;
    cout << "Press 1 for user" << endl;
    cout << "Press 2 for manager" << endl;

    int choice;
    cin >> choice;  // Get the choice from the user

    if (choice == 1) {
        civilian c1(name, "user");
        c1.showdetails();

        int actionChoice;
        cout << "What would you like to do?" << endl;
        cout << "1. Track carbon footprint" << endl;
        cout << "2. View city status" << endl;
        cout << "3. Use a facility" << endl;
        cout << "4. Plant a tree" << endl;
        cout << "Enter your choice: ";
        cin >> actionChoice;

        if (actionChoice == 1) {
            c1.trackCarbonFootprint();  
        } else if (actionChoice == 2) {
            c1.view_city_status();  
        } else if (actionChoice == 3) {
            c1.useFacility();  // Call useFacility to track facility usage
        } else if (actionChoice == 4) {
            c1.plantTree();  // Call plantTree to plant a tree and record it
        } else {
            cout << "Invalid choice." << endl;
        }

        c1.savename();  // Save the name to the file
    } else if (choice == 2) {
        Manager m1(name);

        // Manager password verification
        if (m1.verifyPassword()) {
            int managerChoice;
            cout << "\nWhat would you like to do?" << endl;
            cout << "1. View City Status" << endl;
            cout << "2. View Building Status" << endl;
            cout << "3. Add a resource" << endl;
            cout << "Enter your choice: ";
            cin >> managerChoice;

            if (managerChoice == 1) {
                m1.viewCityStatus();
            } else if (managerChoice == 2) {
                m1.viewBuildingStatus();
            } else if (managerChoice == 3) {
                string resource;
                double amount;
                cout << "Enter resource (Water, Electricity, Gas): ";
                cin >> resource;
                cout << "Enter amount: ";
                cin >> amount;
                m1.addResource(resource, amount);  // Manager can add resources
            } else {
                cout << "Invalid choice." << endl;
            }
        } else {
            cout << "Incorrect password. Access denied." << endl;
        }
    } else {
        cout << "Invalid choice. Exiting program." << endl;
    }

    return 0;
}
