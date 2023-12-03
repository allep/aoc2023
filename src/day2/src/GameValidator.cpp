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

GameRecord GameValidator::GetParsedRecord(const std::string_view record) const {
  const auto gameID = GetParsedGameID(record);
  const auto revealedSets = GetParsedRevealedSets(record);
  // todo:
  // 1. parse record one by one
  // 2. extract game number to be the key, then each game would be an element
  // 3. each element should have a map with {key = color; value = number}
  // 4. create a class for that

  std::cout << "GetParsedRecord: got id = " << gameID << std::endl;

  return {gameID};
}

unsigned int
GameValidator::GetParsedGameID(const std::string_view record) const {
  // TODO
  return 0;
}

std::vector<RevealedSet>
GameValidator::GetParsedRevealedSets(const std::string_view record) const {
  std::vector<RevealedSet> sets{};
  const auto start = record.find(':');

  if (start != record.npos && (start + 1 < record.length())) {
    const auto setStart = start + 1;
    sets = ParseRevealedSetsFromRecord(record, setStart);
  }

  return sets;
}

std::vector<RevealedSet>
GameValidator::ParseRevealedSetsFromRecord(const std::string_view record,
                                           size_t setStart) const {
  return {};
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