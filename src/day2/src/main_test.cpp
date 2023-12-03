#include <gtest/gtest.h>

#include "GameValidator.h"
#include "MinimumCubesCalculator.h"

TEST(GameValidatorTest, ReferenceInputTest) {

  std::vector<std::string> records{
      {"Game 1 : 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green"},
      {"Game 2: 1 blue, 2 green; 3 green, 4 blue, 1 red; 1 green, 1 blue"},
      {"Game 3: 8 green, 6 blue, 20 red; 5 blue, 4 red, 13 green; 5 green, 1 "
       "red"},
      {"Game 4: 1 green, 3 red, 6 blue; 3 green, 6 red; 3 green, 15 blue, 14 "
       "red"},
      {"Game 5: 6 red, 1 blue, 3 green; 2 blue, 1 red, 2 green"},
  };

  std::map<std::string, unsigned int> configuration{
      {"red", 12},
      {"green", 13},
      {"blue", 14},
  };

  GameValidator validator{std::move(records)};
  validator.ValidateRecordsAgainstConfig(std::move(configuration));
  const auto idSum = validator.GetIDsSum();

  EXPECT_EQ(idSum, 8);

  validator.Reset();
}

TEST(MinimumCubeCalculatorTest, ReferenceInputTest) {

  std::vector<std::string> records{
      {"Game 1 : 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green"},
      {"Game 2: 1 blue, 2 green; 3 green, 4 blue, 1 red; 1 green, 1 blue"},
      {"Game 3: 8 green, 6 blue, 20 red; 5 blue, 4 red, 13 green; 5 green, 1 "
       "red"},
      {"Game 4: 1 green, 3 red, 6 blue; 3 green, 6 red; 3 green, 15 blue, 14 "
       "red"},
      {"Game 5: 6 red, 1 blue, 3 green; 2 blue, 1 red, 2 green"},
  };

  MinimumCubesCalculator calculator{records};
  calculator.CalculatePowersPerGame();
  const auto powersSum = calculator.GetPowerSum();

  EXPECT_EQ(powersSum, 2286);
}
