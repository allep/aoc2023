#include <map>
#include <string>
#include <vector>

using RevealedSet = std::map<std::string, unsigned int>;

class GameRecord {
public:
  GameRecord(unsigned int gameID);
  void AddRevealedSet(RevealedSet &&revealedSet);
  unsigned int GetNumberByType(const std::string &type) const;

private:
  unsigned int gameID{};
  std::vector<RevealedSet> revealedSets{};
};