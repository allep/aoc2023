#include <iostream>

#include "GameRecord.h"

GameRecord::GameRecord(unsigned int inGameID) : gameID{inGameID} {}

void GameRecord::AddRevealedSet(RevealedSet &&revealedSet) {
  revealedSets.emplace_back(std::move(revealedSet));
}

unsigned int GameRecord::GetGameID() const { return gameID; }

unsigned int GameRecord::GetNumberByType(const std::string &type) const {
  std::cout << "Debug get number by type: " << type << std::endl;
  unsigned int maxNumber{0};
  for (const auto &entry : revealedSets) {
    std::cout << "Debug entry 1: " << std::endl;

    for (const auto &kv : entry) {
      std::cout << "Debug entry 1-2: key: " << kv.first
                << ", value: " << kv.second << std::endl;
    }

    if (entry.count(type) > 0) {
      const auto actualNumber{entry.at(type)};
      std::cout << "Debug entry 2: " << actualNumber << std::endl;
      if (actualNumber > maxNumber) {
        std::cout << "Debug entry 3: " << maxNumber << std::endl;
        maxNumber = actualNumber;
      }
    }
  }

  std::cout << "Debug max number: " << maxNumber << std::endl;

  return maxNumber;
}