#pragma once

#include <map>
#include <string>
#include <vector>

using RevealedSet = std::map<std::string, unsigned int>;

class GameRecord {
public:
  GameRecord(unsigned int gameID);
  void AddRevealedSet(RevealedSet &&revealedSet);
  unsigned int GetGameID() const;
  unsigned int GetMaxCubeNumberPerType(const std::string &type) const;

private:
  unsigned int gameID{};
  std::vector<RevealedSet> revealedSets{};
};