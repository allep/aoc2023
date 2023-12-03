#include <algorithm>
#include <charconv>
#include <iostream>
#include <string_view>

#include "GameValidator.h"

GameValidator::GameValidator(std::vector<std::string> &&inRecords) {
  for (const auto &rawRecord : inRecords) {
    records.emplace_back(GetParsedRecord((rawRecord)));
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
  static const std::string GameTag{"Game"};
  static const std::string Digits{"0123456789"};
  const auto start{record.find(GameTag)};
  const auto end{record.find(':')};

  unsigned int parsedId{0};
  if (start != record.npos && end != record.npos) {
    const auto idStart = start + GameTag.length();
    const auto idLength = end - idStart;

    if (idLength > 0) {
      const auto id{record.substr(idStart, idLength)};

      const auto actualStart = id.find_first_of(Digits);
      const auto actualEnd = id.find_last_of(Digits);

      const auto updatedId{id.substr(actualStart, actualEnd)};

      // TODO: this may return an error, hence we should manage it.
      std::from_chars(updatedId.data(), updatedId.data() + updatedId.size(),
                      parsedId);
    }
  }

  return parsedId;
}

std::vector<RevealedSet>
GameValidator::GetParsedRevealedSets(const std::string_view record) const {
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