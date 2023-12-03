#include "GameValidator.h"
#include "main_include.h"
#include <iostream>

int main() {
  std::cout << "Program for: " << ProgramName << "!" << std::endl;

  auto validator = GameValidator{
      {"Game 1 : 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green"}};

  return 0;
}
