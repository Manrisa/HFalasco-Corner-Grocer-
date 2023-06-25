//
//Hunter Falasco
// 6/18/23
//SNHU
//
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>

using namespace std;

void printMenu() { // Print menu, this will be looped upon in main
    cout << "\n";
    cout << "Menu:\n";
    cout << "1. Add item\n";
    cout << "2. Print frequency of all items\n";
    cout << "3. Print histogram of item frequency\n";
    cout << "4. Quit\n";
    cout << "Enter your choice (1-4): ";
}

void addItem(map<string, int>) { // This block adds items
    string item;
    cout << "Enter the item: ";
    cin >> item; 

    ofstream outputFile("CS210_Project_Three_Input_File.text", ios::app);
    if (!outputFile) {
        cerr << "Error opening file for writing!\n"; // Error check 
        return;
    }
    outputFile << item << '\n'; // Adds the text 
    outputFile.close();// Closes file
    cout << "Item added to 'CS210_Project_Three_Input_File.text'.\n"; // Confirmation Text


    ofstream backupFile("Backup.dat", ios::app);
    if (!backupFile) {
        cerr << "Error opening file for writing!\n"; // Error check 
        return;
    }
    backupFile << item << '\n'; // Adds the text 
    backupFile.close();// Closes file
    cout << "Item added to 'Backup.dat'.\n"; // Confirmation Text


}


std::map<std::string, int> wordCount;
void printFrequency() { // Print frequency block
    string word;
    ifstream inputFile("CS210_Project_Three_Input_File.text"); // Reads data from Backup.dat to print
    if (!inputFile) {
        cerr << "Error opening file for reading!\n"; // Error check
        return;
    }

    cout << "\n"; // New line for neatness

    cout << "Printing Frequency of All Items:\n";
    string line;
    map<string, int> itemFrequency;

    while (inputFile >> word) {
        
        string cleanedWord; // Removes any accidental number presses or capitals
        for (char c : word) {
            if (std::isalpha(c)) {
                cleanedWord += std::tolower(c);
            }
        }

        if (!cleanedWord.empty()) {
            ++wordCount[cleanedWord];
        }
    }
    inputFile.close(); // Close file

    cout << "Item frequency in the file:\n";
    for (const auto& pair : wordCount) {
        cout << pair.first << ": " << pair.second << '\n';
    }
    wordCount.clear();// Resets the word count after this function has been called Without this the file was douplicating the count
  
}
// This below block is practically just a copy and paste of the PrintFrequency function with a change at the bottom
void printHistogram() { // This reads off of Backup.dat and collects the data to print into a Histogram
    string word;
    ifstream inputFile("CS210_Project_Three_Input_File.text"); // Reads data from Backup.dat to print
    if (!inputFile) {
        cerr << "Error opening file for reading!\n"; // Error check
        return;
    }

    cout << "\n"; // New line for neatness

    cout << "Printing Frequency of All Items:\n";
    string line;
    map<string, int> itemFrequency;

    while (inputFile >> word) {

        string cleanedWord; // Removes any accidental number presses or capitals
        for (char c : word) {
            if (std::isalpha(c)) {
                cleanedWord += std::tolower(c);
            }
        }

        if (!cleanedWord.empty()) {
            ++wordCount[cleanedWord];
        }
    }
    inputFile.close(); // Close file

    for (const auto& pair : wordCount) { // Same printing loop as Print Print frequency, however it adds an * everytime the word is counted rather than a number
        cout << pair.first << ": ";
        for (int i = 0; i < pair.second; ++i) {
            cout << "*";
        }
        cout << "\n";
    }


    wordCount.clear(); // Resets the word count after this function has been called Without this the file was douplicating the count
}


int main() {
    map<string, int> itemFrequency;

    ifstream backupFile("Backup.dat"); // Checking to see if the Data Backup has been created
    if (!backupFile) {
        ofstream createFile("Backup.dat");
        if (!createFile) { // Error check
            cerr << "Error creating file!\n"; // This is unlikley to happen however in the offchance that it does
            return 1;
        }
        createFile.close();
        cout << "Backup file created.\n"; // Creation was sucsessful
    }
    else {
        string line; // If the Backup.dat DOES exist it reads the file
        while (getline(backupFile, line)) {
            istringstream iss(line);
            string item;
            string frequency;
            if (getline(iss, item, ':') && getline(iss, frequency)) {
                itemFrequency[item] = stoi(frequency);
            }
        }
        backupFile.close();
        cout << "Data loaded from backup file.\n"; // Confirmation message
    }

    int choice; // Declaring choice
    do {
        printMenu(); // Main loop block of the program, 
        cin >> choice;

        switch (choice) {
        case 1:
            addItem(itemFrequency);
            break;
        case 2:
            printFrequency();
            break;
        case 3:
            printHistogram();
            break;
        case 4:
            cout << "Exiting the program...\n";
            break;
        default:

            cout << "Invalid choice! Please try again.\n";
            cin >> choice;
            break;
        }
    } while (choice != 4); // if Choice == 4 the loop breaks and the program closes. 

    return 0;
}
