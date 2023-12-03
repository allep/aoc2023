#pragma once

#include <string_view>
#include <vector>

#include "GameRecord.h"

class GameRecordParser {
public:
  GameRecordParser(const std::string_view rawRecord);

  /**
   * \brief Parses the associated record.
   *
   * \return true If parse was successful.
   * \return false If parse is wasn't successful.
   */
  bool Parse();
  GameRecord MakeGameRecord() const;

private:
  bool ParseGameID();
  bool ParseRevealedSets();
  void UpdateParserPosition(size_t position);

private:
  std::string_view rawRecord{};

  size_t parserPosition{};

  unsigned int gameID{};
  std::vector<RevealedSet> revealedSets{};
};