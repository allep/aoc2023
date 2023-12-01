#include <iostream>
#include <fstream>
#include <string>
#include <cstddef>
#include <sstream>
#include <array>
#include <map>

static constexpr char TEST_FILE_PATH1[] = "input/test_input.txt";
static constexpr char TEST_FILE_PATH2[] = "input/test_input_2.txt";
static constexpr char FILE_PATH[] = "input/input.txt";

using DigitMap = std::map<std::string, unsigned int>;

static const DigitMap NUMBERS_MAP = {
    {"one", 1},
    {"two", 2},
    {"three", 3},
    {"four", 4},
    {"five", 5},
    {"six", 6},
    {"seven", 7},
    {"eight", 8},
    {"nine", 9},
    {"0", 0},
    {"1", 1},
    {"2", 2},
    {"3", 3},
    {"4", 4},
    {"5", 5},
    {"6", 6},
    {"7", 7},
    {"8", 8},
    {"9", 9},
};

class CalibrationRecoverer {
public:
    CalibrationRecoverer(const std::string& filePath) : _filePath{filePath} {}

    unsigned int FindFirstNumber(const std::string& line) const {
        size_t retIndex = line.npos;
        unsigned int foundNumber{0};

        for (const auto& element : NUMBERS_MAP) {
            const auto index = line.find(element.first);

            if (index != line.npos && index <= retIndex) {
                retIndex = index;
                foundNumber = element.second;
            }
        }
        
        return foundNumber; 
    }

    unsigned int FindLastNumber(const std::string& line) const {
        size_t retIndex = 0;
        unsigned int foundNumber{0};

        for (const auto& element : NUMBERS_MAP) {
            const auto index = line.rfind(element.first);

            if (index != line.npos && index >= retIndex) {
                retIndex = index;
                foundNumber = element.second;
            }
        }
        
        return foundNumber; 
    }

    unsigned int RecoverCalibrationFromLine(const std::string& line) const {
        const auto first = FindFirstNumber(line);
        const auto last = FindLastNumber(line);

        std::cout << "First: " << first << ", last: " << last << std::endl;
        
        std::stringstream ss;
        ss << first << last;
        const std::string code = ss.str();
        return std::stoi(code);
    }

    bool ParseFileContentAndUpdateCalibration(std::ifstream& file) {
        bool success{false};
        std::string line{};

        unsigned int linesNum{0};
        while (std::getline(file, line)) {
            ++linesNum;

            const auto calibration = RecoverCalibrationFromLine(line);
            _recoveredValue += calibration;
        }

        success = (linesNum > 0);
        return success;
    }

    bool OpenAndParseFile() {
        bool success{false};
        std::ifstream inputFile;
        inputFile.open(_filePath.c_str(), std::ios::in);
        
        if (inputFile) {
            ParseFileContentAndUpdateCalibration(inputFile);
            success = true;
        }

        inputFile.close();
        return success;
    }

    unsigned int RecoverAndReturn() {
        _recoveredValue = 0;

        OpenAndParseFile();

        return _recoveredValue;
    }

private:
    const std::string _filePath{};
    unsigned int _recoveredValue{};
};

int main() {
    CalibrationRecoverer recoverer{FILE_PATH};
    const auto recoveredValue = recoverer.RecoverAndReturn();

    std::cout << "Recovered value: " << recoveredValue << std::endl;

    return 0;
}
