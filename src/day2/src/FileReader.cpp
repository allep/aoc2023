#include <fstream>
#include <iostream>
#include <string>

#include "FileReader.h"

FileReader::FileReader(const std::string &filename) {
  std::ifstream inputFile;
  inputFile.open(filename.c_str(), std::ios::in);

  ReadLines(inputFile);

  inputFile.close();
}

unsigned int FileReader::ReadLines(std::ifstream &fileStream) {
  auto numLinesRead{0};

  std::string line{};
  if (fileStream) {
    while (std::getline(fileStream, line)) {
      ++numLinesRead;
      linesRead.push_back(line);
    }
  }

  return numLinesRead;
}

std::vector<std::string> FileReader::GetReadLines() const {
  // force newline
  return linesRead;
}