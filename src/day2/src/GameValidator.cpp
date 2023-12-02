#include "GameValidator.h"

GameValidator::GameValidator(std::vector<std::string> &&inRecords)
    : records{std::move(inRecords)} {
  // TODO: here I already need to process the records to be able to
  // use them later on
}

void GameValidator::ParseRecords() {
  // TODO:
  // 1. parse record one by one
  // 2. extract game number to be the key, then each game would be an element
  // 3. each element should have a map with {key = color; value = number}
  // 4. create a class for that
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