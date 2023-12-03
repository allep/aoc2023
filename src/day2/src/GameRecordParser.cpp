#include <cassert>
#include <charconv>
#include <iostream>
#include <string_view>

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
      const auto nextTokenPosition = end + 1;
      UpdateParserPosition(nextTokenPosition);

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
  auto success{true};
  const auto start{parserPosition};
  const auto revealedSetsRecord{rawRecord.substr(start)};

  const auto sets = Tokenize(revealedSetsRecord, ';');
  for (const auto &set : sets) {
    success &= ParseSet(set);
  }

  return success;
}

bool GameRecordParser::ParseSet(std::string_view set) {
  RevealedSet element{};
  const auto samples = Tokenize(set, ',');

  for (const auto &sample : samples) {
    // Schema is: NNN type

    // number
    const auto numStart{sample.find_first_of(Digits)};
    const auto numEnd{sample.find_last_of(Digits)};

    const auto numberView{sample.substr(numStart, numEnd)};
    unsigned int number{0};

    // FIXME TODO: this may return an error, hence this code is unsafe
    std::from_chars(numberView.data(), numberView.data() + numberView.size(),
                    number);
    // type
    const auto typeStart = sample.find_first_not_of(' ', numEnd + 1);
    const auto typeEnd = sample.find_last_not_of(' ');
    const auto type{sample.substr(typeStart, typeEnd)};

    std::string typeStr{type};
    assert(element.count(typeStr) == 0);

    element.emplace(typeStr, number);
  }

  revealedSets.push_back(element);
  return true;
}

std::vector<std::string_view>
GameRecordParser::Tokenize(std::string_view view, const char separator) const {
  std::vector<std::string_view> tokens{};
  const auto start{0};
  const auto end{view.length()};

  auto pos{0};
  auto continueTokenize{true};
  while (continueTokenize) {
    const auto tokenStart = pos;
    auto tokenEnd = view.find(separator, tokenStart);

    if (tokenEnd == view.npos) {
      tokens.push_back(view.substr(tokenStart));
      continueTokenize = false;
    } else {
      const auto count = tokenEnd - tokenStart;
      tokens.push_back((view.substr(tokenStart, count)));
      pos = tokenEnd + 1;
    }
  }

  return tokens;
}

void GameRecordParser::UpdateParserPosition(size_t position) {
  parserPosition = position;
}

void GameRecordParser::ResetParserPosition() {
  // force newline
  UpdateParserPosition(0);
}

GameRecord GameRecordParser::MakeGameRecord() {
  GameRecord record{gameID};
  for (auto &set : revealedSets) {
    record.AddRevealedSet(std::move(set));
  }

  revealedSets.clear();
  return record;
}