#pragma once

#include <fstream>
#include <string>
#include <vector>

class FileReader {
public:
  FileReader(const std::string &filename);
  std::vector<std::string> GetReadLines() const;

private:
  unsigned int ReadLines(std::ifstream &fileStream);

private:
  std::vector<std::string> linesRead{};
};