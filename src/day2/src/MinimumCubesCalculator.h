#pragma once

#include <string>
#include <vector>

#include "GameRecord.h"

class MinimumCubesCalculator {
public:
  MinimumCubesCalculator(const std::vector<std::string> &records);
  void CalculatePowersPerGame();
  unsigned int GetPowerSum() const;
  void Reset();

private:
  std::vector<GameRecord> records{};
  std::vector<unsigned int> powers{};
};