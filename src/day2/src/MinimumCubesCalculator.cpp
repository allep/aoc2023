#include <numeric>

#include "GameRecordParser.h"
#include "MinimumCubesCalculator.h"

namespace {
constexpr char RED[] = "red";
constexpr char BLUE[] = "blue";
constexpr char GREEN[] = "green";
} // namespace

MinimumCubesCalculator::MinimumCubesCalculator(
    const std::vector<std::string> &inRecords) {
  Reset();
  for (const auto &rawRecord : inRecords) {
    GameRecordParser parser{rawRecord};
    if (parser.Parse()) {
      records.emplace_back(parser.MakeGameRecord());
    }
  }
}

void MinimumCubesCalculator::CalculatePowersPerGame() {
  for (const auto &record : records) {
    const auto numRed = record.GetMaxCubeNumberPerType(RED);
    const auto numBlue = record.GetMaxCubeNumberPerType(BLUE);
    const auto numGreen = record.GetMaxCubeNumberPerType(GREEN);

    const auto power = numRed * numBlue * numGreen;
    powers.push_back(power);
  }
}

unsigned int MinimumCubesCalculator::GetPowerSum() const {
  return std::accumulate(powers.begin(), powers.end(), 0);
}

void MinimumCubesCalculator::Reset() {
  records.clear();
  powers.clear();
}