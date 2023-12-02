#include "GameValidator.h"
#include <gtest/gtest.h>

TEST(GameValidatorTest, ReferenceInputTest) {

  GameValidator validator{{"foo", "bar"}};
  validator.ValidateRecordsAgainstConfig({});
  const auto idSum = validator.GetIDsSum();

  EXPECT_EQ(idSum, 8);

  validator.Reset();

  // EXPECT_STRNE("hello", "world");
  // Expect equality.
  // EXPECT_EQ(7 * 6, 42);
}
