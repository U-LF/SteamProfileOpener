#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <windows.h>

// Function to extract the id64 from a line of text
std::string extractId64(const std::string& line) {
    std::regex id64Regex("\\d{17}");
    std::smatch match;
    if (std::regex_search(line, match, id64Regex)) {
        return match[0];
    }
    return "";
}

// Function to open a Steam profile in the default web browser
void openProfile(const std::string& id64) {
    std::string url = "https://steamcommunity.com/profiles/" + id64;
    ShellExecuteA(NULL, "open", url.c_str(), NULL, NULL, SW_SHOWNORMAL);
}

int main() {
    // Open or create the input file
    std::ifstream inputFile("players.txt");
    std::ofstream outputFile("players.txt", std::ios_base::app);
    if (!inputFile.is_open()) {
        std::cerr << "Failed to open input file. Creating a new one." << std::endl;
        inputFile.close();
        std::cout << "Enter the Steam player data. Press Ctrl+Z and Enter to save and exit." << std::endl;
        std::string line;
        while (std::getline(std::cin, line)) {
            if (line.empty()) break; // Break the loop when Ctrl+Z is pressed
            outputFile << line << std::endl;
        }
        outputFile.close();
        return 0;
    }

    // Read the data from the file
    std::vector<std::string> lines;
    std::string line;
    while (std::getline(inputFile, line)) {
        lines.push_back(line);
    }
    inputFile.close();

    // Extract the id64 from each line and open the profile in the browser
    int Times{ 0 };
    for (const auto& line : lines) {
        std::string id64 = extractId64(line);
        if (!id64.empty()) {
            openProfile(id64);
        }
        if (Times == 30)
        {
            std::cout << "30 profiles have been opened, press any key when you are ready to open the next 30\n";
            Times = 0;
            system("PAUSE");
        }
        Times++;
    }

    return 0;
}