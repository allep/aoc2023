#include <algorithm>
#include <iostream>
#include <string_view>

#include "GameRecordParser.h"
#include "GameValidator.h"

GameValidator::GameValidator(std::vector<std::string> &&inRecords) {
  for (const auto &rawRecord : inRecords) {
    GameRecordParser parser{rawRecord};
    if (parser.Parse()) {
      records.emplace_back(parser.MakeGameRecord());
    }
  }
}

void GameValidator::ValidateRecordsAgainstConfig(
    std::map<std::string, unsigned int> &&inConfiguration) {
  configuration = std::move(inConfiguration);

  for (const auto &record : records) {
    bool isRecordValid{true};
    for (const auto &constraints : configuration) {
      const auto type = constraints.first;
      const auto maxNumber = constraints.second;

      if (record.GetNumberByType(type) > maxNumber) {
        isRecordValid = false;
        break;
      }
    }

    if (isRecordValid) {
      validRecords.push_back(record);
    }
  }
}

unsigned int GameValidator::GetIDsSum() const {
  auto IDsSum{0};

  for (const auto &record : validRecords) {
    IDsSum += record.GetGameID();
  }

  return IDsSum;
}

void GameValidator::Reset() {
  records.clear();
  validRecords.clear();
  configuration.clear();
}