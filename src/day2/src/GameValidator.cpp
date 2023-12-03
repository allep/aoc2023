#include "GameValidator.h"
#include <string_view>

GameValidator::GameValidator(std::vector<std::string> &&inRecords) {
  for (const auto &rawRecord : inRecords) {
    records.emplace_back(GetParsedRecord((rawRecord)));
  }
}

GameRecord GameValidator::GetParsedRecord(const std::string_view record) const {
  // todo:
  // 1. parse record one by one
  // 2. extract game number to be the key, then each game would be an element
  // 3. each element should have a map with {key = color; value = number}
  // 4. create a class for that
  return {0};
}

void GameValidator::ValidateRecordsAgainstConfig(
    std::map<std::string, unsigned int> &&inConfiguration) {
  configuration = std::move(inConfiguration);
}

unsigned int GameValidator::GetIDsSum() const { return 0; }

void GameValidator::Reset() {
  records.clear();
  validRecords.clear();
  configuration.clear();
}