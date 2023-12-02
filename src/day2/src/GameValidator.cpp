#include "GameValidator.h"

GameValidator::GameValidator(std::vector<std::string> &&records)
    : _records{std::move(records)} {}

void GameValidator::ValidateRecordsAgainstConfig(
    std::map<std::string, unsigned int> &&configuration) {
  _configuration = std::move(configuration);
}

unsigned int GameValidator::GetIDsSum() const { return 0; }

void GameValidator::Reset() {
  _records.clear();
  _configuration.clear();
}