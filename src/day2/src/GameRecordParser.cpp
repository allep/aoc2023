#include <charconv>
#include <iostream>

#include "GameRecordParser.h"

namespace {
const std::string GameTag{"Game"};
const std::string Digits{"0123456789"};
} // namespace

GameRecordParser::GameRecordParser(const std::string_view inRawrawRecord)
    : rawRecord{inRawrawRecord} {}

bool GameRecordParser::Parse() {
  const auto gameIDSuccess = ParseGameID();
  const auto revealedSetSuccess = ParseRevealedSets();

  return gameIDSuccess && revealedSetSuccess;
}

bool GameRecordParser::ParseGameID() {
  auto success{false};
  const auto start{rawRecord.find(GameTag)};
  const auto end{rawRecord.find(':')};

  gameID = 0;
  if (start != rawRecord.npos && end != rawRecord.npos) {
    const auto idStart = start + GameTag.length();
    const auto idLength = end - idStart;

    if (idLength > 0) {
      UpdateParserPosition(end);

      const auto rawId{rawRecord.substr(idStart, idLength)};

      const auto actualStart = rawId.find_first_of(Digits);
      const auto actualEnd = rawId.find_last_of(Digits);

      const auto id{rawId.substr(actualStart, actualEnd)};

      // TODO: this may return an error, hence we should manage it.
      std::from_chars(id.data(), id.data() + id.size(), gameID);

      success = true;
    }
  }

  return success;
}

bool GameRecordParser::ParseRevealedSets() {
  const auto start{parserPosition};
  const auto revealedSetsRecord{rawRecord.substr(start)};

  std::cout << "DEBUG: substr " << revealedSetsRecord << std::endl;

  return false;
}

void GameRecordParser::UpdateParserPosition(size_t position) {
  parserPosition = position;
}

GameRecord GameRecordParser::MakeGameRecord() const {
  // TODO
  return {0};
}