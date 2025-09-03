#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

// Structure to hold nucleus data
struct Nucleus {
    std::string name;
    std::vector<double> values;
};

// Function to parse a line into a Nucleus struct
Nucleus parseLine(const std::string& line) {
    Nucleus nucleus;
    size_t colonPos = line.find(':');
    if (colonPos != std::string::npos) {
        nucleus.name = line.substr(0, colonPos);
        std::string valuesStr = line.substr(colonPos + 1);
        valuesStr.erase(std::remove(valuesStr.begin(), valuesStr.end(), '{'), valuesStr.end());
        valuesStr.erase(std::remove(valuesStr.begin(), valuesStr.end(), '}'), valuesStr.end());
        
        std::stringstream ss(valuesStr);
        std::string value;
        while (std::getline(ss, value, ',')) {
            try {
                nucleus.values.push_back(std::stod(value));
            } catch (const std::invalid_argument& e) {
                // Skip invalid entries
            }
        }
    }
    return nucleus;
}

// Function to search for the value within a given interval
float isValueInInterval(double target, double interval, const std::vector<double>& values) {
  float found=0;
    for(double value : values) {
        if (value >= target - interval && value <= target + interval) {
            found =value;
        }
    }
    return found;
}

int main() {
    std::ifstream file("./gamma_dataset.txt");
    if (!file) {
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }

    std::vector<Nucleus> nuclei;
    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            nuclei.push_back(parseLine(line));
        }
    }
    file.close();

    double target;
    double interval;
    std::cout << "Enter the value you want to search for: ";
    std::cin >> target;
    std::cout << "Enter the interval to search within: ";
    std::cin >> interval;

    for (const auto& nucleus : nuclei) {
        if (isValueInInterval(target, interval, nucleus.values)!=0) {
            // std::cout << nucleus.name << ": ";
	    std::cout << "\033[1;31m" << nucleus.name << ": " << "\033[0m";
	    std::cout << "\033[1;31m" << isValueInInterval(target, interval, nucleus.values)<< "\033[0m"<<'\n';
	    // std::cout<<isValueInInterval(target, interval, nucleus.values)<<'\n';
	    
            for (double value : nucleus.values) {
                std::cout << value << " ";
            }
            std::cout << std::endl;
        }
    }

    return 0;
}
