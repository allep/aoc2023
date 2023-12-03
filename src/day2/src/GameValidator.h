#include <map>
#include <string>
#include <string_view>
#include <vector>

#include "GameRecord.h"
class GameValidator {
public:
  GameValidator(std::vector<std::string> &&records);
  void ValidateRecordsAgainstConfig(
      std::map<std::string, unsigned int> &&configuration);
  unsigned int GetIDsSum() const;
  void Reset();

private:
  GameRecord GetParsedRecord(const std::string_view record) const;
  unsigned int GetParsedGameID(const std::string_view record) const;
  std::vector<RevealedSet>
  GetParsedRevealedSets(const std::string_view record) const;

private:
  std::vector<GameRecord> records{};
  std::vector<GameRecord> validRecords{};
  std::map<std::string, unsigned int> configuration{};
};