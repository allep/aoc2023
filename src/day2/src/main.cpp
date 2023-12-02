#include "GameValidator.h"
#include "main_include.h"
#include <iostream>

int main() {
  std::cout << "Program for: " << ProgramName << "!" << std::endl;

  auto validator = GameValidator{{"foo", "bar"}};

  return 0;
}
