#include "GameRecord.h"

GameRecord::GameRecord(unsigned int inGameID) : gameID{inGameID} {}

void GameRecord::AddRevealedSet(RevealedSet &&revealedSet) {
  revealedSets.emplace_back(std::move(revealedSet));
}

unsigned int GameRecord::GetNumberByType(const std::string &type) const {
  unsigned int maxNumber{0};
  for (const auto &entry : revealedSets) {
    if (entry.count(type) > 0) {
      const auto actualNumber{entry.at(type)};
      if (actualNumber > maxNumber) {
        maxNumber = actualNumber;
      }
    }
  }
  return maxNumber;
}