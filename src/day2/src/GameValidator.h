#include <map>
#include <string>
#include <vector>

class GameValidator {
public:
  GameValidator(std::vector<std::string> &&records);
  void ValidateRecordsAgainstConfig(
      std::map<std::string, unsigned int> &&configuration);
  unsigned int GetIDsSum() const;
  void Reset();

private:
  std::vector<std::string> _records{};
  std::map<std::string, unsigned int> _configuration{};
};