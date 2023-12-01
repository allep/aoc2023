#include <iostream>
#include <fstream>
#include <string>
#include <cstddef>
#include <sstream>

static constexpr char TEST_FILE_PATH[] = "input/test_input.txt";
static constexpr char FILE_PATH[] = "input/input.txt";
static constexpr char DIGITS[] = "0123456789";

class CalibrationRecoverer {
public:
    CalibrationRecoverer(const std::string& filePath) : _filePath{filePath} {}

    unsigned int RecoverCalibrationFromLine(const std::string& line) const {
        const auto first{line.find_first_of(DIGITS)};
        const auto last{line.find_last_of(DIGITS)};

        const char firstChar = line[first];
        const char lastChar = line[last];

        std::cout << "First: " << firstChar << ", last: " << lastChar << std::endl;
        
        std::stringstream ss;
        ss << firstChar << lastChar;
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
