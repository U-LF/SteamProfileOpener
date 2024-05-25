#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <windows.h>

using namespace std;

// Function to extract the id64 from a line of text
string extractId64(const string& line) {
    regex id64Regex("\\d{17}");
    smatch match;
    if (regex_search(line, match, id64Regex)) {
        return match[0];
    }
    return "";
}

// Function to open a Steam profile in the default web browser
void openProfile(const string& id64) {
    string url = "https://steamcommunity.com/profiles/" + id64;
    ShellExecuteA(NULL, "open", url.c_str(), NULL, NULL, SW_SHOWNORMAL);
}

//M_Config stands for make_config and simply creates a new config file
void M_Config(int HowMany = 30)
{
    ofstream MakeConfig("Config.txt");
    MakeConfig << HowMany;
    MakeConfig.close();
}

int main() {

    cout << "Initializing the program...\n\n";

    // Open the input file
    ifstream InputFile("players.txt");

    if (!InputFile.is_open()) {

        cerr << "Failed to open input file, a new file will be created\n\n";

        InputFile.close();
        ofstream OutputFile("players.txt");

        cout << "The file has been created with the name 'player.txt', Enter the data in the file and launch the program again\n\n";

        OutputFile.close();
        return 0;
    }

    int Choice{ 0 };

    a:
    cout << "Press 1 to change config\n";
    cout << "Press 2 to continue with the program\n";
    cout << "Your choice: ";
    cin >> Choice;

    if (Choice == 1)
    {
        int After{ 0 };

        cout << "Enter the number of profiles after which you want to program to pause: ";
        cin >> After;

        M_Config(After);
    }
    if (Choice != 1 && Choice != 2)
    {
        cout << "Invalid choice, try again\n";
        goto a;
    }

    ifstream ConfigFile("Config.txt");

    if (!ConfigFile.is_open())
    {
        cout << "Config file not found, one will be now created\n";

        int After{ 0 };

        cout << "Enter the number of profiles after which you want to program to pause: ";
        cin >> After;

        M_Config(After);

        ConfigFile.close();
        ConfigFile.open("Config.txt");
    }

    cout << "The program is ready to start opening profiles\n";
    system("PAUSE");

    // Read the data from the file
    vector<string> lines;
    string line;
    while (getline(InputFile, line)) {
        lines.push_back(line);
    }
    InputFile.close();

    // Extract the id64 from each line and open the profile in the browser
    int Times{ 0 };

    int StopAfter;

    ConfigFile >> StopAfter;
    
    for (const auto& line : lines) {
        string id64 = extractId64(line);
        if (!id64.empty()) {
            openProfile(id64);
        }
        if (Times == StopAfter + 1)
        {
            cout << StopAfter << " profiles have been opened, press any key when you are ready to open the next " << StopAfter << "\n";
            Times = 0;
            system("PAUSE");
        }
        Times++;
    }

    return 0;
}