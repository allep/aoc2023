#include <iostream>

#include "FileReader.h"
#include "GameValidator.h"
#include "main_include.h"

static constexpr char fileName[] = "../src/input/input1.txt";

int main() {
  std::cout << "Program for: " << ProgramName << "!" << std::endl;

  FileReader reader{fileName};
  auto lines = reader.GetReadLines();

  std::cout << "Num lines read: " << lines.size() << std::endl;

  std::map<std::string, unsigned int> configuration{
      {"red", 12},
      {"green", 13},
      {"blue", 14},
  };

  auto validator = GameValidator{std::move(lines)};
  validator.ValidateRecordsAgainstConfig(std::move(configuration));

  const auto totRecords = validator.GetNumRecords();
  const auto validRecords = validator.GetNumValidRecords();

  const auto idSum = validator.GetIDsSum();

  std::cout << "Total records: " << totRecords << ", " << validRecords
            << std::endl;

  std::cout << "Summed IDs: " << idSum << std::endl;

  return 0;
}
