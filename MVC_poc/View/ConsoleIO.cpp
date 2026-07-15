#include "ConsoleIO.h"

#include <iostream>
#include <limits>

namespace sos::view {

void PrintDivider() {
    std::cout << "----------------------------------------\n";
}

void PrintMessage(const std::string& message) {
    std::cout << message << "\n";
}

int ReadInt(const std::string& prompt) {
    std::cout << prompt;
    int value = 0;
    while (!(std::cin >> value)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "숫자를 입력해주세요: ";
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return value;
}

std::string ReadLine(const std::string& prompt) {
    std::cout << prompt;
    std::string value;
    std::getline(std::cin, value);
    return value;
}

}  // namespace sos::view
