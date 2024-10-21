#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <random>
#include "./fs/filesystem.hpp"

using namespace std;

string getFileNameFromId(string id) {
    string path = "./";
    try {
        for (const auto & entry : ghc::filesystem::directory_iterator(path)) {
            string filename = entry.path().filename().string();
            int length = filename.length();
            if(length <= 7) continue;
            string userId = filename.substr(length-8,length);
            if(userId == id+".txt"){
                return filename;
            }
        }
    } catch (...) {
        cerr << "Error accessing filesystem" << endl;
    }
    return "File not found";
}

class Traveller {
    char tname[50];
    int age;
    char date1[9], date2[9];
    char destination_addr[100];
    char travel_mode[20];
    int id;
    
    public:
        static int counter; 
        void readData() {
            try {
                cout << "Enter traveller name: ";
                cin.getline(tname, 50);
                if (cin.fail()) throw "Invalid input for name";

                cout << "Enter age: ";
                cin >> age;
                if (cin.fail() || age < 0 || age > 150) throw "Invalid age";
                cin.ignore();

                cout << "Enter destination address: ";
                cin.getline(destination_addr, 100);
                if (cin.fail()) throw "Invalid input for address";

                cout << "Enter start date (format: dd/mm/yy): ";
                cin.getline(date1, 9);
                if (cin.fail() || strlen(date1) != 8) throw "Invalid start date format";

                cout << "Enter end date (format: dd/mm/yy): ";
                cin.getline(date2, 9);
                if (cin.fail() || strlen(date2) != 8) throw "Invalid end date format";
            } catch (const char* msg) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                throw;
            }
        }

        string getFileName() {
            counter++; 
            id = counter;
            return "T_" + string(tname) + to_string(counter) + ".txt";
        }

        void writeToFile(ofstream& file) const {
            file.write((char *) & (*this), sizeof(Traveller)); 
        }

        void readFromFile(ifstream& file) {
            file.read((char *) & (*this), sizeof(Traveller));
            file.clear();
        }

        void updateAge(int newAge) { age = newAge; }
        
        void appendTravelMode(const string& mode) {
            strncpy(travel_mode, mode.c_str(), sizeof(travel_mode) - 1);
            travel_mode[sizeof(travel_mode) - 1] = '\0';
        }

        void writeData() {
            int boxWidth = 50;
            char borderChar = '*';
            string title = "TRAVEL INFORMATION";  

            int titlePadding = (boxWidth - title.length()) / 2;  

            cout << setfill(borderChar) << setw(boxWidth) << "" << endl;
            cout << setfill(' ') << setw(titlePadding) << "" << title << setw(boxWidth - titlePadding - title.length()) << "" << endl;
            cout << setfill(borderChar) << setw(boxWidth) << "" << endl;

            cout << setfill(' ');
            cout << "| " << setw(boxWidth - 4) << left << ("Name: " + string(tname)) << " |" << endl;
            cout << "| " << setw(boxWidth - 4) << left << ("Id: " + to_string(id)) << " |" << endl;
            cout << "| " << setw(boxWidth - 4) << left << ("Age: " + to_string(age)) << " |" << endl;
            cout << "| " << setw(boxWidth - 4) << left << ("Destination: " + string(destination_addr)) << " |" << endl;
            cout << "| " << setw(boxWidth - 4) << left << ("Start date: " + string(date1)) << " |" << endl;
            cout << "| " << setw(boxWidth - 4) << left << ("End date: " + string(date2)) << " |" << endl;

            if (travel_mode[0] != '\0') {
                cout << "| " << setw(boxWidth - 4) << left << ("Travel Mode: " + string(travel_mode)) << " |" << endl;
            }

            cout << setfill(borderChar) << setw(boxWidth) << "" << endl;
        }

        char* getStartDate() { return date1; }
        char* getEndDate() { return date2; }
};

int Traveller::counter = 1000;

void createTravellerFile() {
    try {
        Traveller traveller;
        traveller.readData();

        string filename = traveller.getFileName();
        ofstream outFile(filename);

        if (!outFile) {
            throw "Error creating file!";
        }

        traveller.writeToFile(outFile);
        outFile.close();

        cout << "\nTraveller details saved to file: " << filename << endl;
        cout << "\nFile contents:" << endl;

        ifstream inFile(filename);
        if (!inFile) {
            throw "Error opening file for reading!";
        }
        traveller.readFromFile(inFile);
        traveller.writeData();
        inFile.close();
    } catch (const char* msg) {
        cerr << "Error: " << msg << endl;
    }
}

void editTravellerAge() {
    try {
        int newAge;
        string id;
        cout << "Enter traveller's id: ";
        cin >> id;
        if (cin.fail()) throw "Invalid input for ID";

        string filename = getFileNameFromId(id);
        ifstream inFile(filename);
        if (!inFile) {
            throw "Error opening file!";
        }

        Traveller traveller;
        traveller.readFromFile(inFile);
        inFile.close();

        while (true) {
            cout << "Enter new age: ";
            cin >> newAge;
            if (cin.fail() || newAge < 1 || newAge > 150) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid age. Please enter a valid age between 1 and 150." << endl;
            } else {
                break;
            }
        }

        traveller.updateAge(newAge);

        ofstream outFile(filename);
        if (!outFile) {
            throw "Error opening file for writing!";
        }
        traveller.writeToFile(outFile);
        outFile.close();

        cout << "\nUpdated traveller details:" << endl;
        traveller.writeData();
    } catch (const char* msg) {
        cerr << "Error: " << msg << endl;
    }
}

void appendTravelMode() {
    try {
        string id;
        cout << "Enter Traveller's id: ";
        cin >> id;
        if (cin.fail()) throw "Invalid input for ID";

        string filename = getFileNameFromId(id);
        ifstream inFile(filename);
        if (!inFile) {
            throw "Error opening file for reading!";
        }

        Traveller traveller;
        traveller.readFromFile(inFile);
        inFile.close();

        cin.ignore();
        string mode;
        cout << "Enter travel mode(bus/train/flight): ";
        getline(cin, mode);
        if (mode != "bus" && mode != "train" && mode != "flight") {
            throw "Invalid travel mode. Please enter bus, train, or flight.";
        }

        traveller.appendTravelMode(mode);

        ofstream outFile(filename);
        if (!outFile) {
            throw "Error opening file for writing!";
        }
        traveller.writeToFile(outFile);
        outFile.close();

        cout << "\nUpdated traveller details:\n";
        traveller.writeData();
    } catch (const char* msg) {
        cerr << "Error: " << msg << endl;
    }
}

void getTravellersByDate() {
    try {
        string date;
        int choice;
        cout << "Do you want to search by start date or end date? (1/2): ";
        cin >> choice;
        if (cin.fail() || (choice != 1 && choice != 2)) {
            throw "Invalid choice. Please enter 1 or 2.";
        }

        cout << "Enter date (format: dd/mm/yy): ";
        cin >> date;
        if (date.length() != 8) {
            throw "Invalid date format. Please use dd/mm/yy.";
        }

        string path = "./";
        bool found = false;
        for (const auto & entry : ghc::filesystem::directory_iterator(path)) {
            string filename = entry.path().filename().string();
            if (filename.substr(0,2) == "T_") {
                ifstream file(filename);
                if (!file) {
                    cerr << "Warning: Could not open file " << filename << endl;
                    continue;
                }
                Traveller traveller;
                traveller.readFromFile(file);
                file.close();

                if ((choice == 1 && traveller.getStartDate() == date) ||
                    (choice == 2 && traveller.getEndDate() == date)) {
                    traveller.writeData();
                    found = true;
                }
            }
        }
        if (!found) {
            cout << "No travellers found for the given date." << endl;
        }
    } catch (const char* msg) {
        cerr << "Error: " << msg << endl;
    }
}

int main() {
    int choice;
    try {
        ifstream fileIn("state.txt");
        int stateCounter;

        if (fileIn >> stateCounter && stateCounter != 0) {
            Traveller::counter = stateCounter;
        } else {
            ofstream fileOut("state.txt", ios::trunc);
            if (!fileOut) {
                throw "Error creating state file!";
            }
            fileOut << 0;
            fileOut.close();
        }

        string input;
        do {
            cout << "\nTravel Information System\n"
                 << "1. Enter traveller details\n"
                 << "2. Edit traveller age\n"
                 << "3. Append travel mode\n"
                 << "4. Get travellers by date\n"
                 << "5. Exit\n"
                 << "Enter your choice: ";
            getline(cin, input);

            if (input.length() == 1 && isdigit(input[0])) {
                choice = input[0] - '0';
            } else {
                choice = 0; 
            }

            switch (choice) {
                case 1:
                    createTravellerFile();
                    break;
                case 2:
                    editTravellerAge();
                    cin.ignore();
                    break;
                case 3:
                    appendTravelMode();
                    break;
                case 4:
                    getTravellersByDate();
                    cin.ignore();
                    break;
                case 5:
                    cout << "Exiting program." << endl;
                    break;
                default:
                    cout << "Invalid choice. Please try again." << endl;
            }
        } while (choice != 5);

        ofstream fileOut("state.txt", ios::trunc);
        if (!fileOut) {
            throw "Error opening state file for writing!";
        }
        fileOut << Traveller::counter;
        fileOut.close();

    } catch (const char* msg) {
        cerr << "Fatal error: " << msg << endl;
        return 1;
    }

    return 0;
}